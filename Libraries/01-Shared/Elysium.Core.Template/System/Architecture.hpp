/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_ARCHTECTURE
#define ELYSIUM_CORE_TEMPLATE_SYSTEM_ARCHTECTURE

#ifdef _MSC_VER
#pragma once
#endif

// Originally taken from: https://stackoverflow.com/questions/152016/detecting-cpu-architecture-compile-time
// Author: https://stackoverflow.com/users/14804593/freakanon
#if defined __x86_64__ || defined _M_X64
#define ELYSIUM_CORE_ARCHITECTURE_x86_64
#elif defined i386 || defined __i386__ || defined __i386 || defined _M_IX86
#define ELYSIUM_CORE_ARCHITECTURE_x86_32
#elif defined __ARM_ARCH_2__
#define ELYSIUM_CORE_ARCHITECTURE_ARM2
#elif defined __ARM_ARCH_3__ || defined __ARM_ARCH_3M__
#define ELYSIUM_CORE_ARCHITECTURE_ARM3
#elif defined __ARM_ARCH_4T__ || defined __TARGET_ARM_4T
#define ELYSIUM_CORE_ARCHITECTURE_ARM4T
#elif defined __ARM_ARCH_5_ || defined __ARM_ARCH_5E_
#define ELYSIUM_CORE_ARCHITECTURE_ARM5
#elif defined __ARM_ARCH_6T2_ || defined __ARM_ARCH_6T2_
#define ELYSIUM_CORE_ARCHITECTURE_ARM6T2
#elif defined __ARM_ARCH_6__ || defined __ARM_ARCH_6J__ || defined __ARM_ARCH_6K__ || defined __ARM_ARCH_6Z__ || defined __ARM_ARCH_6ZK__
#define ELYSIUM_CORE_ARCHITECTURE_ARM6
#elif defined __ARM_ARCH_7__ || defined __ARM_ARCH_7A__ || defined __ARM_ARCH_7R__ || defined __ARM_ARCH_7M__ || defined __ARM_ARCH_7S__
#define ELYSIUM_CORE_ARCHITECTURE_ARM7
#elif defined __ARM_ARCH_7A__ || defined __ARM_ARCH_7R__ || defined __ARM_ARCH_7M__ || defined __ARM_ARCH_7S__
#define ELYSIUM_CORE_ARCHITECTURE_ARM7A
#elif defined __ARM_ARCH_7R__ || defined __ARM_ARCH_7M__ || defined __ARM_ARCH_7S__
#define ELYSIUM_CORE_ARCHITECTURE_ARM7R
#elif defined __ARM_ARCH_7M__
#define ELYSIUM_CORE_ARCHITECTURE_ARM7M
#elif defined __ARM_ARCH_7S__
#define ELYSIUM_CORE_ARCHITECTURE_ARM7S
#elif defined __aarch64__ || defined _M_ARM64
#define ELYSIUM_CORE_ARCHITECTURE_ARM64
#elif defined mips || defined __mips__ || defined __mips
#define ELYSIUM_CORE_ARCHITECTURE_MIPS
#elif defined __sh__
#define ELYSIUM_CORE_ARCHITECTURE_SUPERH
#elif defined __powerpc || defined __powerpc__ || defined __powerpc64__ || defined __POWERPC__ || defined __ppc__ || defined __PPC__ || defined _ARCH_PPC
#define ELYSIUM_CORE_ARCHITECTURE_POWERPC
#elif defined __PPC64__ || defined __ppc64__ || defined(_ARCH_PPC64)
#define ELYSIUM_CORE_ARCHITECTURE_POWERPC64
#elif defined __sparc__ || defined __sparc
#define ELYSIUM_CORE_ARCHITECTURE_SPARC
#elif defined __m68k__
#define ELYSIUM_CORE_ARCHITECTURE_M68K
#else
#error "Unhandled architecture"
#endif

#if defined ELYSIUM_CORE_ARCHITECTURE_x86_32 || defined ELYSIUM_CORE_ARCHITECTURE_x86_64
#define ELYSIUM_CORE_ARCHITECTURE_ANY_X86
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM2 || defined ELYSIUM_CORE_ARCHITECTURE_ARM3 || defined ELYSIUM_CORE_ARCHITECTURE_ARM4T ||
    defined ELYSIUM_CORE_ARCHITECTURE_ARM5 || defined ELYSIUM_CORE_ARCHITECTURE_ARM6T2 || defined ELYSIUM_CORE_ARCHITECTURE_ARM6 ||
    defined ELYSIUM_CORE_ARCHITECTURE_ARM7 || defined ELYSIUM_CORE_ARCHITECTURE_ARM7A || defined ELYSIUM_CORE_ARCHITECTURE_ARM7R ||
    defined ELYSIUM_CORE_ARCHITECTURE_ARM7M || defined ELYSIUM_CORE_ARCHITECTURE_ARM7S || defined ELYSIUM_CORE_ARCHITECTURE_ARM64
#define ELYSIUM_CORE_ARCHITECTURE_ANY_ARM
#endif

namespace Elysium::Core::Template::System
{
	class Architecture
	{
	public:
		constexpr Architecture() noexcept = delete;

		Architecture(const Architecture& Source) = delete;

		Architecture(Architecture&& Right) noexcept = delete;

		~Architecture() = delete;
	public:
#if defined ELYSIUM_CORE_ARCHITECTURE_x86_64
        inline static constexpr const char8_t* Name = u8"x86_64";
#elif defined ELYSIUM_CORE_ARCHITECTURE_x86_32
        inline static constexpr const char8_t* Name = u8"x86_32";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM2
        inline static constexpr const char8_t* Name = u8"ARM2";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM3
        inline static constexpr const char8_t* Name = u8"ARM3";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM4T
        inline static constexpr const char8_t* Name = u8"ARM4T";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM5
        inline static constexpr const char8_t* Name = u8"ARM5"
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM6T2
        inline static constexpr const char8_t* Name = u8"ARM6T2";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM6
        inline static constexpr const char8_t* Name = u8"ARM6";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM7
        inline static constexpr const char8_t* Name = u8"ARM7";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM7A
        inline static constexpr const char8_t* Name = u8"ARM7A";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM7R
        inline static constexpr const char8_t* Name = u8"ARM7R";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM7M
        inline static constexpr const char8_t* Name = u8"ARM7M";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM7S
        inline static constexpr const char8_t* Name = u8"ARM7S";
#elif defined ELYSIUM_CORE_ARCHITECTURE_ARM64
        inline static constexpr const char8_t* Name = u8"ARM64";
#elif defined ELYSIUM_CORE_ARCHITECTURE_MIPS
        inline static constexpr const char8_t* Name = u8"MIPS";
#elif defined ELYSIUM_CORE_ARCHITECTURE_SUPERH
        inline static constexpr const char8_t* Name = u8"SUPERH";
#elif defined ELYSIUM_CORE_ARCHITECTURE_POWERPC
        inline static constexpr const char8_t* Name = u8"POWERPC";
#elif defined ELYSIUM_CORE_ARCHITECTURE_POWERPC64
        inline static constexpr const char8_t* Name = u8"POWERPC64";
#elif defined ELYSIUM_CORE_ARCHITECTURE_SPARC
        inline static constexpr const char8_t* Name = u8"SPARC";
#elif defined ELYSIUM_CORE_ARCHITECTURE_M68K
        inline static constexpr const char8_t* Name = u8"M68K";
#else
    #error "Unhandled architecture"
#endif
	};
}
#endif