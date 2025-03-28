/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_API

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM
#include "../Elysium.Core.Template/System.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifdef ELYSIUMCORESERVICEPROCESS_EXPORTS
#define ELYSIUM_CORE_SERVICEPROCESS_API __declspec(dllexport)
#else
#define ELYSIUM_CORE_SERVICEPROCESS_API __declspec(dllimport)
#endif
#elif defined ELYSIUM_CORE_OS_LINUX
#define ELYSIUM_CORE_SERVICEPROCESS_API
#else
#error "unsupported os"
#endif

#endif
