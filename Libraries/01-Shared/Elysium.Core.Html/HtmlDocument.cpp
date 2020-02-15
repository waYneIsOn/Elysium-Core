#include "HtmlDocument.hpp"

Elysium::Core::Html::HtmlDocument::HtmlDocument()
	: Elysium::Core::Html::HtmlNode(),
	_RootNode(HtmlElement(u"html", HtmlNodeType::Element, u""))
{
}
Elysium::Core::Html::HtmlDocument::~HtmlDocument()
{
}

const Elysium::Core::String & Elysium::Core::Html::HtmlDocument::GetName() const
{
	static const Elysium::Core::String Name = u"#document";
	return Name;
}
const Elysium::Core::Html::HtmlNodeType Elysium::Core::Html::HtmlDocument::GetNodeType() const
{
	return HtmlNodeType::Document;
}
Elysium::Core::Html::HtmlElement & Elysium::Core::Html::HtmlDocument::GetRootNode()
{
	return _RootNode;
}
