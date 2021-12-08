/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPEECH_API

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/System.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifdef ELYSIUMCORESPEECH_EXPORTS
#define ELYSIUM_CORE_SPEECH_API __declspec(dllexport)
#else
#define ELYSIUM_CORE_SPEECH_API __declspec(dllimport)
#endif
#elif defined ELYSIUM_CORE_OS_ANDROID

#elif defined ELYSIUM_CORE_OS_LINUX

#elif defined ELYSIUM_CORE_OS_MAC

#else
#error "unsupported os"
#endif

#endif
