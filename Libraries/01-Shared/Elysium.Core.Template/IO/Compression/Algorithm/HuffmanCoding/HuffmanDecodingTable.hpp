/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_HUFFMANCODING_HUFFMANDECODINGTABLE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_HUFFMANCODING_HUFFMANDECODINGTABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_HUFFMANCODING_HUFFMANDECODINGTABLEENTRY
#include "HuffmanDecodingTableEntry.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::HuffmanCoding
{
	template <Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::System::uint8_t MaximumCodeLength, Elysium::Core::Template::System::size AlphabetLength,
		Elysium::Core::Template::System::uint8_t TableBits>
	class HuffmanDecodingTable
	{
	public:
		/// <summary>
		/// Afaik an alphabet size larger than 4.294.967.295 does not exist in deflate, audio codecs, image compression etc. so uint64_t won't be used.
		/// @ToDo: If my "assumption" is wrong, add the type!
		/// </summary>
		using SymbolType = Elysium::Core::Template::TypeTraits::ConditionalType<AlphabetLength <= 256, Elysium::Core::Template::System::uint8_t,
			Elysium::Core::Template::TypeTraits::ConditionalType<(AlphabetLength <= 65536), Elysium::Core::Template::System::uint16_t,
			Elysium::Core::Template::System::uint32_t>>;

		using EntryType = HuffmanDecodingTableEntry<SymbolType>;

		using EntryReference = EntryType&;

		using ConstEntryReference = const EntryType&;
	public:
		inline static constexpr Elysium::Core::Template::System::uint8_t _MaximumCodeLength = MaximumCodeLength;

		inline static constexpr Elysium::Core::Template::System::uint8_t _TableBits = TableBits;

		inline static constexpr Elysium::Core::Template::System::size FastTableLength = 1 << TableBits;
	private:
		inline static constexpr bool SubtablesRequired = MaximumCodeLength > TableBits;

		inline static constexpr bool UseDynamicStorage = TableBits > 11 || SubtablesRequired;

		using ContainerType = Elysium::Core::Template::TypeTraits::ConditionalType<UseDynamicStorage, Elysium::Core::Template::Container::Vector<EntryType>, EntryType[FastTableLength]>;
	public:
		constexpr HuffmanDecodingTable() = default;

		inline constexpr HuffmanDecodingTable(const Elysium::Core::Template::System::uint8_t(&CodeLengths)[AlphabetLength])
			: _CodeLengths{}, _CanonicalCodes{}, _Table{}
		{
			// @ToDo: use memcpy instead of the loop, as soon as it's possible to use in constexpr-context!
			//Elysium::Core::Template::Memory::MemCpy(&_CodeLengths, CodeLengths, AlphabetLength);
			for (Elysium::Core::Template::System::size i = 0; i < AlphabetLength; ++i)
			{
				_CodeLengths[i] = CodeLengths[i];
			}
			
			BuildCanonicalCodes();
			BuildTable();
		}

		constexpr HuffmanDecodingTable(const HuffmanDecodingTable& Source) = delete;

		constexpr HuffmanDecodingTable(HuffmanDecodingTable&& Right) noexcept = delete;

		constexpr ~HuffmanDecodingTable() = default;
	public:
		constexpr HuffmanDecodingTable<S, MaximumCodeLength, AlphabetLength, TableBits>& operator=(const HuffmanDecodingTable& Source) = delete;

		constexpr HuffmanDecodingTable<S, MaximumCodeLength, AlphabetLength, TableBits>& operator=(HuffmanDecodingTable&& Right) noexcept = delete;
	public:
		inline constexpr ConstEntryReference operator[](const Elysium::Core::Template::System::size Index) const noexcept
		{
			static constexpr const Elysium::Core::Template::System::size RootMask = (1_ui64 << TableBits) - 1_ui64;

			if constexpr (UseDynamicStorage)
			{
				ConstEntryReference Entry = _Table[Index & RootMask];
				if (0 == Entry._Operation)
				{
					return Entry;
				}

				const Elysium::Core::Template::System::uint8_t SubtableBits = Entry._Operation;
				const SymbolType SubtableOffset = Entry._Value;
				const Elysium::Core::Template::System::size SubtableIndex = (Index >> TableBits) & ((1_ui64 << Entry._Operation) - 1_ui64);

				return _Table[SubtableOffset + SubtableIndex];
			}
			else
			{
				return _Table[Index & RootMask];
			}
		}
	public:
		inline constexpr void BuildCanonicalCodes()
		{
			constexpr Elysium::Core::Template::System::uint8_t ValidLengths = MaximumCodeLength + 1;

			// Build the "histogram of code lengths" ie. count number of bits for each possible code-length (1, 10, 100 etc.)
			Elysium::Core::Template::System::uint16_t BitLengthCount[ValidLengths] = { 0 };
			for (SymbolType Symbol = 0; Symbol < AlphabetLength; ++Symbol)
			{
				Elysium::Core::Template::System::uint8_t CodeLength = _CodeLengths[Symbol];
				if (CodeLength != 0)
				{
					BitLengthCount[CodeLength]++;
				}
			}

			// Perform "Kraft inequality check"
			Elysium::Core::Template::System::int64_t Left = 1;
			for (Elysium::Core::Template::System::uint8_t Bits = 1; Bits <= TableBits; ++Bits)
			{
				Left = (Left << 1) - BitLengthCount[Bits];
			}

			if (Left < 0)
			{	// @ToDo: oversubscribed
				throw 1;
			}
			/*
			else if (Left == 0)
			{
				// perfect
			}
			else if (Left > 0)
			{
				// incomplete tree -> afaik fine as well (as long as I fully populate tables)
			}
			*/

			// Define "canonical code ranges" (specifically: calculate the FIRST ie. smallest canonical huffman code for each bit-length)
			Elysium::Core::Template::System::uint16_t NextCode[ValidLengths] = { 0 };
			Elysium::Core::Template::System::uint16_t Code = 0;
			for (Elysium::Core::Template::System::uint8_t Bits = 1; Bits < ValidLengths; ++Bits)
			{
				Code = (Code + BitLengthCount[Bits - 1]) << 1;
				NextCode[Bits] = Code;
			}

			// Assign canonical Huffman codes to symbols using canonical code ranges.
			for (SymbolType Symbol = 0; Symbol < AlphabetLength; ++Symbol)
			{
				Elysium::Core::Template::System::uint8_t CodeLength = _CodeLengths[Symbol];
				if (0 != CodeLength)
				{
					Elysium::Core::Template::System::uint16_t MSBFirstCode = NextCode[CodeLength]++;
					Elysium::Core::Template::System::uint16_t ReversedCode = ReverseBits(MSBFirstCode, CodeLength);
					_CanonicalCodes[Symbol] = ReversedCode;
				}
			}
		}

		inline constexpr void BuildTable()
		{
			if constexpr (UseDynamicStorage)
			{
				// All of the following calculations are done to receive symbols grouped by length so the subtable-creation can be done in one linear pass.
				// @ToDo: re-calculating BitLengthCount here isn't a huge deal (especially looking at the gains of being able to create subtables in o(n))
				// but it certainly isn't optimal!
				constexpr Elysium::Core::Template::System::uint8_t ValidLengths = MaximumCodeLength + 1;
				Elysium::Core::Template::System::uint16_t BitLengthCount[ValidLengths] = { 0 };
				for (SymbolType Symbol = 0; Symbol < AlphabetLength; ++Symbol)
				{
					Elysium::Core::Template::System::uint8_t CodeLength = _CodeLengths[Symbol];
					if (CodeLength != 0)
					{
						BitLengthCount[CodeLength]++;
					}
				}

				// Calculate starting index/offset for all groups of code-lengths
				// ie. where do code-lengths of length 1 start? where do code-lengths of length 2 start? etc. pp.
				Elysium::Core::Template::System::uint16_t Offsets[MaximumCodeLength + 1];
				Offsets[1] = 0;
				for (Elysium::Core::Template::System::uint8_t Bits = 1; Bits < MaximumCodeLength; ++Bits)
				{
					Offsets[Bits + 1] = Offsets[Bits] + BitLengthCount[Bits];
				}

				// Calculate symbols grouped by length
				Elysium::Core::Template::System::size SymbolsAdded = 0;
				SymbolType SymbolsInCanonicalOrder[AlphabetLength];
				for (SymbolType Symbol = 0; Symbol < AlphabetLength; ++Symbol)
				{
					Elysium::Core::Template::System::uint8_t Length = _CodeLengths[Symbol];

					if (Length != 0)
					{
						SymbolsInCanonicalOrder[Offsets[Length]++] = Symbol;
						++SymbolsAdded;
					}
				}

				// FULLY populate fast table
				_Table.Resize(FastTableLength);
				Elysium::Core::Template::System::size i = 0;
				while(i < SymbolsAdded)
				{
					SymbolType Symbol = SymbolsInCanonicalOrder[i];
					Elysium::Core::Template::System::uint8_t CodeLength = _CodeLengths[Symbol];
					if (CodeLength > TableBits)
					{
						break;
					}

					Elysium::Core::Template::System::uint16_t CanonicalCode = _CanonicalCodes[Symbol];
					FillFastTableEntries(Symbol, CodeLength, CanonicalCode);
					++i;
				}

				// FULLY populate subtables
				while (i < SymbolsAdded)
				{
					Elysium::Core::Template::System::size GroupStartIndex = i;

					SymbolType Symbol = SymbolsInCanonicalOrder[i];
					Elysium::Core::Template::System::uint8_t CodeLength = _CodeLengths[Symbol];
					Elysium::Core::Template::System::uint16_t CanonicalCode = _CanonicalCodes[Symbol];
					if (CodeLength <= TableBits)
					{	// @ToDo: this is a paranoia check! it should never happen because the previous loop stops at the first long code (ie. too large for fasttable)
						throw 1;
					}

					Elysium::Core::Template::System::uint16_t Prefix = CanonicalCode & ((1_ui16 << TableBits) - 1_ui16);

					Elysium::Core::Template::System::uint8_t SubtableBits = 0;
					while (i < SymbolsAdded)
					{
						SymbolType CurrentSymbol = SymbolsInCanonicalOrder[i];
						Elysium::Core::Template::System::uint8_t CurrentCodeLength = _CodeLengths[CurrentSymbol];
						Elysium::Core::Template::System::uint16_t CurrentCanonicalCode = _CanonicalCodes[CurrentSymbol];
						if (CurrentCodeLength <= TableBits)
						{	// @ToDo: this is a paranoia check! it should never happen because the previous loop stops at the first long code (ie. too large for fasttable)
							throw 1;
						}

						Elysium::Core::Template::System::uint16_t CurrentPrefix = CurrentCanonicalCode & ((1_ui16 << TableBits) - 1_ui16);
						if (CurrentPrefix != Prefix)
						{
							break;
						}

						Elysium::Core::Template::System::uint8_t RemainingBits = CurrentCodeLength - TableBits;
						if (RemainingBits > SubtableBits)
						{
							SubtableBits = RemainingBits;
						}

						++i;
					}

					Elysium::Core::Template::System::size GroupEndIndex = i;

					// Allocate subtable
					Elysium::Core::Template::System::size SubtableOffset = _Table.GetLength();
					_Table.Resize(SubtableOffset + (1_ui64 << SubtableBits));

					// Link root table entry to subtable
					_Table[Prefix]._Operation = SubtableBits;
					_Table[Prefix]._Length = TableBits;
					_Table[Prefix]._Value = SubtableOffset;

					// Fill subtable entries
					for (Elysium::Core::Template::System::size GroupIndex = GroupStartIndex; GroupIndex < GroupEndIndex; ++GroupIndex)
					{
						SymbolType GroupSymbol = SymbolsInCanonicalOrder[GroupIndex];
						FillSubTableEntries(GroupSymbol, _CodeLengths[GroupSymbol], _CanonicalCodes[GroupSymbol], SubtableOffset, SubtableBits);
					}
				}
			}
			else
			{	// FULLY populate fast table
				for (SymbolType Symbol = 0; Symbol < AlphabetLength; ++Symbol)
				{
					Elysium::Core::Template::System::uint8_t CodeLength = _CodeLengths[Symbol];
					if (0 == CodeLength)
					{
						continue;
					}

					Elysium::Core::Template::System::uint16_t CanonicalCode = _CanonicalCodes[Symbol];

					FillFastTableEntries(Symbol, CodeLength, CanonicalCode);
				}
				
				// ensure table is fully populated
				for (Elysium::Core::Template::System::size i = 0; i < FastTableLength; ++i)
				{
					EntryReference Entry = _Table[i];
					/*
					if (!_Table[i].GetIsValid())
					{	// @ToDo:
						throw 1;
					}
					*/
				}
				
			}
		}
	private:
		inline constexpr Elysium::Core::Template::System::uint16_t ReverseBits(Elysium::Core::Template::System::uint16_t Code, Elysium::Core::Template::System::uint16_t Length)
		{
			Elysium::Core::Template::System::uint16_t Result = 0;
			for (Elysium::Core::Template::System::uint16_t i = 0; i < Length; i++)
			{
				Result = (Result << 1) | (Code & 1);
				Code >>= 1;
			}

			return Result;
		}

		inline constexpr void FillFastTableEntries(const SymbolType Symbol, const Elysium::Core::Template::System::uint8_t CodeLength, 
			const Elysium::Core::Template::System::uint16_t CanonicalCode)
		{
			for (Elysium::Core::Template::System::uint32_t i = 0; i < (1 << (TableBits - CodeLength)); ++i)
			{
				Elysium::Core::Template::System::size Index = CanonicalCode | (i << CodeLength);
				if (Index > FastTableLength)
				{	// @ToDo:
					throw 1;
				}

				EntryReference Entry = _Table[Index];
				Entry._Operation = 0;
				Entry._Value = Symbol;
				Entry._Length = CodeLength;
			}
		}

		inline constexpr void FillSubTableEntries(const SymbolType Symbol, const Elysium::Core::Template::System::uint8_t CodeLength,
			const Elysium::Core::Template::System::uint16_t CanonicalCode, Elysium::Core::Template::System::size SubtableOffset, Elysium::Core::Template::System::uint8_t SubtableBits)
		{
			Elysium::Core::Template::System::uint8_t RemainingBits = CodeLength - TableBits;
			Elysium::Core::Template::System::uint16_t SubtableCode = CanonicalCode >> TableBits;
			Elysium::Core::Template::System::uint16_t EntryCount = 1_ui16 << (SubtableBits - RemainingBits);
			Elysium::Core::Template::System::uint16_t StartIndex = SubtableCode << (SubtableBits - RemainingBits);

			for (Elysium::Core::Template::System::uint16_t i = 0; i < EntryCount; ++i)
			{
				EntryReference Entry = _Table[SubtableOffset + StartIndex + i];
				Entry._Operation = 0;
				Entry._Value = Symbol;
				Entry._Length = CodeLength;
			}
		}
	public:
		Elysium::Core::Template::System::uint8_t _CodeLengths[AlphabetLength];
		Elysium::Core::Template::System::uint16_t _CanonicalCodes[AlphabetLength];

		ContainerType _Table;
	};
}
#endif
