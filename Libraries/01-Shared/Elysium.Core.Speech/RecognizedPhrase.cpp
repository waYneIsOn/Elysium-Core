#include "RecognizedPhrase.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Speech::Recognition::RecognizedPhrase::RecognizedPhrase(Elysium::Core::Utf8String&& Text)
	: _Text(Elysium::Core::Template::Functional::Move(Text))
{ }

Elysium::Core::Speech::Recognition::RecognizedPhrase::RecognizedPhrase(RecognizedPhrase&& Right) noexcept
	: _Text()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Speech::Recognition::RecognizedPhrase::~RecognizedPhrase()
{ }

Elysium::Core::Speech::Recognition::RecognizedPhrase& Elysium::Core::Speech::Recognition::RecognizedPhrase::operator=(RecognizedPhrase&& Right) noexcept
{
	if (this != &Right)
	{
		_Text = Elysium::Core::Template::Functional::Move(Right._Text);
	}
	return *this;
}

const Elysium::Core::Utf8String& Elysium::Core::Speech::Recognition::RecognizedPhrase::GetText() const
{
	return _Text;
}
