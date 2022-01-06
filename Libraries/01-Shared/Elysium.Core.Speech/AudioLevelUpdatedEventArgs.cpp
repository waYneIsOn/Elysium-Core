#include "AudioLevelUpdatedEventArgs.hpp"

Elysium::Core::Speech::Recognition::AudioLevelUpdatedEventArgs::AudioLevelUpdatedEventArgs(const Elysium::Core::uint32_t AudioLevel)
	: Elysium::Core::EventArgs(),
	_AudioLevel(AudioLevel)
{ }

Elysium::Core::Speech::Recognition::AudioLevelUpdatedEventArgs::~AudioLevelUpdatedEventArgs()
{ }

const Elysium::Core::uint32_t Elysium::Core::Speech::Recognition::AudioLevelUpdatedEventArgs::GetAudioLevel() const
{
	return _AudioLevel;
}
