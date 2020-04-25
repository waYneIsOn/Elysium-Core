#include "HtmlException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Html::HtmlException::HtmlException()
	: Elysium::Core::Exception()
{ }
Elysium::Core::Html::HtmlException::HtmlException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::Html::HtmlException::~HtmlException()
{ }
