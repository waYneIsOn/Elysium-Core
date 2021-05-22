/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_INTERFACE
#define ELYSIUM_CORE_INTERFACE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#define interface struct __declspec(novtable)
/*
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#elif defined(ELYSIUM_CORE_OS_LINUX)

#elif defined(ELYSIUM_CORE_OS_MAC)
*/
#else
#error "unsupported os"
#endif

#endif
