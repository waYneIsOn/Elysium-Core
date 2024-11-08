/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_QUEUE_PRIORITYQUEUE
#include "PriorityQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanTree
	{
	private:
		using Node = HuffmanNode<S, F>;

		using ConstSymbolPointer = const S*;
	public:
		HuffmanTree();

		HuffmanTree(const HuffmanTree& Source) = delete;

		HuffmanTree(HuffmanTree&& Right) noexcept = delete;

		~HuffmanTree();
	public:
		HuffmanTree& operator=(const HuffmanTree& Source) = delete;

		HuffmanTree& operator=(HuffmanTree&& Right) noexcept = delete;
	public:
		static HuffmanTree<S, F> Build(ConstSymbolPointer Input, const Elysium::Core::Template::System::size Length);
	private:
		Node _Root;
	};

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanTree<S, F>::HuffmanTree()
		: _Root()
	{ }

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanTree<S, F>::~HuffmanTree()
	{ }

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	inline Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanTree<S, F> HuffmanTree<S, F>::Build(ConstSymbolPointer Input, const Elysium::Core::Template::System::size Length)
	{
		// count occurrences for each symbol
		constexpr const F OccurrencesLength = Elysium::Core::Template::Numeric::NumericTraitsBase<S>::Maximum + 1;
		F Occurrences[OccurrencesLength] = { 0 };
		for (Elysium::Core::Template::System::size i = 0; i < Length; i++)
		{
			Occurrences[Input[i]]++;
		}

		// create leaf nodes
		//Elysium::Core::Template::Container::Adopter::PriorityQueue<Node*, Container::Vector<Node*>> Heap;
		for (F i = 0; i < OccurrencesLength; i++)
		{
			if (Occurrences[i] > 0)
			{
				//Heap.Push(new Node<S, F>());
			}
		}

		// ...

		return Elysium::Core::Template::IO::Compression::HuffmanCoding::HuffmanTree<S, F>();
	}
}
#endif
