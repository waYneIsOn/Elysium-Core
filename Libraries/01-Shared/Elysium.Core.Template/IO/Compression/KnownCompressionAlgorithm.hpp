/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_KNOWNCOMPRESSIONALGORITHM
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_KNOWNCOMPRESSIONALGORITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class KnownCompressionAlgorithm
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class FileAccess
#else
#error "undefined os"
#endif
	{
		Deflate = 1,

		Brotli = 2,

		Zopfli = 3,
	};
}
#endif
