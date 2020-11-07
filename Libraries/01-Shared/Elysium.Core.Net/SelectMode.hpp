/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_SELECTMODE
#define ELYSIUM_CORE_NET_SOCKETS_SELECTMODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SelectMode : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class SelectMode
#else
#error "undefined os"
#endif
	{
		SelectRead = 0,

		SelectWrite = 1,

		SelectError = 2
	};
}
#endif
