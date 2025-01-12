/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifdef ELYSIUMCOREIOFILESYSTEMWATCHER_EXPORTS
#define ELYSIUM_CORE_IO_FILESYSTEM_WATCHER __declspec(dllexport)
#else
#define ELYSIUM_CORE_IO_FILESYSTEM_WATCHER __declspec(dllimport)
#endif
#elif defined ELYSIUM_CORE_OS_LINUX
#define ELYSIUM_CORE_IO_FILESYSTEM_WATCHER
#else
#error "unsupported os"
#endif

#endif
