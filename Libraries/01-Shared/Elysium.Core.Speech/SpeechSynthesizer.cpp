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

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef SPHelper_h
#include <sphelper.h>
#endif
#endif

Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeechSynthesizer()
#if defined ELYSIUM_CORE_OS_WINDOWS
	: _NativeSynthesizer(InitializeNativeSynthesizer()), _NativeMemoryStream(InitializeNativeStream()), _TargetStream(nullptr)
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
	{	// ToDo: throw specific exception
		throw 1;
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
	{	// ToDo: throw specific excetpion
		throw 1;
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
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	return VoiceInfo(VoiceToken);
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
	{	// ToDo: throw specific exception
		throw 1;
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
	{	// ToDo: throw specific exception
		throw 1;
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
	{	// ToDo: throw specific exception
		throw 1;
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
	{	// ToDo: throw specific exception
		throw 1;
	}

	IEnumSpObjectTokens* VoiceEnumerationToken;
	if (FAILED(Result = CategoryToken->EnumTokens(nullptr, nullptr, &VoiceEnumerationToken)))
	{	
		CategoryToken->Release();
		
		// ToDo: throw specific exception
		throw 1;
	}

	ULONG NumberOfInstalledVoices;
	if (FAILED(Result = VoiceEnumerationToken->GetCount(&NumberOfInstalledVoices)))
	{
		VoiceEnumerationToken->Release();
		CategoryToken->Release();
		
		// ToDo: throw specific exception
		throw 1;
	}

	Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice> InstalledVoices =
		Elysium::Core::Template::Container::Vector<Elysium::Core::Speech::Synthesis::InstalledVoice>(NumberOfInstalledVoices);
	ISpObjectToken* VoiceToken;
	while (VoiceEnumerationToken->Next(1, &VoiceToken, nullptr) == S_OK)
	{
		InstalledVoices.PushBack(Elysium::Core::Template::Functional::Move(InstalledVoice(false, VoiceInfo(VoiceToken))));
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
	{	// ToDo: throw specific exception
		throw 1;
	}

	IEnumSpObjectTokens* VoiceEnumerationToken;
	if (FAILED(Result = CategoryToken->EnumTokens(nullptr, nullptr, &VoiceEnumerationToken)))
	{	
		CategoryToken->Release();

		// ToDo: throw specific exception
		throw 1;
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
			
			// ToDo: throw specific excetpion
			throw 1;
		}

		wchar_t* NativeValue;
		if (FAILED(Result = AttributesKey->GetStringValue(L"Language", &NativeValue)))
		{
			AttributesKey->Release();
			VoiceEnumerationToken->Release();
			CategoryToken->Release();
			
			// ToDo: throw specific excetpion
			throw 1;
		}

		LocaleIdMatches = false;
		const Elysium::Core::int32_t LocaleId = Elysium::Core::Template::Text::Convert<wchar_t>::ToInt32(NativeValue,
			Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(NativeValue), 16);
		if (LocaleId == Culture.GetLCID())
		{
			InstalledVoices.PushBack(Elysium::Core::Template::Functional::Move(InstalledVoice(false, VoiceInfo(VoiceToken))));
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
	{	// ToDo: throw specific exception
		throw 1;
	}
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::Resume()
{
	HRESULT Result = _NativeSynthesizer->Resume();
	if (FAILED(Result))
	{	// ToDo: throw specific exception
		throw 1;
	}
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
	{	// ToDo: throw specific exception
		throw 1;
}

	IEnumSpObjectTokens* VoiceEnumerationToken;
	if (FAILED(Result = CategoryToken->EnumTokens(nullptr, nullptr, &VoiceEnumerationToken)))
	{	
		CategoryToken->Release();

		// ToDo: throw specific exception
		throw 1;
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
			
			// ToDo: throw specific exception
			throw 1;
		}

		wchar_t* NativeValue;
		if (FAILED(Result = AttributesKey->GetStringValue(L"Name", &NativeValue)))
		{
			AttributesKey->Release();
			VoiceEnumerationToken->Release();
			CategoryToken->Release();
			
			// ToDo: throw specific exception
			throw 1;
		}

		if (Elysium::Core::Template::Text::CharacterTraits<wchar_t>::Compare((wchar_t*)&NameBytes[0], NativeValue, NameBytes.GetLength()) == 0)
		{
			if (FAILED(Result = SetNativeVoice(VoiceToken)))
			{
				CoTaskMemFree(NativeValue);
				AttributesKey->Release();
				VoiceEnumerationToken->Release();
				CategoryToken->Release();

				// ToDo: throw specific exception
				throw 1;
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
	{	// ToDo: throw specific exception
		throw 1;
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
	{	// ToDo: throw specific exception
		throw 1;
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
	{	// ToDo: throw specific exception
		throw 1;
	}

	if (FAILED(Result = _NativeSynthesizer->SetOutput(_NativeMemoryStream, TRUE)))
	{	// ToDo: throw specific exception
		throw 1;
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
	{	// ToDo: throw specific exception
		throw 1;
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
	{	// ToDo: throw specific exception
		throw 1;
	}

	if (FAILED(Result = _NativeSynthesizer->SetOutput(_NativeMemoryStream, TRUE)))
	{	// ToDo: throw specific exception
		throw 1;
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
	{	// ToDo: throw specific excetpion
		throw 1;
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
	{	// ToDo: throw specific excetpion
		throw 1;
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
	{	// ToDo: throw specific excetpion
		throw 1;
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
	{	// ToDo: throw specific excetpion
		throw 1;
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
	HRESULT Result = _NativeSynthesizer->WaitUntilDone(Timeout.GetTotalMilliseconds());
	if (FAILED(Result))
	{	// ToDo: throw specific excetpion
		throw 1;
	}
}

#if defined ELYSIUM_CORE_OS_WINDOWS
ISpVoice* Elysium::Core::Speech::Synthesis::SpeechSynthesizer::InitializeNativeSynthesizer()
{
	if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)))
	{
		return nullptr;
	}

	HRESULT Result = S_OK;

	ISpVoice* NativeSynthesizer = nullptr;
	if (FAILED(Result = CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL, IID_ISpVoice, (void**)&NativeSynthesizer)))
	{
		return nullptr;
	}

	const ULONGLONG Interests = SPFEI(SPEVENTENUM::SPEI_VOICE_CHANGE) | SPFEI(SPEVENTENUM::SPEI_SOUND_END) | SPFEI(SPEVENTENUM::SPEI_SOUND_START)
		| SPFEI(SPEVENTENUM::SPEI_WORD_BOUNDARY) | SPFEI(SPEVENTENUM::SPEI_PHONEME) | SPFEI(SPEVENTENUM::SPEI_VISEME);
	if (FAILED(NativeSynthesizer->SetInterest(Interests, Interests)))
	{
		NativeSynthesizer->Release();
		NativeSynthesizer = nullptr;

		return nullptr;
	}
	
	if (FAILED(Result = NativeSynthesizer->SetNotifyCallbackFunction(&NativeSynthesizerEventCallback, 0, 0)))
	{
		NativeSynthesizer->Release();
		NativeSynthesizer = nullptr;

		return nullptr;
	}
	/*
	ISpNotifySink* NativeNotificationSink = nullptr;
	if (FAILED(Result = NativeSynthesizer->SetNotifySink(NativeNotificationSink)))
	{
		NativeSynthesizer->Release();
		NativeSynthesizer = nullptr;

		return nullptr;
	}
	*/
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
	HRESULT Result = S_OK;
	if (SUCCEEDED(Result = _NativeSynthesizer->SetVoice(VoiceToken)))
	{
		/*
		SPEVENT eventItem = SPEVENT();
		while (_NativeSynthesizer->GetEvents(1, &eventItem, NULL) == S_OK)
		{
			switch (eventItem.eEventId)
			{
			case SPEI_WORD_BOUNDARY:
				break;
			default:
				break;
			}
		}
		SpClearEvent(&eventItem);
		*/
	}

	return Result;
}

HRESULT Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeakNatively(const wchar_t* TextToSpeak, const Elysium::Core::int32_t Flags) noexcept
{
	HRESULT Result = S_OK;

	if (FAILED(Result = _NativeSynthesizer->Speak(TextToSpeak, Flags, nullptr)))
	{
		return Result;
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

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::NativeSynthesizerEventCallback(WPARAM wParam, LPARAM lParam)
{
	bool asdfasdf = false;
}
#endif
