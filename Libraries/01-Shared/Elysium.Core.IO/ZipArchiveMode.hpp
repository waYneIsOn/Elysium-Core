/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVEMODE
#define ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVEMODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ZipArchiveMode : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class ZipArchiveMode
#else
#error "undefined os"
#endif
	{
		Read = 0,
		Create = 1,
		Update = 2
	};
}
#endif
