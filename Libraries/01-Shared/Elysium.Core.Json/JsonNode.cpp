#include "JsonNode.hpp"

const Elysium::Core::Json::JsonNode * Elysium::Core::Json::JsonNode::GetParentNode() const
{
	return _ParentNode;
}

Elysium::Core::Json::JsonNode::JsonNode()
	: _ParentNode(nullptr)
{
}
