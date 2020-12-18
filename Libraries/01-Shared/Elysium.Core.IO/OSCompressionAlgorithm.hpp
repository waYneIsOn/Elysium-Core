/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_OSCOMPRESSIONALGORITHM
#define ELYSIUM_CORE_IO_COMPRESSION_OSCOMPRESSIONALGORITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class OSCompressionAlgorithm : Elysium::Core::uint32_t
#elif defined(__ANDROID__)
	enum class OSCompressionAlgorithm
#else
#error "undefined os"
#endif
	{
		MSZIP = 2,
		XPRESS = 3,
		XPRESS_HUFF = 4,
		LZMS = 5,
	};
}
#endif
