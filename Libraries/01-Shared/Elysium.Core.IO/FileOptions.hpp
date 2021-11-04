/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILEOPTIONS
#define ELYSIUM_CORE_IO_FILEOPTIONS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class FileOptions : Elysium::Core::uint32_t
#elif defined(__ANDROID__)
	enum class FileOptions
#else
#error "undefined os"
#endif
	{
		//WriteThrough = -2147483648,
		None = 0,

		Encrypted = 16384,

		DeleteOnClose =	67108864,

		SequentialScan = 134217728,

		RandomAccess = 268435456,

		Asynchronous = 1073741824,	// FILE_FLAG_OVERLAPPED
	};

	inline FileOptions operator|(const FileOptions Left, const FileOptions Right)
	{
		return static_cast<FileOptions>(static_cast<Elysium::Core::uint32_t>(Left) | static_cast<Elysium::Core::uint32_t>(Right));
	}

	inline FileOptions operator&(const FileOptions Left, const FileOptions Right)
	{
		return static_cast<FileOptions>(static_cast<Elysium::Core::uint32_t>(Left) & static_cast<Elysium::Core::uint32_t>(Right));
	}
}
#endif
