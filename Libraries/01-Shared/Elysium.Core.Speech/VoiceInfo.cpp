#include "VoiceInfo.hpp"

Elysium::Core::Speech::Synthesis::VoiceInfo::VoiceInfo()
	: _Age(VoiceAge::NotSet), _Gender(VoiceGender::NotSet)
{ }

Elysium::Core::Speech::Synthesis::VoiceInfo::~VoiceInfo()
{ }

const Elysium::Core::Speech::Synthesis::VoiceAge Elysium::Core::Speech::Synthesis::VoiceInfo::GetAge() const
{
	return _Age;
}

const Elysium::Core::Speech::Synthesis::VoiceGender Elysium::Core::Speech::Synthesis::VoiceInfo::GetGender() const
{
	return _Gender;
}

const Elysium::Core::String Elysium::Core::Speech::Synthesis::VoiceInfo::GetId() const
{
	return String();
}

const Elysium::Core::String  Elysium::Core::Speech::Synthesis::VoiceInfo::GetName() const
{
	return String();
}
