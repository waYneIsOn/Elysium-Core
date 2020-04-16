/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONLEVEL
#define ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONLEVEL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class CompressionLevel : uint32_t
#elif defined(__ANDROID__)
	enum class CompressionLevel
#else
#error "undefined os"
#endif
	{
		Optimal = 1,
		Fastest = 2,
		NoCompression = 3,
	};
}
#endif
