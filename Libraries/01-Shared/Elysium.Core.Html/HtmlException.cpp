#include "HtmlException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Html::HtmlException::HtmlException()
	: Elysium::Core::Exception()
{ }

Elysium::Core::Html::HtmlException::HtmlException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium
::Core::Html::HtmlException::~HtmlException()
{ }
