#include "PromptEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Synthesis::PromptEventArgs::PromptEventArgs(String&& Prompt)
	: _Prompt(Elysium::Core::Template::Functional::Move(Prompt))
{ }

Elysium::Core::Speech::Synthesis::PromptEventArgs::~PromptEventArgs()
{ }

const Elysium::Core::String& Elysium::Core::Speech::Synthesis::PromptEventArgs::GetPrompt() const
{
	return _Prompt;
}
