/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SYSTEM
#define ELYSIUM_CORE_SYSTEM

#if defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(__CYGWIN__)
#define ELYSIUM_CORE_OS_WINDOWS
#elif defined(__ANDROID__)
#define ELYSIUM_CORE_OS_ANDROID
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__))
#define ELYSIUM_CORE_OS_LINUX
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))
#define ELYSIUM_CORE_OS_MAC
#else
#error "unsupported os"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#define LITTLEENDIAN 1
#else
#error "unsupported os"
#endif

#endif
