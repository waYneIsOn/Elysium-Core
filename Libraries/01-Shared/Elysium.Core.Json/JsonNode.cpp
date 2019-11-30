#include "JsonNode.hpp"

Elysium::Core::Json::JsonNode::~JsonNode()
{
	if (_ParentNode != nullptr)
	{
		_ParentNode->RemoveChild(*this);
	}
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
void Elysium::Core::Json::JsonNode::RemoveChild(JsonNode & Node)
{
	Node._ParentNode = nullptr;
	_Children.Remove(&Node);
}

Elysium::Core::Json::JsonNode::JsonNode()
	: _ParentNode(nullptr), _Children(Collections::Generic::List<const JsonNode*>())
{
}
