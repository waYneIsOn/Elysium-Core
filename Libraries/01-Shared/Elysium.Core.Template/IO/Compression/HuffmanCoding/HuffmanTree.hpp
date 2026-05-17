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

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "HuffmanNode.hpp"
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
	class HuffmanTreeBase
	{
	public:
		using Node = HuffmanNode<S, F>;

		using Symbol = S;
		using ConstSymbolPointer = const S*;

		using Frequency = F;

		using CodeLengthsMap = Elysium::Core::Template::Container::UnorderedMap<S, F>;



		using CodeMap = Elysium::Core::Template::Container::UnorderedMap<S, Elysium::Core::Template::Text::String<char8_t>>;
	protected:
		constexpr HuffmanTreeBase() = default;
	public:
		constexpr HuffmanTreeBase(const HuffmanTreeBase& Source) = delete;

		constexpr HuffmanTreeBase(HuffmanTreeBase&& Right) noexcept = delete;

		constexpr virtual ~HuffmanTreeBase() = default;
	public:
		constexpr HuffmanTreeBase& operator=(const HuffmanTreeBase& Source) = delete;

		constexpr HuffmanTreeBase& operator=(HuffmanTreeBase&& Right) noexcept = delete;
	};

	/// <summary>
	/// Specialization used for when compression is based on bytes allowing for using an array.
	/// </summary>
	template<>
	class HuffmanTree<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>
		: public HuffmanTreeBase<Elysium::Core::Template::System::byte, Elysium::Core::Template::System::size>
	{
	private:
		inline constexpr HuffmanTree(Node* Root)
			: _Root(Root)
		{ }
	public:
		inline constexpr virtual ~HuffmanTree()
		{
			if (nullptr != _Root)
			{
				delete _Root;
				_Root = nullptr;
			}
		}
	private:
		struct CompareNodes
		{
			bool operator()(Node* Left, Node* Right)
			{
				/*
				if (Left->_Frequency == Right->_Frequency)
				{
					return Left->_Symbol > Right->_Symbol;
				}
				*/
				return Left->_Frequency > Right->_Frequency;
			}
		};
	public:
		inline static const HuffmanTree Build(ConstSymbolPointer Input, const Elysium::Core::Template::System::size Length,
			bool SwapLeftAndRight = false)
		{
			// count occurrences/frequency for each symbol
			constexpr const Frequency OccurrencesLength = 256;
			Frequency Occurrences[OccurrencesLength] = { 0 };
			for (Elysium::Core::Template::System::size i = 0; i < Length; i++)
			{
				++Occurrences[Input[i]];
			}

			// create leaf nodes
			Elysium::Core::Template::Container::PriorityQueue<Node*, Container::Vector<Node*>, CompareNodes> Heap{};
			for (Frequency i = 0; i < OccurrencesLength; ++i)
			{
				if (Occurrences[i] > 0)
				{
					Heap.Push(new Node(i, Occurrences[i]));
				}
			}
			
			// build the tree
			while (Heap.GetLength() > 1)
			{
				Node* Left = Heap.GetTop();
				Heap.Pop();

				Node* Right = Heap.GetTop();
				Heap.Pop();

				if (SwapLeftAndRight)
				{
					Heap.Push(new Node(Right, Left));
				}
				else
				{
					Heap.Push(new Node(Left, Right));
				}
			}

			return HuffmanTree(Heap.GetTop());
		}
	public:
		inline CodeLengthsMap GenerateCodeLengths()
		{
			// @ToDo: use length of tree to preallocate
			CodeLengthsMap Result = CodeLengthsMap();

			GenerateCodeLengthsRecursively(_Root, 0, Result);

			return Result;
		}

		inline CodeMap GenerateCodes()
		{
			// @ToDo: use length of tree to preallocate
			CodeMap Result = CodeMap();

			GenerateCodesRecursively(_Root, u8"", Result);

			return Result;
		}
	private:
		inline void GenerateCodeLengthsRecursively(const Node* Current, const Elysium::Core::Template::System::uint8_t Depth,
			CodeLengthsMap& CodeLengths)
		{
			if (nullptr == Current) ELYSIUM_CORE_PATH_UNLIKELY
			{
				return;
			}

			// we're only looking for leaf-nodes here obviously
			if (nullptr == Current->_Left && nullptr == Current->_Right)
			{
				CodeLengths.Set(Current->_Symbol, Depth);
				return;
			}

			GenerateCodeLengthsRecursively(Current->_Left, Depth + 1, CodeLengths);
			GenerateCodeLengthsRecursively(Current->_Right, Depth + 1, CodeLengths);
		}

		inline void GenerateCodesRecursively(const Node* Current, const Elysium::Core::Template::Text::String<char8_t>& CurrentCode,
			CodeMap& Codes)
		{
			if (nullptr == Current) ELYSIUM_CORE_PATH_UNLIKELY
			{
				return;
			}

			// we're only looking for leaf-nodes here obviously
			if (nullptr == Current->_Left && nullptr == Current->_Right)
			{
				Codes.Set(Current->_Symbol, CurrentCode);
				return;
			}

			const Elysium::Core::Template::System::size CurrentCodeLength = CurrentCode.GetLength();

			Elysium::Core::Template::Text::String<char8_t> LeftCode =
				Elysium::Core::Template::Text::String<char8_t>(CurrentCodeLength + sizeof(char8_t));
			for (Elysium::Core::Template::System::size i = 0; i < CurrentCodeLength; ++i)
			{
				LeftCode[i] = CurrentCode[i];
			}
			LeftCode[CurrentCodeLength] = u8'0';
			GenerateCodesRecursively(Current->_Left, LeftCode, Codes);

			Elysium::Core::Template::Text::String<char8_t> RightCode =
				Elysium::Core::Template::Text::String<char8_t>(CurrentCodeLength + sizeof(char8_t));
			for (Elysium::Core::Template::System::size i = 0; i < CurrentCodeLength; ++i)
			{
				RightCode[i] = CurrentCode[i];
			}
			RightCode[CurrentCodeLength] = u8'1';
			GenerateCodesRecursively(Current->_Right, RightCode, Codes);
		}
	//private:
	public:
		Node* _Root;
	};
}
#endif
