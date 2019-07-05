/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_COMPRESSION_HUFFMANTREE
#define ELYSIUM_CORE_IO_COMPRESSION_HUFFMANTREE

#ifndef ELYSIUM_CORE_IO_COMPRESSION_HUFFMANNODE
#include "HuffmanNode.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			namespace Compression
			{
				class HuffmanTree
				{
				public:
					//HuffmanTree();
					//~HuffmanTree();
				private:
					HuffmanNode _Root;
				};
			}
		}
	}
}
#endif
