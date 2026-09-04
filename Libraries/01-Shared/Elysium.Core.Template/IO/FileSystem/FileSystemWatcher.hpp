/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMWATCHER
#define ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMWATCHER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMWATCHER_WINDOWS
#include "FileSystemWatcher.Windows.hpp"
#endif
#endif

#endif
