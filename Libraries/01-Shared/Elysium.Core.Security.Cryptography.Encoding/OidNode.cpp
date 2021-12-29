#include "OidNode.hpp"

Elysium::Core::Security::Cryptography::OidNode::OidNode(const Elysium::Core::uint32_t Value, const Elysium::Core::Utf8String Name)
	: _Value(Value), _Name(Name)
{ }

Elysium::Core::Security::Cryptography::OidNode::~OidNode()
{ }
