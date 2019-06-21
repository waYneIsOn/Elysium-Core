/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONMODE
#define ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONMODE

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			namespace Compression
			{
				enum class CompressionMode : long
				{
					Decompress = 0,
					Compress = 1,
				};
			}
		}
	}
}
#endif
