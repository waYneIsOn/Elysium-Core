/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONLEVEL
#define ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONLEVEL

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			namespace Compression
			{
				enum class CompressionLevel : long
				{
					Optimal = 1,
					Fastest = 2,
					NoCompression = 3,
				};
			}
		}
	}
}
#endif
