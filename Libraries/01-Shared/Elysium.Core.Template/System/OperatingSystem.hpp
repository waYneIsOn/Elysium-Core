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

#if defined (_GAMING_XBOX)
	// needs to be ahead of ELYSIUM_CORE_OS_WINDOWS as "_WIN32" and potentially others are also defined in windows!
	#define ELYSIUM_CORE_OS_XBOX

	#if defined (_GAMING_XBOX_XBOXONE)
	#define ELYSIUM_CORE_OS_XBOX_ONE
	#elif defined (_GAMING_XBOX_SCARLETT)
	#define ELYSIUM_CORE_OS_XBOX_SERIES
	#endif
#elif defined (_WIN32) || defined (_WIN64) || defined (__WIN32__) || defined (__TOS_WIN__) || defined (__WINDOWS__) || defined (__CYGWIN__)
	#define ELYSIUM_CORE_OS_WINDOWS
#elif defined (__ANDROID__ )|| defined (__ANDROID_API__)
	// needs to be ahead of ELYSIUM_CORE_OS_LINUX as "linux" is also defined in android!
	#define ELYSIUM_CORE_OS_ANDROID
#elif defined(linux) || defined (__linux) || defined (__linux__)  || defined (__gnu_linux__)
	#define ELYSIUM_CORE_OS_LINUX
	
	// SteamOS, ChromeOS etc. fall in this case
#elif defined (__APPLE__) && defined (__MACH__)
	#define ELYSIUM_CORE_OS_APPLE

	#include <TargetConditionals.h>

	#if TARGET_OS_MACCATALYST
		#define ELYSIUM_CORE_OS_APPLE_MACCATALYST
	#elif TARGET_OS_OSX
		#define ELYSIUM_CORE_OS_APPLE_MACOS
	#elif TARGET_OS_IOS
		#define ELYSIUM_CORE_OS_APPLE_IOS
	#elif TARGET_OS_TV
		#define ELYSIUM_CORE_OS_APPLE_TV
	#elif TARGET_OS_WATCH
		#define ELYSIUM_CORE_OS_APPLE_WATCH
	#elif TARGET_OS_VISION
		#define ELYSIUM_CORE_OS_APPLE_VISION
	#else
		#error "unsupported apple os"
	#endif
#elif defined (__PS3)
	#define ELYSIUM_CORE_OS_PLAYSTATION
	#define ELYSIUM_CORE_OS_PS3
#elif defined (__ORBIS__)
	#define ELYSIUM_CORE_OS_PLAYSTATION
	#define ELYSIUM_CORE_OS_PS4
#elif defined (__PROSPERO__)
	#define ELYSIUM_CORE_OS_PLAYSTATION
	#define ELYSIUM_CORE_OS_PS5
#elif defined (__SWITCH__)
	#define ELYSIUM_CORE_OS_NINTENDO
	#define ELYSIUM_CORE_OS_NINTENDO_SWITCH
#else
	#error "unsupported os"
#endif

#if defined (_WIN64) || defined (__aarch64__) || defined (_M_ARM64) || defined (__x86_64__) || defined (_M_X64 )
	#define ELYSIUM_CORE_BITNESS 64
#elif defined (_WIN32) || defined (__WIN32__) ||defined  (__arm__) || defined (__i386__) || defined (_M_IX86)
	#define ELYSIUM_CORE_BITNESS 32
#else
	#error "unsupported os regarding bitness"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#define ELYSIUM_CORE_LITTLEENDIAN 1
#elif defined ELYSIUM_CORE_OS_LINUX
	#define ELYSIUM_CORE_LITTLEENDIAN 1
	// @ToDo: need to look into this. some linux distros might not be little endian!
#elif defined ELYSIUM_CORE_OS_ANDROID
	#define ELYSIUM_CORE_LITTLEENDIAN 1
#else
	#error "unsupported os regarding endian"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS

#elif defined ELYSIUM_CORE_OS_LINUX

#elif defined ELYSIUM_CORE_OS_ANDROID
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_DIAGNOSTICS
	#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_OID
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_SECURITY (tls etc.)
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_THREADING
	//#define ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_THREADPOOL
#else
#error "unsupported os regarding fallbacks"
#endif

namespace Elysium::Core::Template::System
{
	class OperatingSystem
	{
	public:
		constexpr OperatingSystem() noexcept = delete;

		OperatingSystem(const OperatingSystem& Source) = delete;

		OperatingSystem(OperatingSystem&& Right) noexcept = delete;

		constexpr ~OperatingSystem() = delete;
	public:
		OperatingSystem& operator=(const OperatingSystem& Source) noexcept;

		OperatingSystem& operator=(OperatingSystem&& Right) noexcept;
		/*
	public:
		const PlatformID GetPlatform() const;

		const Version& GetVersion() const;
	public:
		const bool IsWindows() const;
	private:
		PlatformID _PlatformId;
		Version _Version;
		*/
	};
}
#endif
