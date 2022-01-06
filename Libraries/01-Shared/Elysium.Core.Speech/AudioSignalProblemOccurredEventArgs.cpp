#include "AudioSignalProblemOccurredEventArgs.hpp"

Elysium::Core::Speech::Recognition::AudioSignalProblemOccurredEventArgs::AudioSignalProblemOccurredEventArgs(const AudioSignalProblem Problem, const Elysium::Core::uint32_t AudioLevel)
	: Elysium::Core::EventArgs(),
	_AudioSignalProblem(Problem), _AudioLevel(AudioLevel)
{ }

Elysium::Core::Speech::Recognition::AudioSignalProblemOccurredEventArgs::~AudioSignalProblemOccurredEventArgs()
{ }

const Elysium::Core::Speech::Recognition::AudioSignalProblem Elysium::Core::Speech::Recognition::AudioSignalProblemOccurredEventArgs::GetAudioSignalProblem() const
{
	return _AudioSignalProblem;
}

const Elysium::Core::uint32_t Elysium::Core::Speech::Recognition::AudioSignalProblemOccurredEventArgs::GetAudioLevel() const
{
	return _AudioLevel;
}
