#include "SpeechSynthesizer.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template//CharacterTraits.hpp"
#endif

#ifndef SPHelper_h
#include <sphelper.h>
#endif

Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SpeechSynthesizer()
	: _NativeVoice(Initialize())
{ }

Elysium::Core::Speech::Synthesis::SpeechSynthesizer::~SpeechSynthesizer()
{
	if (_NativeVoice != nullptr)
	{
		_NativeVoice->Release();
		_NativeVoice = nullptr;
	}

	CoUninitialize();
}

const Elysium::Core::Speech::Synthesis::VoiceInfo Elysium::Core::Speech::Synthesis::SpeechSynthesizer::GetVoice() const
{
	HRESULT Result = S_OK;

	ISpObjectToken* VoiceToken;
	if (FAILED(Result = _NativeVoice->GetVoice(&VoiceToken)))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	return VoiceInfo(VoiceToken);
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::Speak(const String & TextToSpeak)
{
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = _WindowsEncoding.GetBytes(&TextToSpeak[0], TextToSpeak.GetLength() + sizeof(char8_t));

	HRESULT Result = _NativeVoice->Speak((wchar_t*)&Bytes[0], 0, nullptr);
	if (FAILED(Result))
	{	// ToDo: throw specific excetpion
		throw 1;
	}
}

ISpVoice* Elysium::Core::Speech::Synthesis::SpeechSynthesizer::Initialize()
{
	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
	{
		throw 1;
	}

	ISpVoice* NativeVoice = NULL;
	HRESULT Result = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&NativeVoice);
	if (FAILED(Result))
	{	// ToDo: throw specific excetpion
		throw 1;
	}

	return NativeVoice;
}
