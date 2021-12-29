#include "StateChangedEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Synthesis::StateChangedEventArgs::StateChangedEventArgs(Elysium::Core::Utf8String&& Prompt, const SynthesizerState PreviousState, const SynthesizerState State)
	: Elysium::Core::Speech::Synthesis::PromptEventArgs(Elysium::Core::Template::Functional::Move(Prompt)),
	_PreviousState(PreviousState), _State(State)
{ }

Elysium::Core::Speech::Synthesis::StateChangedEventArgs::~StateChangedEventArgs()
{ }

const Elysium::Core::Speech::Synthesis::SynthesizerState Elysium::Core::Speech::Synthesis::StateChangedEventArgs::GetPreviousState() const
{
	return _PreviousState;
}

const Elysium::Core::Speech::Synthesis::SynthesizerState Elysium::Core::Speech::Synthesis::StateChangedEventArgs::GetState() const
{
	return _State;
}
