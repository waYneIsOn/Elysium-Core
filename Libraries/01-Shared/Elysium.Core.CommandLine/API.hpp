/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_API

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#if defined ELYSIUMCORECOMMANDLINE_EXPORTS
#define ELYSIUM_CORE_COMMANDLINE_API __declspec(dllexport)
#else
#define ELYSIUM_CORE_COMMANDLINE_API __declspec(dllimport)
#endif
#elif defined ELYSIUM_CORE_OS_LINUX
#define ELYSIUM_CORE_COMMANDLINE_API
#else
#error "unsupported os"
#endif

#endif
