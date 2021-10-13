#include "HtmlNode.hpp"

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "../Elysium.Core/IndexOutOfRangeException.hpp"
#endif


Elysium::Core::Html::HtmlNode::~HtmlNode()
{
	for (Elysium::Core::size i = 0; i < _Children.GetCount(); i++)
	{
		delete _Children.operator[](i);
	}
	_Children.Clear();

	if (_ParentNode != nullptr)
	{
		_ParentNode->RemoveChild(*this);
	}
}

const Elysium::Core::Html::HtmlNode * Elysium::Core::Html::HtmlNode::GetParentNode() const
{
	return _ParentNode;
}

const Elysium::Core::size Elysium::Core::Html::HtmlNode::GetChildCount()
{
	return _Children.GetCount();
}

Elysium::Core::Html::HtmlNode & Elysium::Core::Html::HtmlNode::GetChild(Elysium::Core::size Index)
{
	if (Index > _Children.GetCount())
	{
		throw Elysium::Core::IndexOutOfRangeException();
	}
	return *_Children[Index];
}
void Elysium::Core::Html::HtmlNode::RemoveChild(HtmlNode & Node)
{
	Node._ParentNode = nullptr;
	_Children.Remove(&Node);
}

Elysium::Core::Html::HtmlNode::HtmlNode()
	: _ParentNode(nullptr), _Children(Collections::Template::List<HtmlNode*>())
{ }

void Elysium::Core::Html::HtmlNode::AddChild(HtmlNode & Node)
{
	Node._ParentNode = this;
	_Children.Add(&Node);
}
