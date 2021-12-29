#include "HtmlAttribute.hpp"

Elysium::Core::Html::HtmlAttribute::HtmlAttribute(const Elysium::Core::Utf8String& Name, const Elysium::Core::Utf8String& Value)
	: Elysium::Core::Html::HtmlNode(),
	_Name(Name), _Value(Value)
{ }

Elysium::Core::Html::HtmlAttribute::~HtmlAttribute()
{ }

const Elysium::Core::Utf8String & Elysium::Core::Html::HtmlAttribute::GetName() const
{
	return _Name;
}

const Elysium::Core::Html::HtmlNodeType Elysium::Core::Html::HtmlAttribute::GetNodeType() const
{
	return HtmlNodeType::Attribute;
}

const Elysium::Core::Utf8String & Elysium::Core::Html::HtmlAttribute::GetValue() const
{
	return _Value;
}
