#include "SpeechDetectedEventArgs.hpp"

Elysium::Core::Speech::Recognition::SpeechDetectedEventArgs::SpeechDetectedEventArgs(const Elysium::Core::TimeSpan AudioPosition)
	: Elysium::Core::EventArgs(),
	_AudioPosition(AudioPosition)
{ }

Elysium::Core::Speech::Recognition::SpeechDetectedEventArgs::~SpeechDetectedEventArgs()
{ }

const Elysium::Core::TimeSpan& Elysium::Core::Speech::Recognition::SpeechDetectedEventArgs::GetAudioPosition() const
{
	return _AudioPosition;
}
