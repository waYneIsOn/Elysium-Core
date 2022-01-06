#include "RecognitionEventArgs.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Recognition::RecognitionEventArgs::RecognitionEventArgs(RecognitionResult&& Result)
	: Elysium::Core::EventArgs(),
	_Result(Elysium::Core::Template::Functional::Move(Result))
{ }

Elysium::Core::Speech::Recognition::RecognitionEventArgs::~RecognitionEventArgs()
{ }

const Elysium::Core::Speech::Recognition::RecognitionResult& Elysium::Core::Speech::Recognition::RecognitionEventArgs::GetResult() const
{
	return _Result;
}
