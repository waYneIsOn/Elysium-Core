#include "RecognitionEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Recognition::RecognitionEventArgs::RecognitionEventArgs(RecognitionResult&& Result)
	//: _Result(Elysium::Core::Template::Functional::Move(Result))
{ }

Elysium::Core::Speech::Recognition::RecognitionEventArgs::~RecognitionEventArgs()
{ }
