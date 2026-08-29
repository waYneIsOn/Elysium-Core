/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../System/Compiler.hpp"
#endif

#if defined ELYSIUM_CORE_COMPILER_MSVC
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE_MSVC
#include "CoroutineHandle.MSVC.hpp"
#endif
#endif
#endif
