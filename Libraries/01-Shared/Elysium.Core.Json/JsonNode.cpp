#include "JsonNode.hpp"

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

Elysium::Core::Json::JsonNode::~JsonNode()
{
	if (_ParentNode != nullptr)
	{
		_ParentNode->RemoveChild(*this);
	}
	for (size_t i = 0; i < _Children.GetCount(); i++)
	{
		_Children.operator[](i)->_ParentNode = nullptr;
	}
	_Children.Clear();
}

const Elysium::Core::Json::JsonNode * Elysium::Core::Json::JsonNode::GetParentNode() const
{
	return _ParentNode;
}

void Elysium::Core::Json::JsonNode::AddChild(JsonNode & Node)
{
	Node._ParentNode = this;
	_Children.Add(&Node);
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
