#include "InstalledVoice.hpp"

Elysium::Core::Speech::Synthesis::InstalledVoice::InstalledVoice(const bool Enabled, const VoiceInfo& VoiceInfo)
	: _Enabled(Enabled), _VoiceInfo(VoiceInfo)
{ }

Elysium::Core::Speech::Synthesis::InstalledVoice::~InstalledVoice()
{ }

const bool Elysium::Core::Speech::Synthesis::InstalledVoice::GetEnabled() const
{
	return _Enabled;
}

void Elysium::Core::Speech::Synthesis::InstalledVoice::SetEnabled(const bool Value)
{
	_Enabled = Value;
}
