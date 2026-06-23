/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "../../../../Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGRAL
#include "../../../../Concepts/Integral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLEENTRY
#include "HuffmanTableEntry.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENA
#include "../../../../Memory/Scoped/Arena.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../../../../System/Compiler.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "../../../../TypeTraits/Conditional.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::HuffmanCoding
{
	template <Elysium::Core::Template::Concepts::HuffmanCodeable S, Elysium::Core::Template::System::uint8_t MaximumCodeLength, Elysium::Core::Template::System::size AlphabetLength,
		Elysium::Core::Template::System::uint8_t FastTableBits, Elysium::Core::Template::System::size ArenaPageLength>
	class HuffmanTable
	{
	private:
		inline static constexpr bool SubtablesRequired = MaximumCodeLength > FastTableBits;
	public:
		inline static constexpr Elysium::Core::Template::System::uint8_t _FastTableBits = FastTableBits;

		inline static constexpr Elysium::Core::Template::System::uint8_t _MaximumCodeLength = MaximumCodeLength;

		inline static constexpr Elysium::Core::Template::System::size FastTableLength = 1 << FastTableBits;
	public:
		/// <summary>
		/// Afaik an alphabet size larger than 4.294.967.295 does not exist in deflate, audio codecs, image compression etc. so uint64_t won't be used.
		/// @ToDo: If my "assumption" is wrong, add the type!
		/// </summary>
		using SymbolType = Elysium::Core::Template::TypeTraits::ConditionalType<(AlphabetLength <= 256), Elysium::Core::Template::System::uint8_t,
			Elysium::Core::Template::TypeTraits::ConditionalType<(AlphabetLength <= 65536), Elysium::Core::Template::System::uint16_t,
			Elysium::Core::Template::System::uint32_t>>;

		// stick with a singular type for now. HuffmanTable for code-lenghts is not going to waste a lot of memory.
		//using EntryType = Elysium::Core::Template::TypeTraits::ConditionalType<(SubtablesRequired), ComplexHuffmanTableEntry<SymbolType>, SimpleHuffmanTableEntry<SymbolType>>;
		using EntryType = HuffmanTableEntry<SymbolType>;

		using EntryPointer = EntryType*;

		using EntryReference = EntryType&;
	public:
		inline constexpr HuffmanTable()
			: _CodeLengths{}, _CanonicalCodes{}, _FastTable {}, 
			_SubtableArena(SubtablesRequired ? Elysium::Core::Template::Memory::Scoped::ArenaOptions(sizeof(EntryType) * ArenaPageLength, 1) : Elysium::Core::Template::Memory::Scoped::ArenaOptions(0, 0)),
			_Subtables(SubtablesRequired ? _SubtableArena.Push<EntryType>(ArenaPageLength) : nullptr)
		{ }

		constexpr HuffmanTable(const HuffmanTable& Source) = delete;

		constexpr HuffmanTable(HuffmanTable&& Right) noexcept = delete;

		constexpr ~HuffmanTable() = default;
	public:
		constexpr HuffmanTable<S, MaximumCodeLength, AlphabetLength, FastTableBits, ArenaPageLength>& operator=(const HuffmanTable& Source) = delete;

		constexpr HuffmanTable<S, MaximumCodeLength, AlphabetLength, FastTableBits, ArenaPageLength>& operator=(HuffmanTable&& Right) noexcept = delete;
	public:
		inline constexpr EntryReference operator[](const System::size Index) noexcept
		{
			if constexpr (SubtablesRequired)
			{
				EntryReference Entry = _FastTable[Index];
				if (nullptr == Entry._Subtable)
				{
					return Entry;
				}

				//Entry._Subtable[x]
				throw 1;
			}
			else
			{
				return _FastTable[Index];
			}
		}
	public:
		inline void BuildTable()
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
					_CanonicalCodes[Symbol] = NextCode[CodeLength]++;
					/*
					Elysium::Core::Template::System::uint16_t MSBFirstCode = NextCode[CodeLength]++;
					Elysium::Core::Template::System::uint16_t ReversedCode = ReverseBits(MSBFirstCode, CodeLength);
					_CanonicalCodes[Symbol] = ReversedCode;
					*/
				}
			}
			
			if constexpr (SubtablesRequired)
			{
				for (SymbolType Symbol = 0; Symbol < AlphabetLength; ++Symbol)
				{
					Elysium::Core::Template::System::uint8_t CodeLength = _CodeLengths[Symbol];
					if (0 == CodeLength)
					{
						continue;
					}

					Elysium::Core::Template::System::uint16_t CanonicalCode = _CanonicalCodes[Symbol];

					if (CodeLength < FastTableBits)
					{	// fast table
						for (Elysium::Core::Template::System::uint32_t i = 0; i < (1 << (FastTableBits - CodeLength)); ++i)
						{
							Elysium::Core::Template::System::size Index = (CanonicalCode << (FastTableBits - CodeLength)) | i;
							if (Index > FastTableLength)
							{	// @ToDo:
								throw 1;
							}

							EntryType& Entry = _FastTable[Index];
							
							if (0 != Entry._Length && CodeLength != Entry._Length && Symbol != Entry._Symbol)
							{	// @ToDo: overwriting! (this check might not be correct! some entries can be overwritten - I think lower > larger length? need to look it up!)
								throw 1;
							}
							
							Entry._Symbol = Symbol;
							Entry._Length = CodeLength;
							Entry._Subtable = nullptr;
							Entry._SubTableLength = 0;
						}
					}
					else
					{	//
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

					for (Elysium::Core::Template::System::uint32_t i = 0; i < (1 << (FastTableBits - CodeLength)); ++i)
					{
						Elysium::Core::Template::System::size Index = (CanonicalCode << (FastTableBits - CodeLength)) | i;
						if (Index > FastTableLength)
						{	// @ToDo:
							throw 1;
						}

						EntryType& Entry = _FastTable[Index];
						if (0 != Entry._Length && CodeLength != Entry._Length && Symbol != Entry._Symbol)
						{	// @ToDo: overwriting! (this check might not be correct! some entries can be overwritten - I think lower > larger length? need to look it up!)
							throw 1;
						}

						Entry._Symbol = Symbol;
						Entry._Length = CodeLength;
						Entry._Subtable = nullptr;
						Entry._SubTableLength = 0;
					}
				}
				
				// ensure table is fully populated
				for (Elysium::Core::Template::System::uint8_t i = 0; i < FastTableLength; ++i)
				{
					if (!_FastTable[i].GetIsValid())
					{	// @ToDo:
						throw 1;
					}
				}
			}
		}
	private:
		inline Elysium::Core::Template::System::uint16_t ReverseBits(Elysium::Core::Template::System::uint16_t Code, Elysium::Core::Template::System::uint16_t Length)
		{
			Elysium::Core::Template::System::uint16_t Result = 0;
			for (int i = 0; i < Length; i++)
			{
				Result = (Result << 1) | (Code & 1);
				Code >>= 1;
			}

			return Result;
		}
	public:
		Elysium::Core::Template::System::uint8_t _CodeLengths[AlphabetLength];
		Elysium::Core::Template::System::uint16_t _CanonicalCodes[AlphabetLength];

		EntryType _FastTable[FastTableLength];
		Elysium::Core::Template::Memory::Scoped::Arena _SubtableArena;
		EntryPointer _Subtables;

		//Elysium::Core::Template::System::uint8_t _MaxRemainingBitsPerSubtable[1 << FastTableBits];
	};
}
#endif