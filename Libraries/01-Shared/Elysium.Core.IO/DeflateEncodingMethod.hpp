/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_DEFLATE_DEFLATEENCODINGMETHOD
#define ELYSIUM_CORE_IO_COMPRESSION_DEFLATE_DEFLATEENCODINGMETHOD

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Compression::Deflate
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class DeflateEncodingMethod : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
	enum class DeflateEncodingMethod
#else
#error "undefined os"
#endif
	{
		Store = 0,
		Static = 1,
		Dynamic = 2,
		Reserved = 3
	};
}
#endif
