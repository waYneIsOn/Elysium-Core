/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_SYSTEM
#define ELYSIUM_CORE_GLOBALIZATION_SYSTEM

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core.Template/System.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif
/*
#ifndef _WINNLS_
#include <WinNls.h>
#endif
*/
#define ELYSIUM_CORE_GLOBALIZATION_LOCALE_INVARIANT LOCALE_INVARIANT
#define ELYSIUM_CORE_GLOBALIZATION_LOCALE_CUSTOM_DEFAULT LOCALE_CUSTOM_DEFAULT

#elif defined(ELYSIUM_CORE_OS_ANDROID)
#define ELYSIUM_CORE_GLOBALIZATION_LOCALE_INVARIANT 0
#define ELYSIUM_CORE_GLOBALIZATION_LOCALE_CUSTOM_DEFAULT 0

#else
#error "undefined os"
#endif

#endif
