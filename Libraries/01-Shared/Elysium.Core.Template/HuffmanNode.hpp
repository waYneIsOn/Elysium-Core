/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "UnsignedInteger.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanTree;

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanNode
	{
		friend class HuffmanTree<S, F>;
	public:
		HuffmanNode(const S Symbol = 0x00, const F Frequency = 0, const bool IsInternalNode = false);

		HuffmanNode(const HuffmanNode& Source) = delete;

		HuffmanNode(HuffmanNode&& Right) noexcept = delete;

		~HuffmanNode();
	public:
		HuffmanNode& operator=(const HuffmanNode& Source) = delete;

		HuffmanNode& operator=(HuffmanNode&& Right) noexcept = delete;
	public:

	private:
		S _Symbol;
		F _Frequency;
		bool _IsInternalNode;

		HuffmanNode* _Left;
		HuffmanNode* _Right;
	};

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanNode<S, F>::HuffmanNode(const S Symbol, const F Frequency, const bool IsInternalNode)
		: _Symbol(Symbol), _Frequency(Frequency), _IsInternalNode(IsInternalNode), _Left(nullptr), _Right(nullptr)
	{ }

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanNode<S, F>::~HuffmanNode()
	{ }
}
#endif
