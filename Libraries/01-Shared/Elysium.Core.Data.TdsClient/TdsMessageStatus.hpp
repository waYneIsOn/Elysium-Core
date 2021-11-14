/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_TDSCLIENT_TDSMESSAGESTATUS
#define ELYSIUM_CORE_DATA_TDSCLIENT_TDSMESSAGESTATUS

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
	enum class TdsMessageStatus : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TdsMessageStatus
#else
#error "undefined os"
#endif
	{
		Normal = 0x00,

		EndOfMessage = 0x01,

		ResetConnection = 0x08,

		ResetConnectionSkipTransaction = 0x10
	};
}
#endif
