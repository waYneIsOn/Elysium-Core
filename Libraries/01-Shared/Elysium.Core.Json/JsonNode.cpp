#include "JsonNode.hpp"

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "../Elysium.Core/IndexOutOfRangeException.hpp"
#endif

Elysium::Core::Json::JsonNode::~JsonNode()
{
	for (Elysium::Core::size i = 0; i < _Children.GetLength(); i++)
	{
		delete _Children.operator[](i);
	}
	_Children.Clear();

	if (_ParentNode != nullptr)
	{
		_ParentNode->RemoveChild(*this);
	}
}

const Elysium::Core::Json::JsonNode * Elysium::Core::Json::JsonNode::GetParentNode() const
{
	return _ParentNode;
}

const Elysium::Core::size Elysium::Core::Json::JsonNode::GetChildCount()
{
	return _Children.GetLength();
}

Elysium::Core::Json::JsonNode & Elysium::Core::Json::JsonNode::GetChild(Elysium::Core::size Index)
{
	if (Index > _Children.GetLength())
	{
		throw Elysium::Core::IndexOutOfRangeException();
	}
	return *_Children[Index];
}
void Elysium::Core::Json::JsonNode::RemoveChild(JsonNode & Node)
{
	Node._ParentNode = nullptr;
	_Children.Erase(&Node);
}

Elysium::Core::Json::JsonNode::JsonNode()
	: _ParentNode(nullptr), _Children(Elysium::Core::Template::Container::Vector<JsonNode*>())
{ }

void Elysium::Core::Json::JsonNode::AddChild(JsonNode & Node)
{
	Node._ParentNode = this;
	_Children.PushBack(&Node);
}
