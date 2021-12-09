#include "SpeechSynthesizer.hpp"

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
	return VoiceInfo();
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::SetOutputToDefaultAudioDevice()
{
	throw 1;
}

void Elysium::Core::Speech::Synthesis::SpeechSynthesizer::Speak(const String & TextToSpeak)
{
	HRESULT Result = _NativeVoice->Speak(L"Look at you, hacker: a pathetic creature of meat and bone, panting and sweating as you run through my corridors. How can you challenge a perfect immortal machine?", 0, nullptr);
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
