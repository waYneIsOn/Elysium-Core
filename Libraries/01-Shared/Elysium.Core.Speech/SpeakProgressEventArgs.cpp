#include "SpeakProgressEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Synthesis::SpeakProgressEventArgs::SpeakProgressEventArgs(Elysium::Core::Utf8String&& Prompt, const Elysium::Core::uint64_t AudioPositionTicks, const Elysium::Core::uint64_t CharacterCount, const Elysium::Core::uint64_t CharacterPosition)
	: Elysium::Core::Speech::Synthesis::PromptEventArgs(Elysium::Core::Template::Functional::Move(Prompt)),
	_AudioPosition(AudioPositionTicks), _CharacterCount(CharacterCount), _CharacterPosition(CharacterPosition)
{ }

Elysium::Core::Speech::Synthesis::SpeakProgressEventArgs::~SpeakProgressEventArgs()
{ }

const Elysium::Core::TimeSpan& Elysium::Core::Speech::Synthesis::SpeakProgressEventArgs::GetAudioPosition() const
{
	return _AudioPosition;
}

const Elysium::Core::uint64_t Elysium::Core::Speech::Synthesis::SpeakProgressEventArgs::GetCharacterCount() const
{
	return _CharacterCount;
}

const Elysium::Core::uint64_t Elysium::Core::Speech::Synthesis::SpeakProgressEventArgs::GetCharacterPosition() const
{
	return _CharacterPosition;
}
