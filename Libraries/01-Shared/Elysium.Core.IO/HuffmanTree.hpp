/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_COMPRESSION_HUFFMANTREE
#define ELYSIUM_CORE_IO_COMPRESSION_HUFFMANTREE

#ifndef _STDINT_H
#include <cstdint>
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			namespace Compression
			{
				/*
				http://www.ece.iit.edu/~biitcomm/research/Variable-Length%20Codes/prefix%20codes%20decoding/Efficient%20Decoding%20of%20Prefix%20Codes.pdf
				*/
				class HuffmanTree
				{
				public:
					//HuffmanTree();
					//~HuffmanTree();
				private:
					int32_t _TableBits;	// 7 or 9
					int32_t _TableMask;	// last index of _Table:	127 (7) or 511 (9)

					int16_t* _Table;	// 128 (7) or 512 (9) bytes containing ...
					int16_t* _Left;		// 256 (7) or 1024 (9) bytes containing ...
					int16_t* _Right;	// 256 (7) or 1024 (9) bytes containing ...
					byte* _CodeLengths;	// sacrificing a bit of memory for faster lookups
				};
			}
		}
	}
}
#endif
