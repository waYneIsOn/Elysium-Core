/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPVERSIONNEEDED
#define ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPVERSIONNEEDED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Compression::Zip
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ZipVersionNeeded : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
	enum class ZipVersionNeeded
#else
#error "undefined os"
#endif
	{
		Default = 10,
		VolumeLabel = 11,
		Folder = 20,
		Deflate64 = 21,
		PKWAREDclImplode = 25,
		PatchDataSet = 27,
		Zip64Extension = 45,
		BZIP2 = 46,
		DES = 50,
		AES = 51,
		NonOAEP = 61,
		CentralDirectory = 62,
		LZMA = 63
	};
}
#endif
