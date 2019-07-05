#include "HuffmanNode.hpp"

Elysium::Core::IO::Compression::HuffmanNode::HuffmanNode(HuffmanNode * Parent, char Char)
	: _Parent(Parent), _Char(Char), _Children(nullptr), _Frequency(0)
{
}
Elysium::Core::IO::Compression::HuffmanNode::~HuffmanNode()
{
}
