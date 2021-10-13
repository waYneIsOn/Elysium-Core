/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTABLE
#define ELYSIUM_CORE_IO_COMPRESSION_HUFFMANCODING_HUFFMANTABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

namespace Elysium::Core::IO::Compression::HuffmanCoding
{
	/// <summary>
	/// Represents a huffman-tree in form of a lookup-table.
	/// </summary>
	class ELYSIUM_CORE_API HuffmanTable final
	{
	public:
		HuffmanTable();
		HuffmanTable(const HuffmanTable& Source) = delete;
		HuffmanTable(HuffmanTable&& Right) noexcept = delete;
		~HuffmanTable();

		HuffmanTable& operator=(const HuffmanTable& Source) = delete;
		HuffmanTable& operator=(HuffmanTable&& Right) noexcept = delete;
	private:
		/*
		static const Elysium::Core::uint32_t MaximumLiteralTreeElements = 288;	// 256 literal codes, end of block code, 31 distance and length elements
		static const Elysium::Core::uint32_t MaximumDistanceTreeElements = 32;	// 32 distances, fixed 5 bits, additional bits

		static const Elysium::Core::uint32_t EndOfBlockCodeIndex = 256;
		static const Elysium::Core::uint32_t NumberOfCodeLengthTreeElements = 19;

		Elysium::Core::uint32_t _TableBits;	// 7 or 9 depending on the length of _Table
		Elysium::Core::uint32_t _TableMask;	// last index of _Table: 127 (7) or 511 (9)

		Elysium::Core::uint16_t* _Table;	// 128 (7) or 512 (9) bytes containing ...
		Elysium::Core::uint16_t* _Left;		// 256 (7) or 1024 (9) bytes containing ...
		Elysium::Core::uint16_t* _Right;	// 256 (7) or 1024 (9) bytes containing ...
		byte* _CodeLengths;	// sacrificing a bit of memory for faster lookups and also using this as a basis for table, bits, mask etc.
		*/
	};
}
#endif
