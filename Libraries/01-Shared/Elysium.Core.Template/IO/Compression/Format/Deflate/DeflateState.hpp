/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATESTATE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATESTATE

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
	enum class DeflateState
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class DeflateState
#else
#error "undefined os"
#endif
	{
		ReadingBlockHeader = 0,

		// uncompressed
		ReadingUncompressedHeaderFields,

		ReadingUncompressedData,

		// fixed huffman
		DecompressingStaticHuffman,

		// dynamic huffman
		ReadingDynamicHuffmanHeaderFields,

		BuildingCodeLengthTable,

		BuildingLiteralAndDistanceTables,

		DecompressingDynamicHuffman,

		// invalid
		// ...

		Done
	};
}
#endif
