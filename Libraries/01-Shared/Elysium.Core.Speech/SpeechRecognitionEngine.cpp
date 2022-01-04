#include "SpeechRecognitionEngine.hpp"

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_DICTATIONGRAMMAR
#include "DictationGrammar.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEARRAY
#include "../Elysium.Core.Template/FixedSizeArray.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION
#include "../Elysium.Core/COMException.hpp"
#endif

#ifndef SPHelper_h
#include <sphelper.h>
#endif
#endif

Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::SpeechRecognitionEngine()
	: Elysium::Core::Speech::Recognition::SpeechRecognitionEngine(Elysium::Core::Globalization::CultureInfo())
{ }

Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::SpeechRecognitionEngine(const Elysium::Core::Globalization::CultureInfo& Culture)
	: AudioStateChanged(), SpeechRecognized(),
#if defined ELYSIUM_CORE_OS_WINDOWS
	_NativeRecognizer(InitializeNativeRecognizer()), _NativeRecognizerContext(InitializeNativeRecognizerContext()), _NativeMemoryStream(InitializeNativeStream())
#endif
{ }

Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::~SpeechRecognitionEngine()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	if (_NativeMemoryStream != nullptr)
	{
		IStream* BaseStream = nullptr;
		HRESULT Result = _NativeMemoryStream->GetBaseStream(&BaseStream);
		if (SUCCEEDED(Result) && BaseStream != nullptr)
		{
			BaseStream->Release();
			BaseStream = nullptr;
		}

		_NativeMemoryStream->Release();
		_NativeMemoryStream = nullptr;
	}

	if (_NativeRecognizerContext != nullptr)
	{
		_NativeRecognizerContext->Release();
		_NativeRecognizerContext = nullptr;
	}

	if (_NativeRecognizer != nullptr)
	{
		_NativeRecognizer->Release();
		_NativeRecognizer = nullptr;
	}

	CoUninitialize();
#endif
}

void Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::LoadGrammar(Grammar& Grammar)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	if (Grammar._NativeRecognitionGrammar == nullptr)
	{
		if (FAILED(Result = _NativeRecognizerContext->CreateGrammar(0, &Grammar._NativeRecognitionGrammar)))
		{
			throw Elysium::Core::Runtime::InteropServices::COMException(Result);
		}
	}

	Grammar.Load();
#endif
}

void Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::SetInputToDefaultAudioDevice()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	ISpObjectToken* DefaultAudioInputToken = nullptr;
	if (FAILED(Result = SpGetDefaultTokenFromCategoryId(SPCAT_AUDIOIN, &DefaultAudioInputToken)))
	{
		// "0x8004503a - SPERR_NOT_FOUND - IDispatch error #20026" may occurre if no default audio device could be located (for instance if no microphone is connected)
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	if (FAILED(Result = _NativeRecognizer->SetInput(DefaultAudioInputToken, TRUE)))
	{
		// "0x8004505f - SPERR_NOT_SUPPORTED_FOR_SHARED_RECOGNIZER - IDispatch error #20063" occurres if _NativeRecognizer was created using CLSID_SpSharedRecognizer
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::SetInputToAudioStream(Elysium::Core::IO::Stream& AudioStream, const Elysium::Core::Speech::AudioFormat::SpeechAudioFormatInfo& FormatInfo)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	if (_NativeMemoryStream != nullptr)
	{
		IStream* BaseStream = nullptr;
		if (SUCCEEDED(Result = _NativeMemoryStream->GetBaseStream(&BaseStream)) && BaseStream != nullptr)
		{
			BaseStream->Release();
			BaseStream = nullptr;
		}

		_NativeMemoryStream->Release();
		_NativeMemoryStream = InitializeNativeStream();
	}

	IStream* NativeMemoryStream = SHCreateMemStream(NULL, 0);
	if (NativeMemoryStream == nullptr)
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	WAVEFORMATEX NativeFormat = WAVEFORMATEX();
	NativeFormat.wFormatTag = static_cast<Elysium::Core::uint16_t>(FormatInfo.GetEncodingFormat());
	NativeFormat.nChannels = FormatInfo.GetChannelCount();
	NativeFormat.nSamplesPerSec = FormatInfo.GetSamplesPerSecond();
	NativeFormat.wBitsPerSample = FormatInfo.GetBitsPerSample();
	NativeFormat.nBlockAlign = FormatInfo.GetBlockAlign();
	NativeFormat.nAvgBytesPerSec = FormatInfo.GetAverageBytesPerSecond();
	NativeFormat.cbSize = 0;

	if (FAILED(Result = _NativeMemoryStream->SetBaseStream(NativeMemoryStream, SPDFID_WaveFormatEx, &NativeFormat)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	Elysium::Core::size BytesRead = 0;
	ULONG BytesWritten = 0;
	Elysium::Core::Template::Container::FixedSizeArray<Elysium::Core::byte, 4096> Buffer = Elysium::Core::Template::Container::FixedSizeArray<Elysium::Core::byte, 4096>();
	while ((BytesRead = AudioStream.Read(&Buffer[0], Buffer.GetLength())) > 0)
	{
		NativeMemoryStream->Write(&Buffer[0], BytesRead, &BytesWritten);
	}

	LARGE_INTEGER Begin = { };
	ULARGE_INTEGER Position;
	if (FAILED(Result = _NativeMemoryStream->Seek(Begin, 0, &Position)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	if (FAILED(Result = _NativeRecognizer->SetInput(_NativeMemoryStream, TRUE)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
#error "unsupported os"
#endif
}

void Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::SetInputToWaveFile(const Elysium::Core::Utf8String& Path)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;
	if (_NativeMemoryStream != nullptr)
	{
		IStream* BaseStream = nullptr;
		if (SUCCEEDED(Result = _NativeMemoryStream->GetBaseStream(&BaseStream)) && BaseStream != nullptr)
		{
			BaseStream->Release();
			BaseStream = nullptr;
		}

		_NativeMemoryStream->Release();
		_NativeMemoryStream = InitializeNativeStream();
	}

	_NativeMemoryStream = InitializeNativeStream();

	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> PathBytes = _WindowsEncoding.GetBytes(&Path[0], Path.GetLength() + sizeof(char8_t));

	if (FAILED(Result = _NativeMemoryStream->BindToFile((const wchar_t*)&PathBytes[0], SPFM_OPEN_READONLY, &SPDFID_WaveFormatEx, nullptr, 0)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	if (FAILED(Result = _NativeRecognizer->SetInput(_NativeMemoryStream, TRUE)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::Recognize()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	if (FAILED(Result = _NativeRecognizerContext->Resume(0)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	ProcessEventMessageQueue();
#else
	throw 1;
#endif
}

#if defined ELYSIUM_CORE_OS_WINDOWS
ISpRecognizer* Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::InitializeNativeRecognizer()
{
	if (FAILED(CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED)))
	{
		return nullptr;
	}

	HRESULT Result = S_OK;

	ISpRecognizer* NativeRecognizer = nullptr;
	if (FAILED(Result = CoCreateInstance(CLSID_SpInprocRecognizer, nullptr, CLSCTX_ALL, IID_ISpRecognizer, (void**)&NativeRecognizer)))
	{
		return nullptr;
	}

	return NativeRecognizer;
}

ISpRecoContext* Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::InitializeNativeRecognizerContext()
{
	if (_NativeRecognizer == nullptr)
	{
		return nullptr;
	}

	HRESULT Result = S_OK;

	ISpRecoContext* NativeRecognizerContext = nullptr;
	if (FAILED(Result = _NativeRecognizer->CreateRecoContext(&NativeRecognizerContext)))
	{
		// "0x80045077 - SPERR_RECOGNIZER_NOT_FOUND - IDispatch error #20087" may occurre if no speech recognition package is installed
		// "0x80045078 - SPERR_AUDIO_NOT_FOUND - IDispatch error #20088" may occurre if no default audio device could be located (for instance if no microphone is connected)
		//throw Elysium::Core::Runtime::InteropServices::COMException(Result);
		return nullptr;
	}

	if (FAILED(Result = NativeRecognizerContext->Pause(0)))
	{
		NativeRecognizerContext->Release();
		return nullptr;
	}

	const ULONGLONG Interests = SPFEI(SPEVENTENUM::SPEI_RECOGNITION) | SPFEI(SPEVENTENUM::SPEI_FALSE_RECOGNITION) | SPFEI(SPEVENTENUM::SPEI_RECO_STATE_CHANGE);
	if (FAILED(Result = NativeRecognizerContext->SetInterest(Interests, Interests)))
	{
		NativeRecognizerContext->Release();
		return nullptr;
	}

	if (FAILED(Result = NativeRecognizerContext->SetNotifyWin32Event()))
	{
		NativeRecognizerContext->Release();
		return nullptr;
	}

	return NativeRecognizerContext;
}

ISpStream* Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::InitializeNativeStream()
{
	ISpStream* NativeStream;
	HRESULT Result = CoCreateInstance(CLSID_SpStream, nullptr, CLSCTX_ALL, __uuidof(ISpStream), (void**)&NativeStream);
	if (FAILED(Result))
	{
		return nullptr;
	}

	return NativeStream;
}

void Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::ProcessEventMessageQueue()
{
	HRESULT Result = S_OK;
	SPEVENT Event;
	ULONG NumberOfEventsReceived = 0;

	wchar_t* NativeText;
	Elysium::Core::Utf8String Text;

	do
	{
		Result = _NativeRecognizerContext->WaitForNotifyEvent(500);
		if (Result == S_FALSE)
		{
			break;
		}

		if (SUCCEEDED(Result = _NativeRecognizerContext->GetEvents(1, &Event, &NumberOfEventsReceived)))
		{
			ISpRecoResult* NativeRecognizedResult = reinterpret_cast<ISpRecoResult*>(Event.lParam);

			if (FAILED(Result = NativeRecognizedResult->GetText(SPPHRASERNG::SPPR_ALL_ELEMENTS, SPPHRASERNG::SPPR_ALL_ELEMENTS, FALSE, &NativeText, NULL)))
			{
				// ToDo: cleanup
				break;
			}

			Text = _WindowsEncoding.GetString((Elysium::Core::byte*)NativeText, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetSize(NativeText));
			CoTaskMemFree(NativeText);

			switch (Event.eEventId)
			{
			case SPEVENTENUM::SPEI_RECOGNITION:
			{
				SpeechRecognized(*this, SpeechRecognizedEventArgs(RecognitionResult(Elysium::Core::Template::Functional::Move(Text))));
				break;
			}
			case SPEVENTENUM::SPEI_FALSE_RECOGNITION:
			{
				bool sdfsdfdsfdsf = false;
				break;
			}
			case SPEVENTENUM::SPEI_RECO_STATE_CHANGE:
			{
				bool sdfsdfdsfds678f = false;
				break;
			}
			default:
			{
				bool x456 = false;
				break;
			}
			}
			SpClearEvent(&Event);
		}
	} while (true);
}
#endif
