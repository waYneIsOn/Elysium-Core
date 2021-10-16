/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SYSTEM
#define ELYSIUM_CORE_SYSTEM

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(__CYGWIN__)
#define ELYSIUM_CORE_OS_WINDOWS
#elif defined(__ANDROID__) || defined(__ANDROID_API__)
#define ELYSIUM_CORE_OS_ANDROID
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__))
#define ELYSIUM_CORE_OS_LINUX
#elif defined(_MAC) || defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))
#define ELYSIUM_CORE_OS_MAC
#else
#error "unsupported os"
#endif

#if defined(_MSC_VER)
#define ELYSIUM_CORE_COMPILER u8"Microsoft Visual C++"
#elif defined(__clang__)
#define ELYSIUM_CORE_COMPILER u8"LLVM C compiler"
#elif defined(__INTEL_)
#define ELYSIUM_CORE_COMPILER u8"Intel C/C++ compiler"
#elif defined(__GNUC__)
#define ELYSIUM_CORE_COMPILER u8"GNU C compiler"
#else
#error "unsupported compiler"
#endif

#if defined(_WIN64) || defined(__aarch64__) || defined(__x86_64__)
#define ELYSIUM_CORE_BITNESS 64
#elif defined(_WIN32) || defined(__WIN32__) || defined(__arm__) || defined(__i386__)
#error "32bit is not supported"
#else
#error "unsupported os regarding bitness"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS) || defined(ELYSIUM_CORE_OS_ANDROID)
#define ELYSIUM_CORE_LITTLEENDIAN 1
#else
#error "unsupported os regarding endian"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#define ELYSIUM_CORE_OS_HAS_API_GLOBALIZATION true
#define ELYSIUM_CORE_OS_HAS_API_OID true
#define ELYSIUM_CORE_OS_HAS_API_THREADING true
#define ELYSIUM_CORE_OS_HAS_API_THREADPOOL true
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else
#error "unsupported os"
#endif

#endif
