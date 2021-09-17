#include "HuffmanNode.hpp"

Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::HuffmanNode(const Elysium::Core::byte Symbol)
	: _Symbol(Symbol), _Left(nullptr), _Right(nullptr)
{ }
Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::~HuffmanNode()
{
	if (_Left != nullptr)
	{
		delete _Left;
		_Left = nullptr;
	}
	if (_Right != nullptr)
	{
		delete _Right;
		_Right = nullptr;
	}
}

const Elysium::Core::byte Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::GetSymbol() const
{
	return _Symbol;
}

const Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode* Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::GetLeft() const
{
	return _Left;
}

const Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode* Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::GetRight() const
{
	return _Right;
}

const bool Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::GetIsLeaf() const
{
	return _Left == nullptr || _Right == nullptr;
}

void Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::SetSymbol(const Elysium::Core::byte Value)
{
	_Symbol = Value;
}

Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode* Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::SetLeft(const Elysium::Core::byte Symbol)
{
	if (_Left != nullptr)
	{
		_Left->_Symbol = Symbol;
		return _Left;
	}

	_Left = new HuffmanNode(Symbol);
	return _Left;
}

Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode* Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::SetRight(const Elysium::Core::byte Symbol)
{
	if (_Right != nullptr)
	{
		_Right->_Symbol = Symbol;
		return _Right;
	}

	_Right = new HuffmanNode(Symbol);
	return _Right;
}

const Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode* Elysium::Core::IO::Compression::HuffmanCoding::HuffmanNode::Find(const Elysium::Core::byte Symbol) const
{
	if (Symbol == _Symbol)
	{
		return this;
	}

	if (_Left != nullptr)
	{
		return _Left->Find(Symbol);
	}

	if (_Right != nullptr)
	{
		return _Right->Find(Symbol);
	}
	
	return nullptr;
}
