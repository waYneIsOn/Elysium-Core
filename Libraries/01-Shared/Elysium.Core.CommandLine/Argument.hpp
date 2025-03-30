/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_ARGUMENT
#define ELYSIUM_CORE_COMMANDLINE_ARGUMENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_SYMBOL
#include "Symbol.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::CommandLine
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class Argument final
		: public Symbol
	{
	public:
		constexpr Argument() = delete;

		constexpr Argument(const Argument& Source) = delete;

		constexpr Argument(Argument&& Right) noexcept = delete;

		constexpr virtual ~Argument() = default;
	public:
		constexpr Argument& operator=(const Argument& Source) = delete;

		constexpr Argument& operator=(Argument&& Right) noexcept = delete;
	private:
	};
}
#endif
