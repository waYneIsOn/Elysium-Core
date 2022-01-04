#include "RecognitionResult.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Recognition::RecognitionResult::RecognitionResult(Elysium::Core::Utf8String&& Text)
	: Elysium::Core::Speech::Recognition::RecognizedPhrase(Elysium::Core::Template::Functional::Move(Text))
{ }

Elysium::Core::Speech::Recognition::RecognitionResult::RecognitionResult(RecognitionResult&& Right) noexcept
	: Elysium::Core::Speech::Recognition::RecognizedPhrase(Elysium::Core::Template::Functional::Move(u8""))
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Speech::Recognition::RecognitionResult::~RecognitionResult()
{ }

Elysium::Core::Speech::Recognition::RecognitionResult& Elysium::Core::Speech::Recognition::RecognitionResult::operator=(RecognitionResult && Right) noexcept
{
	if (this != &Right)
	{
		Elysium::Core::Speech::Recognition::RecognizedPhrase::operator=(Elysium::Core::Template::Functional::Move(Right));
	}
	return *this;
}
