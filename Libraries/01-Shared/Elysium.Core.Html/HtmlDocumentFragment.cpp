#include "HtmlDocumentFragment.hpp"

Elysium::Core::Html::HtmlDocumentFragment::HtmlDocumentFragment()
	: Elysium::Core::Html::HtmlNode()
{
}
Elysium::Core::Html::HtmlDocumentFragment::~HtmlDocumentFragment()
{
}

const Elysium::Core::String & Elysium::Core::Html::HtmlDocumentFragment::GetName() const
{
	static const Elysium::Core::String Name = u"#document fragment";
	return Name;
}
const Elysium::Core::Html::HtmlNodeType Elysium::Core::Html::HtmlDocumentFragment::GetNodeType() const
{
	return HtmlNodeType::DocumentFragment;
}
