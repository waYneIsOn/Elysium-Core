#include "SpeechSynthesizer.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Elysium.Core.Template/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#include "../Elysium.Core.Threading/Task.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_COMEXCEPTION
#include "../Elysium.Core/COMException.hpp"
#endif

#ifndef SPHelper_h
#include <sphelper.h>
#endif
#endif

Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeechSynthesizer()
	: BookmarkReached(), PhonemeReached(), SpeakCompleted(), SpeakProgress(), SpeakStarted(), StateChanged(), VisemeReached(), VoiceChanged(),
#if defined ELYSIUM_CORE_OS_WINDOWS
	_NativeSynthesizer(InitializeNativeSynthesizer()), _NativeMemoryStream(InitializeNativeStream()), _TargetStream(nullptr)
#endif
{ }

Elysium::Core::Speech::Synthesis::SpeechSynthesizer::~SpeechSynthesizer()
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

	if (_NativeSynthesizer != nullptr)
	{
		_NativeSynthesizer->Release();
		_NativeSynthesizer = nullptr;
	}

	CoUninitialize();
#endif
}

const Elysium::Core::uint32_t Elysium::Core::Speech::Synthesis::SpeechSynthesizer::GetRate() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	long Volume;
	HRESULT Result = _NativeSynthesizer->GetRate(&Volume);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	return Volume;
#else
	throw 1;
#endif
}

const Elysium::Core::Speech::Synthesis::SynthesizerState Elysium::Core::Speech::Synthesis::SpeechSynthesizer::GetState() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	SPVOICESTATUS VoiceStatus;
	LPWSTR LastBookmark = { };
	HRESULT Result = _NativeSynthesizer->GetStatus(&VoiceStatus, &LastBookmark);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	return (SynthesizerState)VoiceStatus.dwRunningState;
#else
	throw 1;
#endif
}

const Elysium::Core::Speech::Synthesis::VoiceInfo Elysium::Core::Speech::Synthesis::SpeechSynthesizer::GetVoice() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	ISpObjectToken* VoiceToken;
	HRESULT Result = _NativeSynthesizer->GetVoice(&VoiceToken);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	return VoiceInfo(VoiceToken, true);
#else
	throw 1;
#endif
}

const Elysium::Core::uint16_t Elysium::Core::Speech::Synthesis::SpeechSynthesizer::GetVolume() const
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	unsigned short Volume;
	HRESULT Result = _NativeSynthesizer->GetVolume(&Volume);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	return Volume;
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SetRate(const Elysium::Core::uint32_t Value)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = _NativeSynthesizer->SetRate(Value);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SetVolume(const Elysium::Core::uint16_t Value)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = _NativeSynthesizer->SetVolume(Value);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
	throw 1;
#endif
}

const Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice> Elysium::Core::Speech::Synthesis::SpeechSynthesizer::GetInstalledVoices()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	ISpObjectTokenCategory* CategoryToken = nullptr;
	if (FAILED(Result = SpGetCategoryFromId(SPCAT_VOICES, &CategoryToken)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	IEnumSpObjectTokens* VoiceEnumerationToken;
	if (FAILED(Result = CategoryToken->EnumTokens(nullptr, nullptr, &VoiceEnumerationToken)))
	{	
		CategoryToken->Release();

		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	ULONG NumberOfInstalledVoices;
	if (FAILED(Result = VoiceEnumerationToken->GetCount(&NumberOfInstalledVoices)))
	{
		VoiceEnumerationToken->Release();
		CategoryToken->Release();

		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice> InstalledVoices =
		Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice>(NumberOfInstalledVoices);
	ISpObjectToken* VoiceToken;
	while (VoiceEnumerationToken->Next(1, &VoiceToken, nullptr) == S_OK)
	{
		InstalledVoices.PushBack(Elysium::Core::Template::Functional::Move(InstalledVoice(false, VoiceInfo(VoiceToken, true))));
		// do NOT release token as VoiceInfo now owns VoiceToken and is responsible for releasing it
	}

	VoiceEnumerationToken->Release();
	CategoryToken->Release();

	return InstalledVoices;
#else
	throw 1;
#endif
}

const Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice> Elysium::Core::Speech::Synthesis::SpeechSynthesizer::GetInstalledVoices(const Elysium::Core::Globalization::CultureInfo& Culture)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;

	ISpObjectTokenCategory* CategoryToken = nullptr;
	if (FAILED(Result = SpGetCategoryFromId(SPCAT_VOICES, &CategoryToken)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	IEnumSpObjectTokens* VoiceEnumerationToken;
	if (FAILED(Result = CategoryToken->EnumTokens(nullptr, nullptr, &VoiceEnumerationToken)))
	{	
		CategoryToken->Release();

		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice> InstalledVoices =
		Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice>();
	bool LocaleIdMatches;
	ISpObjectToken* VoiceToken;
	while (VoiceEnumerationToken->Next(1, &VoiceToken, nullptr) == S_OK)
	{
		ISpDataKey* AttributesKey;
		if (FAILED(Result = VoiceToken->OpenKey(SPTOKENKEY_ATTRIBUTES, &AttributesKey)))
		{
			VoiceEnumerationToken->Release();
			CategoryToken->Release();

			throw Elysium::Core::Runtime::InteropServices::COMException(Result);
		}

		wchar_t* NativeValue;
		if (FAILED(Result = AttributesKey->GetStringValue(L"Language", &NativeValue)))
		{
			AttributesKey->Release();
			VoiceEnumerationToken->Release();
			CategoryToken->Release();

			throw Elysium::Core::Runtime::InteropServices::COMException(Result);
		}

		LocaleIdMatches = false;
		const Elysium::Core::int32_t LocaleId = Elysium::Core::Template::Text::Convert<wchar_t>::ToInt32(NativeValue,
			Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(NativeValue), 16);
		if (LocaleId == Culture.GetLCID())
		{
			InstalledVoices.PushBack(Elysium::Core::Template::Functional::Move(InstalledVoice(false, VoiceInfo(VoiceToken, true))));
			LocaleIdMatches = true;
		}

		CoTaskMemFree(NativeValue);
		AttributesKey->Release();
		if (!LocaleIdMatches)
		{	// only release VoiceToken if no VoiceInfo owns it
			VoiceToken->Release();
		}
	}

	VoiceEnumerationToken->Release();
	CategoryToken->Release();

	return InstalledVoices;
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::Pause()
{
	HRESULT Result = _NativeSynthesizer->Pause();
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
	StateChanged(*this, StateChangedEventArgs(u8"PROMPT", SynthesizerState::Speaking, SynthesizerState::Paused));
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::Resume()
{
	HRESULT Result = _NativeSynthesizer->Resume();
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
	StateChanged(*this, StateChangedEventArgs(u8"PROMPT", SynthesizerState::Paused, SynthesizerState::Speaking));

	// ToDo:
	// this should be done async as the speak was triggered in an async fashion!
	// as I am currently unaware of how microsoft does this (freesync notifications?), I will leave this in for now
	ProcessEventMessageQueue();
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SelectVoice(const String& Name)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	// ToDo: find a better way to select voice than by iterating through all installed voices!

	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> NameBytes =
		_WindowsEncoding.GetBytes(&Name[0], Name.GetLength() + sizeof(char8_t));

	HRESULT Result = S_OK;

	ISpObjectTokenCategory* CategoryToken = nullptr;
	if (FAILED(Result = SpGetCategoryFromId(SPCAT_VOICES, &CategoryToken)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
}

	IEnumSpObjectTokens* VoiceEnumerationToken;
	if (FAILED(Result = CategoryToken->EnumTokens(nullptr, nullptr, &VoiceEnumerationToken)))
	{	
		CategoryToken->Release();

		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice> InstalledVoices =
		Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice>();
	ISpObjectToken* VoiceToken;
	while (VoiceEnumerationToken->Next(1, &VoiceToken, nullptr) == S_OK)
	{
		ISpDataKey* AttributesKey;
		if (FAILED(Result = VoiceToken->OpenKey(SPTOKENKEY_ATTRIBUTES, &AttributesKey)))
		{
			VoiceEnumerationToken->Release();
			CategoryToken->Release();

			throw Elysium::Core::Runtime::InteropServices::COMException(Result);
		}

		wchar_t* NativeValue;
		if (FAILED(Result = AttributesKey->GetStringValue(L"Name", &NativeValue)))
		{
			AttributesKey->Release();
			VoiceEnumerationToken->Release();
			CategoryToken->Release();
			
			throw Elysium::Core::Runtime::InteropServices::COMException(Result);
		}

		if (Elysium::Core::Template::Text::CharacterTraits<wchar_t>::Compare((wchar_t*)&NameBytes[0], NativeValue, NameBytes.GetLength()) == 0)
		{
			if (FAILED(Result = SetNativeVoice(VoiceToken)))
			{
				CoTaskMemFree(NativeValue);
				AttributesKey->Release();
				VoiceEnumerationToken->Release();
				CategoryToken->Release();

				throw Elysium::Core::Runtime::InteropServices::COMException(Result);
			}
		}

		CoTaskMemFree(NativeValue);
		AttributesKey->Release();
		VoiceToken->Release();
	}

	VoiceEnumerationToken->Release();
	CategoryToken->Release();
#else
throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SelectVoice(const VoiceInfo& Info)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = SetNativeVoice(Info._VoiceToken);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SetOutputToAudioStream(Elysium::Core::IO::Stream& AudioDestination, const AudioFormat::SpeechAudioFormatInfo& FormatInfo)
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

	if (FAILED(Result = _NativeSynthesizer->SetOutput(_NativeMemoryStream, TRUE)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	_TargetStream = &AudioDestination;
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SetOutputToDefaultAudioDevice()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	HRESULT Result = S_OK;
	
	if (FAILED(Result = _NativeSynthesizer->SetOutput(nullptr, TRUE)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	_TargetStream = nullptr;
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SetOutputToWaveFile(const Elysium::Core::String& Path, const AudioFormat::SpeechAudioFormatInfo& FormatInfo)
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

	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> PathBytes = _WindowsEncoding.GetBytes(&Path[0], Path.GetLength() + sizeof(char8_t));

	WAVEFORMATEX NativeFormat = WAVEFORMATEX();
	NativeFormat.wFormatTag = static_cast<Elysium::Core::uint16_t>(FormatInfo.GetEncodingFormat());
	NativeFormat.nChannels = FormatInfo.GetChannelCount();
	NativeFormat.nSamplesPerSec = FormatInfo.GetSamplesPerSecond();
	NativeFormat.wBitsPerSample = FormatInfo.GetBitsPerSample();
	NativeFormat.nBlockAlign = FormatInfo.GetBlockAlign();
	NativeFormat.nAvgBytesPerSec = FormatInfo.GetAverageBytesPerSecond();
	NativeFormat.cbSize = 0;

	if (FAILED(Result = _NativeMemoryStream->BindToFile((const wchar_t*)&PathBytes[0], SPFM_CREATE_ALWAYS, &SPDFID_WaveFormatEx, &NativeFormat, 0)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	if (FAILED(Result = _NativeSynthesizer->SetOutput(_NativeMemoryStream, TRUE)))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}

	_TargetStream = nullptr;
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SetOutputToWaveStream(Elysium::Core::IO::Stream& AudioDestination)
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	throw 1;
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeakAsync(const char8_t* TextToSpeak)
{
	if (TextToSpeak == nullptr)
	{	// ToDo: throw specific exception
		throw 1;
	}

#if defined ELYSIUM_CORE_OS_WINDOWS
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes =
		_WindowsEncoding.GetBytes(&TextToSpeak[0], Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(TextToSpeak) + sizeof(char8_t));

	HRESULT Result = SpeakNatively((wchar_t*)&Bytes[0], SPEAKFLAGS::SPF_ASYNC);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeakAsync(const String& TextToSpeak)
{
	SpeakAsync(&TextToSpeak[0]);
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::Speak(const char8_t* TextToSpeak)
{
	if (TextToSpeak == nullptr)
	{	// ToDo: throw specific exception
		throw 1;
	}

#if defined ELYSIUM_CORE_OS_WINDOWS
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes =
		_WindowsEncoding.GetBytes(&TextToSpeak[0], Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(TextToSpeak) + sizeof(char8_t));

	HRESULT Result = SpeakNatively((wchar_t*)&Bytes[0], SPEAKFLAGS::SPF_DEFAULT);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::Speak(const String & TextToSpeak)
{
	Speak(&TextToSpeak[0]);
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeakSsml(const char8_t* TextToSpeak)
{
	if (TextToSpeak == nullptr)
	{	// ToDo: throw specific exception
		throw 1;
	}

#if defined ELYSIUM_CORE_OS_WINDOWS
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes =
		_WindowsEncoding.GetBytes(&TextToSpeak[0], Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(TextToSpeak) + sizeof(char8_t));

	HRESULT Result = SpeakNatively((wchar_t*)&Bytes[0], SPEAKFLAGS::SPF_IS_XML);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeakSsml(const String& TextToSpeak)
{
	SpeakSsml(&TextToSpeak[0]);
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeakSsmlAsync(const char8_t* TextToSpeak)
{
	if (TextToSpeak == nullptr)
	{	// ToDo: throw specific exception
		throw 1;
	}

#if defined ELYSIUM_CORE_OS_WINDOWS
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes =
		_WindowsEncoding.GetBytes(&TextToSpeak[0], Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(TextToSpeak) + sizeof(char8_t));

	HRESULT Result = SpeakNatively((wchar_t*)&Bytes[0], SPEAKFLAGS::SPF_IS_XML | SPEAKFLAGS::SPF_ASYNC);
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
#else
	throw 1;
#endif
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeakSsmlAsync(const String& TextToSpeak)
{
	SpeakSsmlAsync(&TextToSpeak[0]);
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::WaitUntilDone(const Elysium::Core::TimeSpan Timeout)
{
	HRESULT Result = _NativeSynthesizer->WaitUntilDone(static_cast<ULONG>(Timeout.GetTotalMilliseconds()));
	if (FAILED(Result))
	{
		throw Elysium::Core::Runtime::InteropServices::COMException(Result);
	}
}

#if defined ELYSIUM_CORE_OS_WINDOWS
ISpVoice* Elysium::Core::Speech::Synthesis::SpeechSynthesizer::InitializeNativeSynthesizer()
{
	if (FAILED(CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED)))
	{
		return nullptr;
	}

	HRESULT Result = S_OK;

	ISpVoice* NativeSynthesizer = nullptr;
	if (FAILED(Result = CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL, IID_ISpVoice, (void**)&NativeSynthesizer)))
	{
		return nullptr;
	}

	const ULONGLONG Interests = SPFEI(SPEVENTENUM::SPEI_START_INPUT_STREAM) | SPFEI(SPEVENTENUM::SPEI_END_INPUT_STREAM) |
		SPFEI(SPEVENTENUM::SPEI_VOICE_CHANGE) | SPFEI(SPEVENTENUM::SPEI_TTS_BOOKMARK) | SPFEI(SPEVENTENUM::SPEI_WORD_BOUNDARY) |
		SPFEI(SPEVENTENUM::SPEI_PHONEME) | SPFEI(SPEVENTENUM::SPEI_VISEME) | SPFEI(SPEVENTENUM::SPEI_TTS_BOOKMARK);
	if (FAILED(NativeSynthesizer->SetInterest(Interests, Interests)))
	{
		NativeSynthesizer->Release();
		NativeSynthesizer = nullptr;

		return nullptr;
	}
	
	if (FAILED(Result = NativeSynthesizer->SetNotifyWin32Event()))
	{
		NativeSynthesizer->Release();
		NativeSynthesizer = nullptr;

		return nullptr;
	}

	return NativeSynthesizer;
}

ISpStream* Elysium::Core::Speech::Synthesis::SpeechSynthesizer::InitializeNativeStream()
{
	ISpStream* NativeStream;
	HRESULT Result = CoCreateInstance(CLSID_SpStream, nullptr, CLSCTX_ALL, __uuidof(ISpStream), (void**)&NativeStream);
	if (FAILED(Result))
	{
		return nullptr;
	}

	return NativeStream;
}

HRESULT Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SetNativeVoice(ISpObjectToken* VoiceToken) noexcept
{
	return _NativeSynthesizer->SetVoice(VoiceToken);
}

HRESULT Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeakNatively(const wchar_t* TextToSpeak, const Elysium::Core::int32_t Flags) noexcept
{
	HRESULT Result = S_OK;

	// always speak async as to give the current thread the ability to poll the message queue (so events can be triggered and processed right away)
	if (FAILED(Result = _NativeSynthesizer->Speak(TextToSpeak, Flags | SPEAKFLAGS::SPF_ASYNC, nullptr)))
	{
		return Result;
	}

	if ((Flags & SPEAKFLAGS::SPF_ASYNC) == SPEAKFLAGS::SPF_ASYNC)
	{
		// ToDo:
		// while this works per se, it causes problems with multiple calls of SpeakAsync(...)!
		// also all these events will then be processed on a single thread while this does not appear to be the case in .NET.
		// ergo microsoft might use some other way (freesync notification?) for this in general.
		Elysium::Core::Threading::Tasks::Task ProcessEventsTask = Elysium::Core::Threading::Tasks::Task(Elysium::Core::Template::Container::Delegate<void>::Bind<SpeechSynthesizer, &SpeechSynthesizer::ProcessEventMessageQueue>(*this));
		ProcessEventsTask.Start();
	}
	else
	{
		ProcessEventMessageQueue();
	}

	if (_TargetStream != nullptr)
	{
		LARGE_INTEGER Begin = { };
		ULARGE_INTEGER Position;
		if (FAILED(Result = _NativeMemoryStream->Seek(Begin, 0, &Position)))
		{
			return Result;
		}

		const Elysium::Core::uint32_t BufferLength = 255;
		Elysium::Core::byte Buffer[BufferLength];
		unsigned long BytesRead = 0;
		do
		{
			if (FAILED(Result = _NativeMemoryStream->Read(&Buffer[0], BufferLength, &BytesRead)))
			{
				return Result;
			}

			_TargetStream->Write(&Buffer[0], BytesRead);
		} while (BytesRead > 0);
	}

	return Result;
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::ProcessEventMessageQueue()
{
	HRESULT Result = S_OK;
	SPEVENT Event;
	ULONG NumberOfEventsReceived = 0;
	do
	{
		Result = _NativeSynthesizer->WaitForNotifyEvent(500);
		if (Result == S_FALSE)
		{
			break;
		}

		if (SUCCEEDED(Result = _NativeSynthesizer->GetEvents(1, &Event, &NumberOfEventsReceived)))
		{
			switch (Event.eEventId)
			{
			case SPEVENTENUM::SPEI_START_INPUT_STREAM:
			{
				StateChanged(*this, StateChangedEventArgs(u8"PROMPT", SynthesizerState::Ready, SynthesizerState::Speaking));
				SpeakStarted(*this, SpeakStartedEventArgs(u8"PROMPT"));
				break;
			}
			case SPEVENTENUM::SPEI_END_INPUT_STREAM:
			{
				SpeakCompleted(*this, SpeakCompletedEventArgs(u8"PROMPT"));
				StateChanged(*this, StateChangedEventArgs(u8"PROMPT", SynthesizerState::Speaking, SynthesizerState::Ready));
				break;
			}
			case SPEVENTENUM::SPEI_VOICE_CHANGE:
			{
				VoiceChanged(*this, VoiceChangeEventArgs(u8"PROMPT", VoiceInfo((ISpObjectToken*)Event.lParam, false)));
				break;
			}
			case SPEVENTENUM::SPEI_TTS_BOOKMARK:
			{
				wchar_t* BookmarkValue = (wchar_t*)Event.lParam;
				BookmarkReached(*this, BookmarkReachedEventArgs(u8"PROMPT", Event.ullAudioStreamOffset,
					_WindowsEncoding.GetString((Elysium::Core::byte*)BookmarkValue, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetSize(BookmarkValue))));
				break;
			}
			case SPEVENTENUM::SPEI_WORD_BOUNDARY:
			{
				SpeakProgress(*this, SpeakProgressEventArgs(u8"PROMPT", Event.ullAudioStreamOffset, Event.wParam, Event.lParam));
				break;
			}
			case SPEVENTENUM::SPEI_PHONEME:
			{
				wchar_t CurrentPhoneme = LOWORD(Event.lParam);
				wchar_t NextPhoneme = LOWORD(Event.wParam);
				/*
				const Elysium::Core::String bla2 = _WindowsEncoding.GetString((Elysium::Core::byte*)&CurrentPhoneme, 1);
				const Elysium::Core::String bla1 = _WindowsEncoding.GetString((Elysium::Core::byte*)&CurrentPhoneme, 1);
				*/
				PhonemeReached(*this, PhonemeReachedEventArgs(u8"PROMPT", Event.ullAudioStreamOffset, HIWORD(Event.wParam),
					(SynthesizerEmphasis)HIWORD(Event.lParam)));
				break;
			}
			case SPEVENTENUM::SPEI_VISEME:
			{
				VisemeReached(*this, VisemeReachedEventArgs(u8"PROMPT", Event.ullAudioStreamOffset, HIWORD(Event.wParam),
					(SynthesizerEmphasis)HIWORD(Event.lParam), LOWORD(Event.lParam), LOWORD(Event.wParam)));
				break;
			}
			default:
				break;
			}
			SpClearEvent(&Event);
		}
	} while (true);
}
#endif
