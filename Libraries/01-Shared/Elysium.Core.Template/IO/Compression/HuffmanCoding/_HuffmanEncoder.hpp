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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANCODE
#include "_HuffmanCode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANFREQUENCYTABLE
#include "_HuffmanFrequencyTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "_HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANSYMBOLCODELENGTHPAIR
#include "_HuffmanSymbolCodeLengthPair.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#include "_HuffmanTree.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANUTILITY
#include "_HuffmanUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_STACK
#include "../../../Container/Adopter/Stack.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanEncoder
	{
	private:
		using Tree = HuffmanTree<S, F>;

		using Node = Tree::Node;

		// limit code-length to 255 by using uint8_t
		using CodeLengthsMap = Elysium::Core::Template::Container::UnorderedMap<S, Elysium::Core::Template::System::uint8_t>;

		using CodeLengthsMapFIterator = CodeLengthsMap::FIterator;
	public:
		using Symbol = HuffmanSymbolTraits<S>::Symbol;

		using SymbolCodeMap = HuffmanUtility<S>::SymbolCodeMap;
	public:
		constexpr HuffmanEncoder() = default;

		constexpr HuffmanEncoder(const HuffmanEncoder& Source) = delete;

		constexpr HuffmanEncoder(HuffmanEncoder&& Right) noexcept = delete;

		constexpr ~HuffmanEncoder() = default;
	public:
		constexpr HuffmanEncoder& operator=(const HuffmanEncoder& Source) = delete;

		constexpr HuffmanEncoder& operator=(HuffmanEncoder&& Right) noexcept = delete;
	public:
		inline SymbolCodeMap CreateTreeBased(const S* Data, const Elysium::Core::Template::System::size Length, const bool InvertLeftAndRight = false)
		{
			// Step 1: count occurrences for each symbol
			HuffmanFrequencyTable<S, F> Frequencies = CountOcccurrences(Data, Length);

			// Step 2: generate huffman tree
			Elysium::Core::Template::System::uint8_t CountedNumberOfLeafNodes = 0;	// used later on to pre-allocate the required amount of elements
			_Tree.Rebuild(Frequencies, InvertLeftAndRight, CountedNumberOfLeafNodes);
			
			// Step 3: create codes directly
			SymbolCodeMap SymbolCodes = SymbolCodeMap(CountedNumberOfLeafNodes);
			if (nullptr == _Tree._Root->_Left && nullptr == _Tree._Root->_Right)
			{	// special case if input only contains a single symbol
				SymbolCodes.Set(_Tree._Root->_Symbol, HuffmanCode(0b0, 1));
			}
			else
			{
				if (nullptr == _Tree._Root) ELYSIUM_CORE_PATH_UNLIKELY
				{
					return SymbolCodes;
				}

				struct StackFrame
				{
					const Node* Node;
					HuffmanCode Code;
				};

				Elysium::Core::Template::Container::Stack<StackFrame> Stack{};
				Stack.Push({ _Tree._Root, HuffmanCode(0b0, 0) });
				
				while(!Stack.GetIsEmpty())
				{
					const StackFrame CurrentFrame = Stack.GetTop();
					Stack.Pop();

					const Node* Current = CurrentFrame.Node;
					const HuffmanCode& CurrentCode = CurrentFrame.Code;

					if (nullptr == Current->_Left && nullptr == Current->_Right)
					{
						SymbolCodes.Set(Current->_Symbol, CurrentCode);
						continue;
					}

					if (nullptr != Current->_Left)
					{
						HuffmanCode LeftCode(CurrentCode._Bits << 1, CurrentCode._Length + 1);
						Stack.Push({ Current->_Left, LeftCode });
					}

					if (nullptr != Current->_Right)
					{
						HuffmanCode RightCode((CurrentCode._Bits << 1) | 1, CurrentCode._Length + 1);
						Stack.Push({ Current->_Right, RightCode });
					}
				}
			}
						
			return SymbolCodes;
		}

		inline SymbolCodeMap CreateCanonical(const S* Data, const Elysium::Core::Template::System::size Length, const bool InvertLeftAndRight = false)
		{
			// Step 1: count occurrences for each symbol
			HuffmanFrequencyTable<S, F> Frequencies = CountOcccurrences(Data, Length);

			// @ToDo: I am currently doing a "classic huffman tree" here. There are algorithms that can calculate CodeLengths more or less directly from Frequencies - make those available!
			// Examples:
			//	- two-queue linear huffman https://www.geeksforgeeks.org/dsa/efficient-huffman-coding-for-sorted-input-greedy-algo-4/
			//	- in-place huffman https://experiencestack.co/in-place-huffman-codes-ff7d5305d019
			//  - Package-Merge Algorithm (used by deflate, so required anyways!!!) https://en.wikipedia.org/wiki/Package-merge_algorithm <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			//	- etc.

			// Step 2: generate huffman tree
			Elysium::Core::Template::System::uint8_t CountedNumberOfLeafNodes = 0;	// used later on to pre-allocate the required amount of elements
			_Tree.Rebuild(Frequencies, InvertLeftAndRight, CountedNumberOfLeafNodes);

			// Step 3: Derive code-lengths for each symbol and sort them
			// @ToDo: pretty sure this step can be simplified by a lot (currently: unordered_map into vector into sort)
			CodeLengthsMap CodeLengths = CodeLengthsMap(CountedNumberOfLeafNodes);
			if (nullptr != _Tree._Root) ELYSIUM_CORE_PATH_LIKELY
			{
				struct StackFrame
				{
					const Node* Node;
					Elysium::Core::Template::System::uint8_t Depth;
				};
				
				Elysium::Core::Template::Container::Stack<StackFrame> Stack{};
				Stack.Push({ _Tree._Root, 0_ui8 });

				while (!Stack.GetIsEmpty())
				{
					const StackFrame CurrentFrame = Stack.GetTop();
					Stack.Pop();

					const Node* Current = CurrentFrame.Node;
					const Elysium::Core::Template::System::uint8_t CurrentDepth = CurrentFrame.Depth;

					if (nullptr == Current->_Left && nullptr == Current->_Right)
					{
						CodeLengths.Set(Current->_Symbol, CurrentDepth);
						continue;
					}

					if (nullptr != Current->_Left)
					{
						const Elysium::Core::Template::System::uint8_t LeftDepth = CurrentDepth + 1_ui8;
						Stack.Push({ Current->_Left, LeftDepth });
					}

					if (nullptr != Current->_Left)
					{
						const Elysium::Core::Template::System::uint8_t RightDepth = CurrentDepth + 1_ui8;
						Stack.Push({ Current->_Right, RightDepth });
					}
				}
			}
			
			Elysium::Core::Template::Container::Vector<HuffmanSymbolCodeLengthPair<Elysium::Core::Template::System::byte>> SymbolCodeLengths;
			for (CodeLengthsMapFIterator Iterator = CodeLengths.GetBegin(); Iterator != CodeLengths.GetEnd(); ++Iterator)
			{
				const Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<S, Elysium::Core::Template::System::uint8_t>>* Node = *Iterator;
				const Elysium::Core::Template::Container::KeyValuePair<S, Elysium::Core::Template::System::uint8_t>& Item = Node->GetItem();

				SymbolCodeLengths.PushBack(HuffmanSymbolCodeLengthPair<Elysium::Core::Template::System::byte>(Item.GetKey(), Item.GetValue()));
			}

			// Step 4: discard tree (only symbol/code-lengths are necessarys at this point)
			_Tree.Discard();

			// Step 5: Sort that symbol/code-length pair
			// @ToDo: simplify this step together with step 3!
			Elysium::Core::Template::Algorithms::Sorting::BubbleSort(SymbolCodeLengths.GetBegin(), SymbolCodeLengths.GetEnd());
			
			// Step 6: Generate codes from that data
			SymbolCodeMap SymbolCodes = HuffmanUtility<S>::CreateFromSymbolCodeLengths(SymbolCodeLengths);

			return SymbolCodes;
		}
		
		inline const Elysium::Core::Template::System::size CalculateCompressedSize(const S* Data, const Elysium::Core::Template::System::size Length, const SymbolCodeMap& SymbolCodes)
		{
			Elysium::Core::Template::System::size CompressedLength = 0;
			for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
			{
				const HuffmanCode& CurrentCode = SymbolCodes[Data[i]];

				CompressedLength += CurrentCode._Length;
			}
			return CompressedLength;
		}

		inline const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Compress(const S* Data, const Elysium::Core::Template::System::size Length, 
			const SymbolCodeMap& SymbolCodes)
		{
			Elysium::Core::Template::System::size CompressedLength = CalculateCompressedSize(Data, Length, SymbolCodes) / 8 + 1;

			Elysium::Core::Template::System::uint64_t Buffer = 0;
			Elysium::Core::Template::System::uint8_t BitCount = 0;

			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result = 
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>(CompressedLength);
			Result.Clear();
			for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
			{
				const S& CurrentInput = Data[i];
				const HuffmanCode& CurrentCode = SymbolCodes[CurrentInput];

				Buffer <<= CurrentCode._Length;
				Buffer |= CurrentCode._Bits;

				BitCount += CurrentCode._Length;

				while (BitCount >= 8)
				{
					BitCount -= 8;
					Elysium::Core::Template::System::byte Byte = (Buffer >> BitCount) & 0xFF;

					Result.PushBack(Byte);
				}
			}

			if (BitCount > 0)
			{
				Elysium::Core::Template::System::byte Byte = (Buffer << (8 - BitCount)) & 0xFF;

				Result.PushBack(Byte);

				BitCount = 0;
			}

			return Result;
		}
		/*
		// @ToDo
		inline void Compress(Stream& TargetStream, const S* Data, const Elysium::Core::Template::System::size Length)
		{

		}
		*/
	public:
		inline void Encode()
		{
			// input: symbol and target to write the encoded symbol to (bitstream or w/e)
		}
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
	private:
		HuffmanTree<S, F> _Tree{ };
	};
}
#endif
