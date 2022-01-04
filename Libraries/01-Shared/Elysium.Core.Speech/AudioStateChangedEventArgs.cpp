#include "AudioStateChangedEventArgs.hpp"

Elysium::Core::Speech::Recognition::AudioStateChangedEventArgs::AudioStateChangedEventArgs(const AudioFormat::AudioState AudioState)
	: Elysium::Core::EventArgs(),	
	_AudioState(AudioState)
{ }

Elysium::Core::Speech::Recognition::AudioStateChangedEventArgs::~AudioStateChangedEventArgs()
{ }

const Elysium::Core::Speech::AudioFormat::AudioState& Elysium::Core::Speech::Recognition::AudioStateChangedEventArgs::GetAudioState() const
{
	return _AudioState;
}
