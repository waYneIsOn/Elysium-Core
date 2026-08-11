/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_ZLIB_ZLIBSTATE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_ZLIB_ZLIBSTATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../..//System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::ZLib
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class ZLibState
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class ZLibState
#else
#error "undefined os"
#endif
	{
		ReadingHeader = 0,

		DecodingBlock = 1,

		ReadingFooter = 2,

		Done = 3
	};
}
#endif
