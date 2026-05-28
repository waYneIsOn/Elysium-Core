/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANDECODER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "../../../Concepts/UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_QUEUE_VECTOR
#include "../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANCODE
#include "_HuffmanCode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANNODE
#include "_HuffmanNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANSYMBOLTRAITS
#include "_HuffmanSymbolTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTREE
#include "_HuffmanTree.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANUTILITY
#include "_HuffmanUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MAX
#include "../../../Math/Max.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENA
#include "../../../Memory/Scoped/Arena.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	template<Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::Concepts::UnsignedInteger F>
	class HuffmanDecoder
	{
	public:
		using Symbol = HuffmanUtility<S>::Symbol;

		using SymbolCodeMap = HuffmanUtility<S>::SymbolCodeMap;
	private:
		using SymbolCodeMapFIterator = SymbolCodeMap::FIterator;

		using PackedCodeSymbolMap = Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::Template::System::uint64_t, S>;
	public:
		constexpr HuffmanDecoder() = default;

		constexpr HuffmanDecoder(const HuffmanDecoder& Source) = delete;

		constexpr HuffmanDecoder(HuffmanDecoder&& Right) noexcept = delete;

		constexpr ~HuffmanDecoder() = default;
	public:
		constexpr HuffmanDecoder& operator=(const HuffmanDecoder& Source) = delete;

		constexpr HuffmanDecoder& operator=(HuffmanDecoder&& Right) noexcept = delete;
	private:
		//inline static constexpr const Elysium::Core::Template::System::uint8_t _FastTableBits = 0;	// EVERYTHING goes into subtables
		//inline static constexpr const Elysium::Core::Template::System::uint8_t _FastTableBits = 1;

		//inline static constexpr const Elysium::Core::Template::System::uint8_t _FastTableBits = 3;
		//inline static constexpr const Elysium::Core::Template::System::uint8_t _FastTableBits = 5;

		//inline static constexpr const Elysium::Core::Template::System::uint8_t _FastTableBits = 8;

		// @Note: should be in the range of 8 to 12 bits resulting in 256 to 4096 entries normally fitting into L1 cache.
		inline static constexpr const Elysium::Core::Template::System::uint8_t _FastTableBits = 9;

		//inline static constexpr const Elysium::Core::Template::System::uint8_t _FastTableBits = 12;
	public:
		inline const Elysium::Core::Template::Container::Vector<S> DecompressMSB(const Elysium::Core::Template::System::byte* CompressedData, const Elysium::Core::Template::System::size Length,
			const Elysium::Core::Template::System::size UncompressedLength, SymbolCodeMap& SymbolCodes)
		{
			// @Note: most algorithms either store "UncompressedLength" or some other way of "termination logic" (like EOB - end of block) in the header.
			// For now I will implement the approach of having access to the uncompressed length, I will need to implement other methods as well though!
			Elysium::Core::Template::Container::Vector<S> Result = Elysium::Core::Template::Container::Vector<S>(UncompressedLength + sizeof(S));
			Result.Clear();

			/*
			* To find symbols:
			* - The most naive approach recreates the tree which then is iterated on a bit-by-bit basis.
			* - A better but still fairly naive approach generates a lookup-table to be used trying increasingly longer code-lengths.
			* - An even better approach generates a larger lookup-table adding symbols multiple times with different prefixes to
			*	eliminate the inner-loop of having to use increasingly longer code-lengths.
			* - The standard approach creates multiple lookup-tables: One "fast table" for short codes and subtables for longer codes
			*	resulting in a singular lookup and two at worst.
			*/

			struct TableEntry
			{
				S _Symbol;
				Elysium::Core::Template::System::uint8_t _Length;
				bool _IsLeaf;

				TableEntry* _Subtable;
				Elysium::Core::Template::System::uint8_t _SubTableLength;
			};

			TableEntry FastTable[1 << _FastTableBits] = {};

			// Step 1: Run a first pass to determine the total number of subtables as well as the total number of subtable-entries required
			Elysium::Core::Template::System::uint8_t MaxRemainingBitsPerSubtable[1 << _FastTableBits] = {};
			for (SymbolCodeMapFIterator Iterator = SymbolCodes.GetBegin(); Iterator != SymbolCodes.GetEnd(); ++Iterator)
			{
				const Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<Symbol, HuffmanCode>>* Node = *Iterator;
				const Elysium::Core::Template::Container::KeyValuePair<Symbol, HuffmanCode>& Item = Node->GetItem();

				const HuffmanCode& CurrentHuffmanCode = Item.GetValue();

				const Elysium::Core::Template::System::uint32_t CurrentCode = CurrentHuffmanCode._Bits;
				const Elysium::Core::Template::System::uint8_t CurrentLength = CurrentHuffmanCode._Length;

				if (CurrentLength <= _FastTableBits)
				{
					continue;
				}

				Elysium::Core::Template::System::size Index = CurrentCode >> (CurrentLength - _FastTableBits);
				Elysium::Core::Template::System::uint8_t RemainingBits = CurrentLength - _FastTableBits;

				MaxRemainingBitsPerSubtable[Index] = Elysium::Core::Template::Math::Max(MaxRemainingBitsPerSubtable[Index], RemainingBits);
			}

			Elysium::Core::Template::System::size TotalNumberOfSubtables = 0;
			Elysium::Core::Template::System::size TotalNumberOfSubtableEntries = 0;
			for (size_t i = 0; i < (1u << _FastTableBits); ++i)
			{
				if (MaxRemainingBitsPerSubtable[i] > 0)
				{
					++TotalNumberOfSubtables;
					TotalNumberOfSubtableEntries += (1_ui64 << MaxRemainingBitsPerSubtable[i]);
				}
			}

			// Step 2: Create an arena holding all entries in one page and pre-allocate values in FastTable whenever a Subtable is required
			Elysium::Core::Template::Memory::Scoped::Arena SubtableArena(Elysium::Core::Template::Memory::Scoped::ArenaOptions(sizeof(TableEntry) * TotalNumberOfSubtableEntries, 1));
			TableEntry* SubtableCursor = SubtableArena.Push<TableEntry>(TotalNumberOfSubtableEntries);

			for (Elysium::Core::Template::System::size i = 0; i < (1_ui64 << _FastTableBits); ++i)
			{
				if (0 == MaxRemainingBitsPerSubtable[i])
				{
					continue;
				}

				FastTable[i]._Subtable = SubtableCursor;
				FastTable[i]._SubTableLength = MaxRemainingBitsPerSubtable[i];
				FastTable[i]._IsLeaf = false;

				// @ToDo: not 100% sure this is correct!!!
				Elysium::Core::Template::System::size AdvanceBy = 1_ui64 << MaxRemainingBitsPerSubtable[i];
				SubtableCursor += AdvanceBy;
			}

			// Step 3: Fully popoulate all tables (MSB)
			for (SymbolCodeMapFIterator Iterator = SymbolCodes.GetBegin(); Iterator != SymbolCodes.GetEnd(); ++Iterator)
			{
				const Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<Symbol, HuffmanCode>>* Node = *Iterator;
				const Elysium::Core::Template::Container::KeyValuePair<Symbol, HuffmanCode>& Item = Node->GetItem();

				const S& CurrentSymbol = Item.GetKey();
				const HuffmanCode& CurrentHuffmanCode = Item.GetValue();

				const Elysium::Core::Template::System::uint32_t CurrentCode = CurrentHuffmanCode._Bits;
				const Elysium::Core::Template::System::uint8_t CurrentLength = CurrentHuffmanCode._Length;
				
				if (CurrentLength <= _FastTableBits) ELYSIUM_CORE_PATH_LIKELY
				{	// can simply populate
					Elysium::Core::Template::System::uint32_t Shift = _FastTableBits - CurrentLength;
					Elysium::Core::Template::System::uint32_t Start = CurrentCode << Shift;
					Elysium::Core::Template::System::uint32_t End = 1_ui32 << Shift;

					for (Elysium::Core::Template::System::uint32_t i = 0; i < End; ++i)
					{
						FastTable[Start + i] = { CurrentSymbol, CurrentLength, true, nullptr, 0 };
					}
				}
				else
				{	// pointer to subtable required
					Elysium::Core::Template::System::size FastTableIndex = CurrentCode >> (CurrentLength - _FastTableBits);
					TableEntry* Subtable = FastTable[FastTableIndex]._Subtable;

					Elysium::Core::Template::System::uint8_t RemainingBits = CurrentLength - _FastTableBits;
					Elysium::Core::Template::System::uint32_t SubTableIndex = CurrentCode & ((1_ui32 << RemainingBits) - 1_ui32);

					Elysium::Core::Template::System::uint8_t SubtableBits = FastTable[FastTableIndex]._SubTableLength;
					Elysium::Core::Template::System::uint8_t SuffixBits = SubtableBits - RemainingBits;

					Elysium::Core::Template::System::uint32_t Start = SubTableIndex << SuffixBits;
					Elysium::Core::Template::System::uint32_t End = 1 << SuffixBits;

					for (Elysium::Core::Template::System::uint32_t i = 0; i < End; ++i)
					{
						Subtable[Start + i] = { CurrentSymbol, CurrentLength, true, nullptr, 0 };
					}
				}
			}

			// Step 4: Actually decode
			Elysium::Core::Template::System::size InputPosition = 0;

			Elysium::Core::Template::System::uint64_t Buffer = 0;
			Elysium::Core::Template::System::uint8_t BitCount = 0;

			for (Elysium::Core::Template::System::size i = 0; i < UncompressedLength; ++i)
			{
				// Once there are 56 bits in an uint64_t another shift by eight bits is still possible. Afterwards it would result in an overflow.
				while (BitCount <= 56)
				{
					if (InputPosition < Length)
					{
						Buffer = (Buffer << 8) | CompressedData[InputPosition++];
						BitCount += 8;
					}
					else
					{	// Obviously at the EOF/EOB the buffer still needs to be populated correctly!
						Buffer = (Buffer << 8) | 0x0;
						BitCount += 8;
					}
				}
				
				const Elysium::Core::Template::System::uint64_t Mask = (1_ui64 << _FastTableBits) - 1_ui64;
				const Elysium::Core::Template::System::size FastTableIndex = (BitCount >= _FastTableBits) ? 
					(Buffer >> (BitCount - _FastTableBits)) & Mask :
					(Buffer << (_FastTableBits - BitCount)) & Mask;
				const TableEntry& FastTableEntry = FastTable[FastTableIndex];

				if (FastTableEntry._IsLeaf)
				{
					Result.PushBack(FastTableEntry._Symbol);

					BitCount -= FastTableEntry._Length;
					Buffer &= ((1_ui64 << BitCount) - 1);
				}
				else
				{
					const Elysium::Core::Template::System::uint32_t RemainingBits = FastTableEntry._SubTableLength;

					const Elysium::Core::Template::System::uint32_t SubTableIndex = (Buffer >> (BitCount - _FastTableBits - RemainingBits)) & ((1_ui64 << RemainingBits) - 1_ui64);
					const TableEntry& SubTableEntry = FastTableEntry._Subtable[SubTableIndex];

					if (!SubTableEntry._IsLeaf)
					{	// @ToDo: throw specific exception
						throw 1;
					}

					Result.PushBack(SubTableEntry._Symbol);

					BitCount -= SubTableEntry._Length;
					Buffer &= ((1ULL << BitCount) - 1);
				}
			}

			return Result;
		}

		inline const Elysium::Core::Template::Container::Vector<S> DecompressMSB(const Elysium::Core::Template::System::byte* CompressedData, const Elysium::Core::Template::System::size Length,
			const Elysium::Core::Template::System::size UncompressedLength, const Elysium::Core::Template::Container::Vector<HuffmanSymbolCodeLengthPair<S>>& SymbolCodeLengths)
		{
			/*
			// @ToDo: do I just want to assume sorted code lengths? will depend on input from how well known algorithms store things!
			HuffmanSymbolCodeLengthPair<Elysium::Core::Template::System::byte>& First = *SymbolCodeLengths.GetBegin();
			HuffmanSymbolCodeLengthPair<Elysium::Core::Template::System::byte>& Last = *SymbolCodeLengths.GetEnd();
			Elysium::Core::Template::Algorithms::Sorting::BubbleSort<HuffmanSymbolCodeLengthPair<Elysium::Core::Template::System::byte>*>(&First, &Last);
			*/
			SymbolCodeMap SymbolCodes = HuffmanUtility<S>::CreateFromSymbolCodeLengths(SymbolCodeLengths);

			return DecompressMSB(CompressedData, Length, UncompressedLength, SymbolCodes);
		}
	};
}
#endif
