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
#if defined _MSC_VER
		inline static constexpr const char8_t* Name = u8"Microsoft Visual C++";
#elif defined __clang__
		inline static constexpr const char8_t* Name = u8"LLVM C compiler";
#elif defined __INTEL_
		inline static constexpr const char8_t* Name = u8"Intel C/C++ compiler";
#elif defined __GNUC__
		inline static constexpr const char8_t* Name = u8"GNU C compiler";
#else
		inline static constexpr const char8_t* Name = u8"Unhandled compiler";
#endif
	};
}
#endif
