#include "HtmlElement.hpp"

Elysium::Core::Html::HtmlElement::HtmlElement(const HtmlNodeType NodeType, const Utf8String& Value)
	: Elysium::Core::Html::HtmlNode(),
	_Name(NodeType == HtmlNodeType::Text ? u8"#Text" :
		NodeType == HtmlNodeType::CDATASection ? u8"#CDATASection" :
		NodeType == HtmlNodeType::Comment ? u8"#Comment" : u8""), _Type(NodeType), _Value(Value)
{ }

Elysium::Core::Html::HtmlElement::HtmlElement(const Utf8String& Name, const HtmlNodeType NodeType, const Utf8String& Value)
	: Elysium::Core::Html::HtmlNode(),
	_Name(Name), _Type(NodeType), _Value(Value)
{ }

Elysium::Core::Html::HtmlElement::~HtmlElement()
{ }

const Elysium::Core::Utf8String& Elysium::Core::Html::HtmlElement::GetName() const
{
	return _Name;
}

const Elysium::Core::Html::HtmlNodeType Elysium::Core::Html::HtmlElement::GetNodeType() const
{
	return _Type;
}

const Elysium::Core::Utf8String& Elysium::Core::Html::HtmlElement::GetValue() const
{
	return _Value;
}
