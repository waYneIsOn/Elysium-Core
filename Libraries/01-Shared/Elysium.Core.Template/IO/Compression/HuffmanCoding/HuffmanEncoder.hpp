/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANENCODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANENCODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ALGORITHMS_SORTING_BUBBLESORT
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Algorithms/Sorting/BubbleSort.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../../Concepts/UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_QUEUE_PRIORITYQUEUE
#include "../../../Container/PriorityQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANFREQUENCYTABLE
#include "HuffmanFrequencyTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#include "HuffmanTree.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanEncoder
	{
	private:
		using Tree = HuffmanTree<S, F>;

		using Node = HuffmanNode<S, F>;

		// limit code-length to 255 by using uint8_t
		using CodeLengthsMap = Elysium::Core::Template::Container::UnorderedMap<S, Elysium::Core::Template::System::uint8_t>;

		using CodeLengthsMapFIterator = CodeLengthsMap::FIterator;
	public:
		using SymbolCodeMap = Elysium::Core::Template::Container::UnorderedMap<S, Elysium::Core::Template::Text::String<char>>;
	public:
		constexpr HuffmanEncoder() = default;

		constexpr HuffmanEncoder(const HuffmanEncoder& Source) = delete;

		constexpr HuffmanEncoder(HuffmanEncoder&& Right) noexcept = delete;

		constexpr ~HuffmanEncoder() = default;
	public:
		constexpr HuffmanEncoder& operator=(const HuffmanEncoder& Source) = delete;

		constexpr HuffmanEncoder& operator=(HuffmanEncoder&& Right) noexcept = delete;
	private:
		struct SymbolCodeLengthPair
		{
			S Symbol;
			Elysium::Core::Template::System::uint8_t CodeLength;

			friend bool operator<(const SymbolCodeLengthPair& Left, const SymbolCodeLengthPair& Right)
			{
				if (Left.CodeLength == Right.CodeLength)
				{
					return Left.Symbol > Right.Symbol;
				}

				return Left.CodeLength > Right.CodeLength;
			}
		};
	public:
		inline SymbolCodeMap CreateTreeBased(const S* Data, const Elysium::Core::Template::System::size Length, const bool InvertLeftAndRight = false)
		{
			// Step 1: count occurrences for each symbol
			HuffmanFrequencyTable<S, F> Frequencies = CountOcccurrences(Data, Length);

			// Step 2: generate huffman tree
			Elysium::Core::Template::System::uint8_t CountedNumberOfLeafNodes = 0;	// used later on to pre-allocate the required amount of elements
			_Tree.Clear();
			_Tree._Root = CreateTree(Frequencies, InvertLeftAndRight, CountedNumberOfLeafNodes);
			
			// Step 3: create codes directly
			SymbolCodeMap SymbolCodes = SymbolCodeMap(CountedNumberOfLeafNodes);
			GenerateTreeBasedCodesRecursively(_Tree._Root, "", SymbolCodes);
			
			return SymbolCodes;
		}

		inline SymbolCodeMap CreateCanonical(const S* Data, const Elysium::Core::Template::System::size Length, const bool InvertLeftAndRight = false)
		{
			// Step 1: count occurrences for each symbol
			HuffmanFrequencyTable<S, F> Frequencies = CountOcccurrences(Data, Length);

			// Step 2: generate huffman tree
			Elysium::Core::Template::System::uint8_t CountedNumberOfLeafNodes = 0;	// used later on to pre-allocate the required amount of elements
			_Tree.Clear();
			_Tree._Root = CreateTree(Frequencies, InvertLeftAndRight, CountedNumberOfLeafNodes);






			// Step 3: Derive code-lengths for each symbol and sort them
			// @ToDo: simplify this step!
			CodeLengthsMap CodeLengths = CodeLengthsMap(CountedNumberOfLeafNodes);
			DeriveCodeLengthsRecursively(_Tree._Root, 0, CodeLengths);

			Elysium::Core::Template::Container::Vector<SymbolCodeLengthPair> SymbolCodeLengths;
			for (CodeLengthsMapFIterator Iterator = CodeLengths.GetBegin(); Iterator != CodeLengths.GetEnd(); ++Iterator)
			{
				const Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<S, Elysium::Core::Template::System::uint8_t>>* Node = *Iterator;
				const Elysium::Core::Template::Container::KeyValuePair<S, Elysium::Core::Template::System::uint8_t>& Item = Node->GetItem();

				SymbolCodeLengths.PushBack(SymbolCodeLengthPair(Item.GetKey(), Item.GetValue()));
			}

			// Step 4: discard tree (only symbol/code-lengths are necessarys at this point)
			_Tree.Clear();

			// Step 5: Sort that symbol/code-length pair
			// @ToDo: simplify this step together with step 3!
			SymbolCodeLengthPair& First = *SymbolCodeLengths.GetBegin();
			SymbolCodeLengthPair& Last = *SymbolCodeLengths.GetEnd();
			Elysium::Core::Template::Algorithms::Sorting::BubbleSort<SymbolCodeLengthPair*>(&First, &Last);
			





			// Step 6: Generate codes from that data
			SymbolCodeMap SymbolCodes = GenerateCanonicalCodes(SymbolCodeLengths);

			return SymbolCodes;
		}
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
	private:
		inline HuffmanFrequencyTable<S, F> CountOcccurrences(const S* Data, const Elysium::Core::Template::System::size Length)
		{
			HuffmanFrequencyTable<S, F> Result{};
			for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
			{
				Result.Add(Data[i]);
			}

			return Result;
		}

		inline Node* CreateTree(const HuffmanFrequencyTable<S, F>& Frequencies, const bool InvertLeftAndRight, Elysium::Core::Template::System::uint8_t& CountedNumberOfLeafNodes)
		{
			const F OccurrencesLength = Frequencies.GetLength();
			Elysium::Core::Template::Container::PriorityQueue<Node*, Container::Vector<Node*>, NodeComparison> Heap{};
			for (F i = 0; i < OccurrencesLength; ++i)
			{
				if (Frequencies[i] > 0)
				{
					++CountedNumberOfLeafNodes;
					Heap.Push(new Node(i, Frequencies[i]));
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
			
			return Root;
		}

		inline void GenerateTreeBasedCodesRecursively(const Node* Current, const Elysium::Core::Template::Text::String<char>& CurrentCode, SymbolCodeMap& Codes)
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

			Elysium::Core::Template::Text::String<char> LeftCode =
				Elysium::Core::Template::Text::String<char>(CurrentCodeLength + sizeof(char));
			for (Elysium::Core::Template::System::size i = 0; i < CurrentCodeLength; ++i)
			{
				LeftCode[i] = CurrentCode[i];
			}
			LeftCode[CurrentCodeLength] = u8'0';
			GenerateTreeBasedCodesRecursively(Current->_Left, LeftCode, Codes);

			Elysium::Core::Template::Text::String<char> RightCode =
				Elysium::Core::Template::Text::String<char>(CurrentCodeLength + sizeof(char));
			for (Elysium::Core::Template::System::size i = 0; i < CurrentCodeLength; ++i)
			{
				RightCode[i] = CurrentCode[i];
			}
			RightCode[CurrentCodeLength] = u8'1';
			GenerateTreeBasedCodesRecursively(Current->_Right, RightCode, Codes);
		}

		inline void DeriveCodeLengthsRecursively(const Node* Current, const Elysium::Core::Template::System::uint8_t Depth, CodeLengthsMap& CodeLengths)
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

			DeriveCodeLengthsRecursively(Current->_Left, Depth + 1, CodeLengths);
			DeriveCodeLengthsRecursively(Current->_Right, Depth + 1, CodeLengths);
		}

		inline SymbolCodeMap GenerateCanonicalCodes(const Elysium::Core::Template::Container::Vector<SymbolCodeLengthPair>& SymbolCodeLengths)
		{
			SymbolCodeMap Result = SymbolCodeMap();
			Elysium::Core::Template::System::size CurrentCode = 0;
			Elysium::Core::Template::System::size PreviousLength = 0;
			for (Elysium::Core::Template::System::size i = 0; i < SymbolCodeLengths.GetLength(); ++i)
			{
				const char Symbol = SymbolCodeLengths[i].Symbol;

				CurrentCode <<= (SymbolCodeLengths[i].CodeLength - PreviousLength);
				PreviousLength = SymbolCodeLengths[i].CodeLength;

				Elysium::Core::Template::System::size Temp = CurrentCode;

				Elysium::Core::Template::Text::String<char> CodeResult = Elysium::Core::Template::Text::String<char>('0', SymbolCodeLengths[i].CodeLength);
				for (int l = SymbolCodeLengths[i].CodeLength - 1; l >= 0; --l)	// highest bit first
					//for(int l = 0; l < SymbolCodeLengths[i].CodeLength; ++l)	// lowest bit first
				{
					CodeResult[l] = (Temp & 1) ? '1' : '0';
					Temp >>= 1;
				}

				Result.Set(SymbolCodeLengths[i].Symbol, CodeResult);

				CurrentCode++;
			}

			return Result;
		}
	private:
		HuffmanTree<S, F> _Tree{ };
	};
}
#endif
