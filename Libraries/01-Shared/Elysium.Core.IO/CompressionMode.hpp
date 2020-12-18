/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONMODE
#define ELYSIUM_CORE_IO_COMPRESSION_COMPRESSIONMODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class CompressionMode : Elysium::Core::uint32_t
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
