#include "JsonNode.hpp"

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "../Elysium.Core/IndexOutOfRangeException.hpp"
#endif

Elysium::Core::Json::JsonNode::~JsonNode()
{
	for (size_t i = 0; i < _Children.GetCount(); i++)
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

const size_t Elysium::Core::Json::JsonNode::GetChildCount()
{
	return _Children.GetCount();
}

Elysium::Core::Json::JsonNode & Elysium::Core::Json::JsonNode::GetChild(size_t Index)
{
	if (Index > _Children.GetCount())
	{
		throw Elysium::Core::IndexOutOfRangeException();
	}
	return *_Children[Index];
}
void Elysium::Core::Json::JsonNode::RemoveChild(JsonNode & Node)
{
	Node._ParentNode = nullptr;
	_Children.Remove(&Node);
}

Elysium::Core::Json::JsonNode::JsonNode()
	: _ParentNode(nullptr), _Children(Collections::Template::List<JsonNode*>())
{
}

void Elysium::Core::Json::JsonNode::AddChild(JsonNode & Node)
{
	Node._ParentNode = this;
	_Children.Add(&Node);
}
