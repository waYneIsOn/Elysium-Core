#include "VisemeReachedEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Synthesis::VisemeReachedEventArgs::VisemeReachedEventArgs(String&& Prompt, const Elysium::Core::uint64_t AudioPositionTicks, const Elysium::Core::uint64_t DurationMilliseconds, const SynthesizerEmphasis Emphasis, const Elysium::Core::uint16_t Viseme, const Elysium::Core::uint16_t NextViseme)
	: Elysium::Core::Speech::Synthesis::PromptEventArgs(Elysium::Core::Template::Functional::Move(Prompt)),
	_AudioPosition(AudioPositionTicks), _Duration(DurationMilliseconds * 10000), _Emphasis(Emphasis), _Viseme(Viseme), _NextViseme(NextViseme)
{ }

Elysium::Core::Speech::Synthesis::VisemeReachedEventArgs::~VisemeReachedEventArgs()
{ }

const Elysium::Core::TimeSpan& Elysium::Core::Speech::Synthesis::VisemeReachedEventArgs::GetAudioPosition() const
{
	return _AudioPosition;
}

const Elysium::Core::TimeSpan& Elysium::Core::Speech::Synthesis::VisemeReachedEventArgs::GetDuration() const
{
	return _Duration;
}

const Elysium::Core::Speech::Synthesis::SynthesizerEmphasis Elysium::Core::Speech::Synthesis::VisemeReachedEventArgs::GetEmphasis() const
{
	return _Emphasis;
}

const Elysium::Core::uint16_t Elysium::Core::Speech::Synthesis::VisemeReachedEventArgs::GetViseme() const
{
	return _Viseme;
}

const Elysium::Core::uint16_t Elysium::Core::Speech::Synthesis::VisemeReachedEventArgs::GetNextViseme() const
{
	return _NextViseme;
}
