/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_PROTECTIONLEVEL
#define ELYSIUM_CORE_NET_SECURITY_PROTECTIONLEVEL

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Net::Security
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ProtectionLevel : uint32_t
#elif defined(__ANDROID__)
	enum class ProtectionLevel
#else
#error "undefined os"
#endif
	{
		None = 0,
		Sign = 1,
		EncryptAndSign = 2
	};
}
#endif
