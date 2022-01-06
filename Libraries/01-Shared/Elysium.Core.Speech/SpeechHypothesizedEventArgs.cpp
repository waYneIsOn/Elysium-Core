#include "SpeechHypothesizedEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Recognition::SpeechHypothesizedEventArgs::SpeechHypothesizedEventArgs(RecognitionResult&& Result)
	: Elysium::Core::Speech::Recognition::RecognitionEventArgs(Elysium::Core::Template::Functional::Move(Result))
{ }

Elysium::Core::Speech::Recognition::SpeechHypothesizedEventArgs::~SpeechHypothesizedEventArgs()
{ }
