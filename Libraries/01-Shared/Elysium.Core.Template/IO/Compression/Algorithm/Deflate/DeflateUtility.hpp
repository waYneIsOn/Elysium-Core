/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEUTILITY
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATEUTILITY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_HUFFMANTABLE
#include "../../Format/HuffmanCoding/HuffmanTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_SIMPLEHUFFMANTABLE
#include "../../Format/HuffmanCoding/SimpleHuffmanTable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../../Numeric/NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::Deflate
{
	// @ToDo: think about a better name!
	class DeflateUtility
	{
	public:
		inline static constexpr Elysium::Core::Template::System::size MaximumUncompressedBlockLength =
			Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::uint16_t>::Maximum;
	public:
		using CodeLengthTreeType = Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTable<Elysium::Core::Template::System::uint8_t, 7, 19, 7, 0>;
		using LiteralTreeType = Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTable<Elysium::Core::Template::System::uint16_t, 15, 288, 9, 2048>;
		using DistanceTreeType = Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::HuffmanTable<Elysium::Core::Template::System::uint8_t, 15, 32, 5, 256>;

		using CodeLengthTreeSymbolType = CodeLengthTreeType::SymbolType;
		using LiteralTreeSymbolType = LiteralTreeType::SymbolType;
		using DistanceTreeSymbolType = DistanceTreeType::SymbolType;

		using CodeLengthTreeEntryType = CodeLengthTreeType::EntryType;
		using LiteralTreeEntryType = LiteralTreeType::EntryType;
		using DistanceTreeEntryType = DistanceTreeType::EntryType;

		using CodeLengthTreeEntryReference = CodeLengthTreeType::EntryReference;
		using LiteralTreeEntryReference = LiteralTreeType::EntryReference;
		using DistanceTreeEntryReference = DistanceTreeType::EntryReference;

		using CodeLengthTreeConstEntryReference = CodeLengthTreeType::ConstEntryReference;
	public:
		// https://www.rfc-editor.org/info/rfc1951/#page-13
		// 3.2.7 Compression with dynamic Huffman codes (BTYPE=10)
		// (HCLEN + 4) x 3 bits: code lengths for the code length
		// 	alphabet given just above, in the order : 16, 17, 18,
		// 	0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
		inline static constexpr Elysium::Core::Template::System::uint8_t FixedCodeLengthPermutations[19] =
		{
			// repeat instructions
			16, 17, 18,

			// low-ish lengths
			0, 8, 7, 9, 6, 10, 5,

			// remaining lengths
			11, 4, 12, 3, 13, 2, 14, 1, 15
		};

		inline static constexpr Elysium::Core::Template::System::size HLITMaximum = 29;

		inline static constexpr Elysium::Core::Template::System::size HDISTMaximum = 31;

		inline static constexpr Elysium::Core::Template::System::size HCLENMaximum = 15;

		inline static constexpr Elysium::Core::Template::System::size BitsRequiredPerCodeLengthEntry = 3;

		inline static constexpr Elysium::Core::Template::System::size HCLENAddition = 4;

		inline static constexpr Elysium::Core::Template::System::size HLITAddition = 257;

		inline static constexpr Elysium::Core::Template::System::size HDISTAddition = 1;
	public:
		inline static constexpr Elysium::Core::Template::System::uint8_t StaticLiteralMaximumLength = 9;

		inline static constexpr Elysium::Core::Template::System::uint8_t StaticDistanceMaximumLength = 5;

		using StaticLiteralTreeType = Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::SimpleHuffmanTable<Elysium::Core::Template::System::uint16_t, StaticLiteralMaximumLength,
			288, StaticLiteralMaximumLength>;
		using StaticDistanceTreeType = Elysium::Core::Template::IO::Compression::Format::HuffmanCoding::SimpleHuffmanTable<Elysium::Core::Template::System::uint8_t, StaticDistanceMaximumLength,
			32, StaticDistanceMaximumLength>;

		inline static constexpr StaticLiteralTreeType StaticLiteralTree = StaticLiteralTreeType({
			// 0 - 143
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,

			// 144 – 255
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,

			// 256 - 279
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,

			// 280 - 287
			8, 8, 8, 8, 8, 8, 8, 8
		});

		inline static constexpr StaticDistanceTreeType StaticDistanceTree = StaticDistanceTreeType({
			5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
		});

		using StaticLiteralTreeSymbolType = StaticLiteralTreeType::SymbolType;
		using StaticDistanceTreeSymbolType = StaticDistanceTreeType::SymbolType;

		using StaticLiteralTreeEntryType = StaticLiteralTreeType::EntryType;
		using StaticDistanceTreeEntryType = StaticDistanceTreeType::EntryType;

		using StaticLiteralTreeEntryReference = StaticLiteralTreeType::EntryReference;
		using StaticDistanceTreeEntryReference = StaticDistanceTreeType::EntryReference;

		using StaticLiteralTreeConstEntryReference = StaticLiteralTreeType::ConstEntryReference;
		using StaticDistanceTreeConstEntryReference = StaticDistanceTreeType::ConstEntryReference;
	public:
		inline static constexpr Elysium::Core::Template::System::size LZ77HistoryBufferSize = 32768;
	};
}
#endif
