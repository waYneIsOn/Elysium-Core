/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESHARE
#define ELYSIUM_CORE_IO_FILESHARE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class FileShare : Elysium::Core::uint32_t
#elif defined(__ANDROID__)
	enum class FileShare
#else
#error "undefined os"
#endif
	{
		None = 0,

		Read = 1,

		Write = 2,

		ReadWrite = 3,

		Delete = 4,

		Inheritable = 16,
	};
}
#endif
