/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_LINQ_API

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core.Template/System.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifdef ELYSIUMCORELINQ_EXPORTS
#define ELYSIUM_CORE_LINQ_API __declspec(dllexport)
#else
#define ELYSIUM_CORE_LINQ_API __declspec(dllimport)
#endif
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#elif defined(ELYSIUM_CORE_OS_LINUX)

#elif defined(ELYSIUM_CORE_OS_MAC)

#else
#error "unsupported os"
#endif

#endif
