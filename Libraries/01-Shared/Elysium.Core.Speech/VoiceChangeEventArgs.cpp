#include "VoiceChangeEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Synthesis::VoiceChangeEventArgs::VoiceChangeEventArgs(Elysium::Core::Utf8String&& Prompt, VoiceInfo&& Voice)
	: Elysium::Core::Speech::Synthesis::PromptEventArgs(Elysium::Core::Template::Functional::Move(Prompt)),
	_Voice(Elysium::Core::Template::Functional::Move(Voice))
{ }

Elysium::Core::Speech::Synthesis::VoiceChangeEventArgs::~VoiceChangeEventArgs()
{ }

const Elysium::Core::Speech::Synthesis::VoiceInfo& Elysium::Core::Speech::Synthesis::VoiceChangeEventArgs::GetVoice() const
{
	return _Voice;
}
