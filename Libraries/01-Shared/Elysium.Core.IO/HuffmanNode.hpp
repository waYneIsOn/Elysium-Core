/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_COMPRESSION_HUFFMANNODE
#define ELYSIUM_CORE_IO_COMPRESSION_HUFFMANNODE

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
				class HuffmanNode
				{
				public:
					HuffmanNode(HuffmanNode* Parent, char Char);
					~HuffmanNode();

					//HuffmanNode* GetParent();
					//HuffmanNode* GetLeft();
					//HuffmanNode* GetRight();

					//char GetChar();
					//int GetFrequency();
				private:
					HuffmanNode* _Parent;
					HuffmanNode* _Children;

					byte _Char;
					int _Frequency;
				};
			}
		}
	}
}
#endif
