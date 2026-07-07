/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATECOMPRESSIONLEVEL
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_ALGORITHM_DEFLATE_DEFLATECOMPRESSIONLEVEL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::Deflate
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class DeflateCompressionLevel
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class DeflateCompressionLevel
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Stores all data in uncompressed blocks.
		/// </summary>
		Stored = 0,

		/// <summary>
		/// Compresses all data using static huffman tables.
		/// </summary>
		StaticOnly = 1,

		/// <summary>
		/// Compresses all data using calculated, dynamic huffman tables.
		/// </summary>
		DynamicOnly = 2,




		SelectOptimal = 3
	};
}
#endif
