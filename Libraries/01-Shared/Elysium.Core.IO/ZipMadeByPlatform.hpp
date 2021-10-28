/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPMADEBYPLATFORM
#define ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPMADEBYPLATFORM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::IO::Compression::Zip
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class ZipMadeByPlatform : Elysium::Core::uint16_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class ZipMadeByPlatform
#else
#error "undefined os"
#endif
	{
		FAT = 0,
		Amiga = 1,
		OpenVMS = 2,
		Unix = 3,
		AtariST = 5,
		OS2HPFS = 6,
		Macintosh = 7,
		ZSystem = 8,
		CPM = 9,
		WindowsNTFS = 10,
		MVS = 11,
		VSE = 12,
		AcornRisc = 13,
		VFAT = 14,
		AlternateMVS = 15,
		BeOS = 16,
		Tandem = 17,
		OS400 = 18,
		DarwinOSX = 19,

		// unused from here on

		PossiblyWinZip = 20,

		PossiblySevenZip = 63,
	};
}
#endif
