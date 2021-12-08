#include "InstalledVoice.hpp"

Elysium::Core::Speech::Synthesis::InstalledVoice::InstalledVoice()
	: _Enabled(false), _VoiceInfo()
{ }

Elysium::Core::Speech::Synthesis::InstalledVoice::~InstalledVoice()
{ }

const bool Elysium::Core::Speech::Synthesis::InstalledVoice::GetEnabled() const
{
	return _Enabled;
}

const Elysium::Core::Speech::Synthesis::VoiceInfo& Elysium::Core::Speech::Synthesis::InstalledVoice::GetVoiceInfo() const
{
	return _VoiceInfo;
}

void Elysium::Core::Speech::Synthesis::InstalledVoice::SetEnabled(const bool Value)
{
	_Enabled = Value;
}
