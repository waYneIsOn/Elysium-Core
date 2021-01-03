/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIP_COMPRESSIONMETHOD
#define ELYSIUM_CORE_IO_COMPRESSION_ZIP_COMPRESSIONMETHOD

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Compression::Zip
{
	#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class CompressionMethod : Elysium::Core::uint16_t
	#elif defined(__ANDROID__)
	enum class CompressionMethod
	#else
	#error "undefined os"
	#endif
	{
		Store = 0,
		Unshrink = 1,
		ReduceFactor1 = 2,
		ReduceFactor2 = 3,
		ReduceFactor3 = 4,
		ReduceFactor4 = 5,
		Implode = 6,
		Tokenize = 7,
		Deflate = 8,
		Deflate64 = 9,
		PKWARE = 10,
		ReservedByPKWARE11 = 11,
		Bzip2 = 12,
		ReservedByPKWARE13 = 13,
		LZMA = 14,
		ReservedByPKWARE15 = 15,
		CMPSCCompressed = 16,
		ReservedByPKWARE17 = 17,
		IBMTerse = 18,
		IBMLZ77 = 19,
		Deprecated20 = 20,
		ZStandard = 93,
		Mp3 = 94,
		XZCompressed = 95,
		JPEG = 96,
		WavPack = 97,
		PPMd = 98,
		AEx = 99
	};
}
#endif
