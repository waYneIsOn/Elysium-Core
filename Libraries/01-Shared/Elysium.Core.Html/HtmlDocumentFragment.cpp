#include "HtmlDocumentFragment.hpp"

Elysium::Core::Html::HtmlDocumentFragment::HtmlDocumentFragment()
	: Elysium::Core::Html::HtmlNode()
{ }

Elysium::Core::Html::HtmlDocumentFragment::~HtmlDocumentFragment()
{ }

const Elysium::Core::Utf8String & Elysium::Core::Html::HtmlDocumentFragment::GetName() const
{
	static const Elysium::Core::Utf8String Name = u8"#document fragment";
	return Name;
}

const Elysium::Core::Html::HtmlNodeType Elysium::Core::Html::HtmlDocumentFragment::GetNodeType() const
{
	return HtmlNodeType::DocumentFragment;
}
