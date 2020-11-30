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
	/*
	https://tools.ietf.org/html/rfc1951
	http://www.ece.iit.edu/~biitcomm/research/Variable-Length%20Codes/prefix%20codes%20decoding/Efficient%20Decoding%20of%20Prefix%20Codes.pdf
	*/
	class HuffmanTree
	{
	public:
		//HuffmanTree();
		//~HuffmanTree();
	private:
		static const int32_t MaximumLiteralTreeElements = 288;	// 256 literal codes, end of block code, 31 distance and length elements
		static const int32_t MaxiomumDistanceTreeElements = 32;	// 32 distances, fixed 5 bits, additional bits

		static const int32_t EndOfBlockCodeIndex = 256;
		static const int32_t NumberOfCodeLengthTreeElements = 19;

		int32_t _TableBits;	// 7 or 9 depending on the length of _Table
		int32_t _TableMask;	// last index of _Table: 127 (7) or 511 (9)

		int16_t* _Table;	// 128 (7) or 512 (9) bytes containing ...
		int16_t* _Left;		// 256 (7) or 1024 (9) bytes containing ...
		int16_t* _Right;	// 256 (7) or 1024 (9) bytes containing ...
		byte* _CodeLengths;	// sacrificing a bit of memory for faster lookups and also using this as a basis for table, bits, mask etc.
	};
}
#endif
