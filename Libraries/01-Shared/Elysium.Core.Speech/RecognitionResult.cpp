#include "RecognitionResult.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Recognition::RecognitionResult::RecognitionResult()
{ }

Elysium::Core::Speech::Recognition::RecognitionResult::RecognitionResult(RecognitionResult&& Right) noexcept
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Speech::Recognition::RecognitionResult::~RecognitionResult()
{ }

Elysium::Core::Speech::Recognition::RecognitionResult& Elysium::Core::Speech::Recognition::RecognitionResult::operator=(RecognitionResult && Right) noexcept
{
	if (this != &Right)
	{
		// ...
	}
	return *this;
}
