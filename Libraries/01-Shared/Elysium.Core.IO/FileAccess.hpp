/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILEACCESS
#define ELYSIUM_CORE_IO_FILEACCESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class FileAccess : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class FileAccess
#else
#error "undefined os"
#endif
	{
		Read = 1,

		Write = 2
	};

	inline FileAccess operator|(const FileAccess Left, const FileAccess Right)
	{
		return static_cast<FileAccess>(static_cast<Elysium::Core::uint8_t>(Left) | static_cast<Elysium::Core::uint8_t>(Right));
	}

	inline FileAccess operator&(const FileAccess Left, const FileAccess Right)
	{
		return static_cast<FileAccess>(static_cast<Elysium::Core::uint8_t>(Left) & static_cast<Elysium::Core::uint8_t>(Right));
	}
}
#endif
