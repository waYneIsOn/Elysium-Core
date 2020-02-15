#include "HtmlElement.hpp"

Elysium::Core::Html::HtmlElement::~HtmlElement()
{ }

const Elysium::Core::String & Elysium::Core::Html::HtmlElement::GetName() const
{
	return _Name;
}
const Elysium::Core::Html::HtmlNodeType Elysium::Core::Html::HtmlElement::GetNodeType() const
{
	return _Type;
}
const Elysium::Core::String & Elysium::Core::Html::HtmlElement::GetValue() const
{
	return _Value;
}

Elysium::Core::Html::HtmlElement::HtmlElement(const HtmlNodeType NodeType, const String & Value)
	: Elysium::Core::Html::HtmlNode(),
	_Name(NodeType == HtmlNodeType::Text ? u"#Text" : 
		NodeType == HtmlNodeType::CDATASection ? u"#CDATASection" : 
		NodeType == HtmlNodeType::Comment ? u"#Comment" : u""), _Type(NodeType), _Value(Value)
{ }
Elysium::Core::Html::HtmlElement::HtmlElement(const String & Name, const HtmlNodeType NodeType, const String& Value)
	: Elysium::Core::Html::HtmlNode(),
	_Name(Name), _Type(NodeType), _Value(Value)
{ }
