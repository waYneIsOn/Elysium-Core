/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONMODE
#define ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONMODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class CompressionMode : uint32_t
#elif defined(__ANDROID__)
	enum class CompressionMode
#else
#error "undefined os"
#endif
	{
		Decompress = 0,
		Compress = 1,
	};
}
#endif
