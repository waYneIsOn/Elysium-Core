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
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANFREQUENCYTABLE
#include "_HuffmanFrequencyTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "_HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../../UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_QUEUE_PRIORITYQUEUE
#include "../../../Container/PriorityQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_UNORDEREDMAP
#include "../../../Container/UnorderedMap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENA
#include "../../../Memory/Scoped/Arena.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../../../Numeric/NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../../../System/Compiler.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../../Text/String.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanEncoder;

	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanDecoder;
	
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanTree
	{
		friend class HuffmanEncoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
		friend class HuffmanDecoder<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>;
	public:
		using Node = HuffmanNode<S, F>;
	private:
		using NodePointer = HuffmanNode<S, F>*;
	public:
		constexpr HuffmanTree() = default;

		constexpr HuffmanTree(const HuffmanTree& Source) = delete;

		constexpr HuffmanTree(HuffmanTree&& Right) noexcept = delete;

		constexpr ~HuffmanTree() = default;
	public:
		constexpr HuffmanTree& operator=(const HuffmanTree& Source) = delete;

		constexpr HuffmanTree& operator=(HuffmanTree&& Right) noexcept = delete;
	private:
		struct NodeComparison
		{
			bool operator()(Node* Left, Node* Right)
			{
				if (Left->_Frequency == Right->_Frequency)
				{
					return Left->_Symbol > Right->_Symbol;
				}

				return Left->_Frequency > Right->_Frequency;
			}
		};
	public:
		inline void Rebuild(const HuffmanFrequencyTable<S, F>& Frequencies, const bool InvertLeftAndRight, Elysium::Core::Template::System::uint8_t& CountedNumberOfLeafNodes)
		{
			const F OccurrencesLength = Frequencies.GetLength();
			for (F i = 0; i < OccurrencesLength; ++i)
			{
				if (Frequencies[i] > 0)
				{
					++CountedNumberOfLeafNodes;
				}
			}

			//Discard();	// @ToDo: since _NodeArena.SetOptions(...) resets the arena and _Root gets set later on, this should not be necessary here -> make sure!
			_NodeArena.SetOptions(Elysium::Core::Template::Memory::Scoped::ArenaOptions(CountedNumberOfLeafNodes, 1));

			Elysium::Core::Template::Container::PriorityQueue<Node*, Container::Vector<Node*>, NodeComparison> Heap{};
			for (F i = 0; i < OccurrencesLength; ++i)
			{
				if (Frequencies[i] > 0)
				{
					void* Data = _NodeArena.Push(sizeof(Node));
					Node* CurrentNode = reinterpret_cast<Node*>(Data);
					CurrentNode->_Symbol = i;
					CurrentNode->_Frequency = Frequencies[i];
					CurrentNode->_Left = nullptr;
					CurrentNode->_Right = nullptr;

					Heap.Push(CurrentNode);
				}
			}

			while (Heap.GetLength() > 1)
			{
				Node* Left = Heap.GetTop();
				Heap.Pop();

				Node* Right = Heap.GetTop();
				Heap.Pop();

				if (InvertLeftAndRight)
				{
					Heap.Push(new Node(Left, Right));
				}
				else
				{
					Heap.Push(new Node(Right, Left));
				}
			}

			Node* Root = Heap.GetTop();
			Heap.Pop();

			// ...
			_Root = Root;
		}

		inline void Discard()
		{
			_Root = nullptr;
			_NodeArena.Clear();
		}
	private:
		Elysium::Core::Template::Memory::Scoped::Arena _NodeArena{};
		NodePointer _Root{};
	};
}
#endif
