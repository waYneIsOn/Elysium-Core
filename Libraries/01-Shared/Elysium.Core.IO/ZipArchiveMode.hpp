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

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class ZipArchiveMode : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
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
