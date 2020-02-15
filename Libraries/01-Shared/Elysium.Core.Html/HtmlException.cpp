#include "HtmlException.hpp"

Elysium::Core::Html::HtmlException::HtmlException()
	: Elysium::Core::Exception()
{
}
Elysium::Core::Html::HtmlException::HtmlException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::Html::HtmlException::~HtmlException()
{
}
