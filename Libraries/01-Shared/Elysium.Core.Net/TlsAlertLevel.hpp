/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_TLSALERTLEVEL
#define ELYSIUM_CORE_NET_SECURITY_TLSALERTLEVEL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Security
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class TlsAlertLevel : uint8_t
#elif defined(__ANDROID__)
	enum class TlsAlertLevel
#else
#error "undefined os"
#endif
	{
		Warning = 1,
		Fatal = 2
	};
}
#endif
