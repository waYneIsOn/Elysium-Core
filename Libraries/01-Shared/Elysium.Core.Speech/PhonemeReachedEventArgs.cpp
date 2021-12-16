#include "PhonemeReachedEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Synthesis::PhonemeReachedEventArgs::PhonemeReachedEventArgs(String&& Prompt, const Elysium::Core::uint64_t AudioPositionTicks, const Elysium::Core::uint64_t DurationMilliseconds, const SynthesizerEmphasis Emphasis)
	: Elysium::Core::Speech::Synthesis::PromptEventArgs(Elysium::Core::Template::Functional::Move(Prompt)),
	_AudioPosition(AudioPositionTicks), _Duration(DurationMilliseconds * 10000), _Emphasis(Emphasis)
{ }

Elysium::Core::Speech::Synthesis::PhonemeReachedEventArgs::~PhonemeReachedEventArgs()
{ }

const Elysium::Core::TimeSpan& Elysium::Core::Speech::Synthesis::PhonemeReachedEventArgs::GetAudioPosition() const
{
	return _AudioPosition;
}

const Elysium::Core::TimeSpan& Elysium::Core::Speech::Synthesis::PhonemeReachedEventArgs::GetDuration() const
{
	return _Duration;
}

const Elysium::Core::Speech::Synthesis::SynthesizerEmphasis Elysium::Core::Speech::Synthesis::PhonemeReachedEventArgs::GetEmphasis() const
{
	return _Emphasis;
}
