/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_TDSCLIENT_TDSVERSION
#define ELYSIUM_CORE_DATA_TDSCLIENT_TDSVERSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Data::TdsClient
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class TdsVersion : Elysium::Core::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TdsVersion
#else
#error "undefined os"
#endif
	{
		v7_0
	};
}
#endif
