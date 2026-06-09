/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKTYPE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../..//System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::Deflate
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class DeflateBlockType
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class DeflateBlockType
#else
#error "undefined os"
#endif
	{
		Uncompressed = 0,

		FixedHuffmanCodes = 1,

		DynamicHuffmanCodes = 2,

		Invalid = 3
	};
}
#endif
