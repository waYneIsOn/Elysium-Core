#include "SpeechSynthesizer.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Elysium.Core.Template/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template//CharacterTraits.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef SPHelper_h
#include <sphelper.h>
#endif
#endif

Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeechSynthesizer()
#if defined ELYSIUM_CORE_OS_WINDOWS
	: _NativeSynthesizer(Initialize())
#endif
{ }

Elysium::Core::Speech::Synthesis::SpeechSynthesizer::~SpeechSynthesizer()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	if (_NativeSynthesizer != nullptr)
	{
		_NativeSynthesizer->Release();
		_NativeSynthesizer = nullptr;
	}

	CoUninitialize();
#endif
}

const Elysium::Core::int32_t Elysium::Core::Speech::Synthesis::SpeechSynthesizer::GetRate() const
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

const Elysium::Core::int32_t Elysium::Core::Speech::Synthesis::SpeechSynthesizer::GetVolume() const
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
			if (FAILED(Result = SelectNativeVoice(VoiceToken)))
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
	HRESULT Result = SelectNativeVoice(Info._VoiceToken);
	if (FAILED(Result))
	{	// ToDo: throw specific exception
		throw 1;
	}
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

	HRESULT Result = _NativeSynthesizer->Speak((wchar_t*)&Bytes[0], SPEAKFLAGS::SPF_ASYNC, nullptr);
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

	HRESULT Result = _NativeSynthesizer->Speak((wchar_t*)&Bytes[0], SPEAKFLAGS::SPF_DEFAULT, nullptr);
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

	HRESULT Result = _NativeSynthesizer->Speak((wchar_t*)&Bytes[0], SPEAKFLAGS::SPF_IS_XML, nullptr);
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

	HRESULT Result = _NativeSynthesizer->Speak((wchar_t*)&Bytes[0], SPEAKFLAGS::SPF_IS_XML | SPEAKFLAGS::SPF_ASYNC, nullptr);
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

#if defined ELYSIUM_CORE_OS_WINDOWS
ISpVoice* Elysium::Core::Speech::Synthesis::SpeechSynthesizer::Initialize()
{
	if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)))
	{	// ToDo
		throw 1;
	}

	ISpVoice* NativeVoice = nullptr;
	HRESULT Result = CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL, IID_ISpVoice, (void**)&NativeVoice);
	if (FAILED(Result))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	return NativeVoice;
}

HRESULT Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SelectNativeVoice(ISpObjectToken* VoiceToken)
{
	return _NativeSynthesizer->SetVoice(VoiceToken);
}
#endif
