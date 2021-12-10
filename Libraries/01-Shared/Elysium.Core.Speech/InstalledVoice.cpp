#include "InstalledVoice.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Synthesis::InstalledVoice::InstalledVoice(const bool Enabled, VoiceInfo&& VoiceInfo)
	: _Enabled(Enabled), _VoiceInfo(Elysium::Core::Template::Functional::Move(VoiceInfo))
{ }

Elysium::Core::Speech::Synthesis::InstalledVoice::InstalledVoice(InstalledVoice&& Right) noexcept
	: _Enabled(false), _VoiceInfo(nullptr)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Speech::Synthesis::InstalledVoice::~InstalledVoice()
{ }

Elysium::Core::Speech::Synthesis::InstalledVoice& Elysium::Core::Speech::Synthesis::InstalledVoice::operator=(InstalledVoice&& Right) noexcept
{
	if (this != &Right)
	{
		_Enabled = Right._Enabled;
		_VoiceInfo = Elysium::Core::Template::Functional::Move(Right._VoiceInfo);

		Right._Enabled = false;
	}
	return *this;
}

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
