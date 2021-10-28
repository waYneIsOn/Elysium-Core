#include "SystemSpecific.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else
#error "unsupported os"
#endif


const Elysium::Core::int32_t Elysium::Core::SystemSpecific::GetLastErrorCode()
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	return GetLastError();
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else
#error "unsupported os"
#endif
}
