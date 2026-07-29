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

		using EntryType = HuffmanDecodingTableEntry<S>;

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
			if constexpr (SubtablesRequired)
			{
				ConstEntryReference Entry = _Table[Index];
				return Entry;
				/*
				if (nullptr == Entry._Subtable)
				{
					return Entry;
				}

				// @ToDo
				//Entry._Subtable[x]
				throw 1;
				*/
			}
			else
			{
				return _Table[Index];
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
			for (Elysium::Core::Template::System::uint8_t Bits = 0; Bits < TableBits; ++Bits)
			{
				Left = (Left << 1) - BitLengthCount[Bits];
			}

			if (Left < 0)
			{	// @ToDo: oversubscribed
				//throw 1;
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
				_Table.Resize(FastTableLength);

				for (SymbolType Symbol = 0; Symbol < AlphabetLength; ++Symbol)
				{
					Elysium::Core::Template::System::uint8_t CodeLength = _CodeLengths[Symbol];
					if (0 == CodeLength)
					{
						continue;
					}

					Elysium::Core::Template::System::uint16_t CanonicalCode = _CanonicalCodes[Symbol];

					if (CodeLength <= TableBits)
					{	// fast table
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
					else
					{	// @ToDo
						throw 1;
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
					
					for (Elysium::Core::Template::System::uint32_t i = 0; i < (1 << (TableBits - CodeLength)); ++i)
					{
						Elysium::Core::Template::System::size Index = CanonicalCode | (i << CodeLength);
						if (Index >= FastTableLength)
						{	// @ToDo:
							throw 1;
						}

						EntryReference Entry = _Table[Index];
						Entry._Operation = 0;
						Entry._Value = Symbol;
						Entry._Length = CodeLength;
					}
				}
				/*
				// ensure table is fully populated
				for (Elysium::Core::Template::System::size i = 0; i < FastTableLength; ++i)
				{
					if (!_Table[i].GetIsValid())
					{	// @ToDo:
						throw 1;
					}
				}
				*/
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
	public:
		Elysium::Core::Template::System::uint8_t _CodeLengths[AlphabetLength];
		Elysium::Core::Template::System::uint16_t _CanonicalCodes[AlphabetLength];

		ContainerType _Table;
	};
}
#endif
