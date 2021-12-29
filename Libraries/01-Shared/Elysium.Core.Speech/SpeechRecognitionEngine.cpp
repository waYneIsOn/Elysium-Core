#include "SpeechRecognitionEngine.hpp"

#ifndef ELYSIUM_CORE_SPEECH_RECOGNITION_DICTATIONGRAMMAR
#include "DictationGrammar.hpp"
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
	: SpeechRecognized(),
#if defined ELYSIUM_CORE_OS_WINDOWS
	_NativeRecognizer(InitializeNativeRecognizer()), _NativeRecognizerContext(InitializeNativeRecognizerContext()), _NativeMemoryStream(nullptr)
#endif
{ }

Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::~SpeechRecognitionEngine()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	if (_NativeMemoryStream != nullptr)
	{
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

void Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::LoadGrammar(const Grammar& Grammar)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	ISpRecoGrammar* NativeRecognitionGrammar = nullptr;
	if (FAILED(Result = _NativeRecognizerContext->CreateGrammar(0, &NativeRecognitionGrammar)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	const wchar_t* RuleName = L"SomeCustomRuleName";

	const DictationGrammar* DictationGrammar = dynamic_cast<const Elysium::Core::Speech::Recognition::DictationGrammar*>(&Grammar);
	if (DictationGrammar == nullptr)
	{
		// ToDo
		WORD LanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
		if (FAILED(Result = NativeRecognitionGrammar->ResetGrammar(LanguageId)))
		{
			NativeRecognitionGrammar->Release();
			throw Elysium::Core::Runtime::InteropServices::COMException(Result);
		}

		// ToDo
		SPSTATEHANDLE State;
		if (FAILED(Result = NativeRecognitionGrammar->GetRule(RuleName, 0, SPRAF_TopLevel | SPRAF_Active, true, &State)))
		{
			NativeRecognitionGrammar->Release();
			throw Elysium::Core::Runtime::InteropServices::COMException(Result);
		}

		// ToDo
		const wchar_t* Command = L"computer";
		if (FAILED(Result = NativeRecognitionGrammar->AddWordTransition(State, NULL, Command, L" ", SPWT_LEXICAL, 1, nullptr)))
		{
			NativeRecognitionGrammar->Release();
			throw Elysium::Core::Runtime::InteropServices::COMException(Result);
		}

		//NativeRecognitionGrammar->LoadCmdFromFile(nullptr, SPLOADOPTIONS::SPLO_DYNAMIC);
	}
	else
	{
		//DictationGrammar->_Topic
		//NativeRecognitionGrammar->LoadDictation()
	}







	if (FAILED(Result = NativeRecognitionGrammar->Commit(0)))
	{
		NativeRecognitionGrammar->Release();
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	if (FAILED(Result = NativeRecognitionGrammar->SetRuleState(RuleName, 0, SPRS_ACTIVE)))
	{
		NativeRecognitionGrammar->Release();
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
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

void Elysium::Core::Speech::Recognition::SpeechRecognitionEngine::SetInputToWaveFile(const Elysium::Core::String& Path)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	if (_NativeMemoryStream != nullptr)
	{
		_NativeMemoryStream->Release();
		_NativeMemoryStream = InitializeNativeStream();
	}

	_NativeMemoryStream = InitializeNativeStream();

	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> PathBytes = _WindowsEncoding.GetBytes(&Path[0], Path.GetLength() + sizeof(char8_t));

	HRESULT Result = S_OK;
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

	const ULONGLONG Interests = SPFEI(SPEVENTENUM::SPEI_RECOGNITION) | SPFEI(SPEVENTENUM::SPEI_FALSE_RECOGNITION);
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
	ISpRecoResult* RecognizedResult = nullptr;
	SPPHRASE* Phrase = nullptr;
	ISpPhraseAlt* PhraseAlternates = nullptr;
	ULONG PhrasesReceived = 0;
	do
	{
		Result = _NativeRecognizerContext->WaitForNotifyEvent(500);
		if (Result == S_FALSE)
		{
			break;
		}

		if (SUCCEEDED(Result = _NativeRecognizerContext->GetEvents(1, &Event, &NumberOfEventsReceived)))
		{
			RecognizedResult = reinterpret_cast<ISpRecoResult*>(Event.lParam);

			wchar_t* WindowsText;
			if (FAILED(Result = RecognizedResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, FALSE, &WindowsText, NULL)))
			{
				// ToDo: cleanup
				break;
			}
			
			if (FAILED(Result = RecognizedResult->GetAlternates(0, SPPHRASERNG::SPPR_ALL_ELEMENTS, 1, &PhraseAlternates, &PhrasesReceived)))
			{
				// ToDo: cleanup
				break;
			}
			
			//RecognizedResult->GetAlternates
			//RecognizedResult->GetAudio
			//RecognizedResult->GetPhrase
			//RecognizedResult->GetRecoContext
			//RecognizedResult->GetResultTimes
			//RecognizedResult->GetSerializedPhrase

			switch (Event.eEventId)
			{
			case SPEVENTENUM::SPEI_RECOGNITION:
			{
				SpeechRecognized(*this, SpeechRecognizedEventArgs(RecognitionResult()));

				PhraseAlternates->Release();
				CoTaskMemFree(WindowsText);
				//RecognizedResult->Release();	// SpClearEvent(&Event) appears to be cleaning this up

				break;
			}
			case SPEVENTENUM::SPEI_FALSE_RECOGNITION:
			{
				PhraseAlternates->Release();
				CoTaskMemFree(WindowsText);
				//RecognizedResult->Release();	// SpClearEvent(&Event) appears to be cleaning this up

				break;
			}
			default:
			{
				bool x = false;
				break;
			}
			}
			SpClearEvent(&Event);
		}
	} while (true);
}
#endif
