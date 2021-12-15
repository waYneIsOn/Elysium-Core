#include "PhonemeReachedEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Synthesis::PhonemeReachedEventArgs::PhonemeReachedEventArgs(String&& Prompt)
	: Elysium::Core::Speech::Synthesis::PromptEventArgs(Elysium::Core::Template::Functional::Move(Prompt))
{ }

Elysium::Core::Speech::Synthesis::PhonemeReachedEventArgs::~PhonemeReachedEventArgs()
{ }
