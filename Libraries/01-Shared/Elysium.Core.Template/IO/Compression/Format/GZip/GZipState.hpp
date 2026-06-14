/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPSTATE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPSTATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../..//System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::GZip
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class GZipState
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class GZipState
#else
#error "undefined os"
#endif
	{
		ReadingFixedHeader = 0,

		ReadingOptionalHeaderExtra = 1,

		ReadingOptionalHeaderName = 2,

		ReadingOptionalHeaderComment = 3,

		ReadingOptionalHeaderCrc = 4,

		DecodingBlock = 5,

		ReadingFooter = 6,

		Done = 7
	};
}
#endif
