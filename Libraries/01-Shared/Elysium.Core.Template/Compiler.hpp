/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#define ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#if defined _MSC_VER	
	#define ELYSIUM_CORE_COMPILER_MSVC
#elif defined __clang__
	#define ELYSIUM_CORE_COMPILER_CLANG
#elif defined __INTEL_
	#define ELYSIUM_CORE_COMPILER_INTEL
#elif defined __GNUC__
	#define ELYSIUM_CORE_COMPILER_GCC
#else
	#error "Unhandled compiler"
#endif

namespace Elysium::Core::Template::System
{
	class Compiler
	{
	public:
		constexpr Compiler() noexcept = delete;

		Compiler(const Compiler& Source) = delete;

		Compiler(Compiler&& Right) noexcept = delete;

		~Compiler() = delete;
	public:

	public:
		static constexpr Elysium::Core::Template::System::int32_t GetLine() noexcept;

		static constexpr Elysium::Core::Template::System::int32_t GetColumn() noexcept;

		static constexpr char8_t* GetFileName() noexcept;

		static constexpr char8_t* GetFunctionName() noexcept;
	public:
#if defined ELYSIUM_CORE_COMPILER_MSVC
		inline static constexpr const char8_t* Name = u8"Microsoft Visual C++";
#elif defined ELYSIUM_CORE_COMPILER_CLANG
		inline static constexpr const char8_t* Name = u8"LLVM C compiler";
#elif defined ELYSIUM_CORE_COMPILER_INTEL
		inline static constexpr const char8_t* Name = u8"Intel C/C++ compiler";
#elif defined ELYSIUM_CORE_COMPILER_GCC
		inline static constexpr const char8_t* Name = u8"GNU C compiler";
#else
	#error "Unhandled compiler"
#endif
	};

	inline constexpr Elysium::Core::Template::System::int32_t Elysium::Core::Template::System::Compiler::GetLine() noexcept
	{
#if defined ELYSIUM_CORE_COMPILER_MSVC
		// @ToDo: under which conditions does this function throw? what does it throw? can I catch it?
		return __builtin_LINE();
#else
#error "unsupported compiler"
#endif
	}

	inline constexpr Elysium::Core::Template::System::int32_t Compiler::GetColumn() noexcept
	{
#if defined ELYSIUM_CORE_COMPILER_MSVC
		// @ToDo: under which conditions does this function throw? what does it throw? can I catch it?
		return __builtin_COLUMN();
#else
#error "unsupported compiler"
#endif
	}

	inline constexpr char8_t* Compiler::GetFileName() noexcept
	{
#if defined ELYSIUM_CORE_COMPILER_MSVC
		// @ToDo: under which conditions does this function throw? what does it throw? can I catch it?
		return (char8_t*)__builtin_FILE();
#else
#error "unsupported compiler"
#endif
	}

	inline constexpr char8_t* Compiler::GetFunctionName() noexcept
	{
#if defined ELYSIUM_CORE_COMPILER_MSVC
		// @ToDo: under which conditions does this function throw? what does it throw? can I catch it?
		return (char8_t*)__builtin_FUNCTION();
#else
#error "unsupported compiler"
#endif
	}
}
#endif
