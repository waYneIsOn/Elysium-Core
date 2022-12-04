/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#define ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM

#ifdef _MSC_VER
#pragma once
#endif

#if defined _WIN32 || defined _WIN64 || defined __WIN32__ || defined __TOS_WIN__ || defined __WINDOWS__ || defined __CYGWIN__
	#define ELYSIUM_CORE_OS_WINDOWS
#elif defined __ANDROID__ || defined __ANDROID_API__
	#define ELYSIUM_CORE_OS_ANDROID
#elif defined linux || defined __linux || defined __linux__  || defined __gnu_linux__
	#define ELYSIUM_CORE_OS_LINUX
#elif defined _MAC || defined macintosh || defined Macintosh || (defined __APPLE__ && defined __MACH__)
	#define ELYSIUM_CORE_OS_MAC
#else
	#error "unsupported os"
#endif

#if defined _WIN64 || defined __aarch64__ || defined __x86_64__
	#define ELYSIUM_CORE_BITNESS 64
#elif defined _WIN32 || defined __WIN32__ || defined __arm__ || defined __i386__
	#error "32bit is not supported"
#else
	#error "unsupported os regarding bitness"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS || defined ELYSIUM_CORE_OS_ANDROID
	#define ELYSIUM_CORE_LITTLEENDIAN 1
#else
	#error "unsupported os regarding endian"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS

#elif defined ELYSIUM_CORE_OS_ANDROID
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_DIAGNOSTICS
	#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_OID
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_SECURITY (tls etc.)
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_THREADING
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_THREADPOOL

#else
#error "unsupported os"
#endif
/*
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_ACTIVATOR
#include "../Elysium.Core.Template/Activator.hpp"
#endif

#define ELYSIUM_CORE_DEFAULT_FRIEND_CLASSES friend class Elysium::Core::Template::Memory::Activator;
*/
#endif
