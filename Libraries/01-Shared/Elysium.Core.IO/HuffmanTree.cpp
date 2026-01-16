#include "HuffmanTree.hpp"

Elysium::Core::IO::Compression::HuffmanCoding::HuffmanTree::HuffmanTree()
	: _Root(0x00)
{ }

Elysium::Core::IO::Compression::HuffmanCoding::HuffmanTree::~HuffmanTree()
{ }

Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode& Elysium::Core::IO::Compression::HuffmanCoding::HuffmanTree::GetRootNode()
{
	return _Root;
}

const Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode& Elysium::Core::IO::Compression::HuffmanCoding::HuffmanTree::GetRootNode() const
{
	return _Root;
}
