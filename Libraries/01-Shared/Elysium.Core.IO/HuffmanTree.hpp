/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_HUFFMANTREE
#define ELYSIUM_CORE_IO_COMPRESSION_HUFFMANTREE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
	class HuffmanTree final
	{
	public:
		//HuffmanTree();
		HuffmanTree(const HuffmanTree& Source) = delete;
		HuffmanTree(HuffmanTree&& Right) noexcept = delete;
		//~HuffmanTree();

		HuffmanTree& operator=(const HuffmanTree& Source) = delete;
		HuffmanTree& operator=(HuffmanTree&& Right) noexcept = delete;
	private:
		static constexpr const Elysium::Core::int32_t MaximumLiteralTreeElements = 288;	// 256 literal codes, end of block code, 31 distance and length elements
		static constexpr const Elysium::Core::int32_t MaximumDistanceTreeElements = 32;	// 32 distances, fixed 5 bits, additional bits

		static constexpr const Elysium::Core::int32_t EndOfBlockCodeIndex = 256;
		static constexpr const Elysium::Core::int32_t NumberOfCodeLengthTreeElements = 19;

		Elysium::Core::int32_t _TableBits;	// 7 or 9 depending on the length of _Table
		Elysium::Core::int32_t _TableMask;	// last index of _Table: 127 (7) or 511 (9)

		Elysium::Core::int16_t* _Table;	// 128 (7) or 512 (9) bytes containing ...
		Elysium::Core::int16_t* _Left;		// 256 (7) or 1024 (9) bytes containing ...
		Elysium::Core::int16_t* _Right;	// 256 (7) or 1024 (9) bytes containing ...
		byte* _CodeLengths;	// sacrificing a bit of memory for faster lookups and also using this as a basis for table, bits, mask etc.
	};
}
#endif
