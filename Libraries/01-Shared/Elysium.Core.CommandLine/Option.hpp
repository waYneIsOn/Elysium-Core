/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COMMANDLINE_OPTION
#define ELYSIUM_CORE_COMMANDLINE_OPTION

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
	class Option
		: public Symbol
	{
	public:
		constexpr Option() = delete;

		constexpr Option(const char8_t* Name, const char8_t* Description = nullptr);

		constexpr Option(const Option& Source) = delete;

		constexpr Option(Option&& Right) noexcept = delete;

		constexpr virtual ~Option() = default;
	public:
		constexpr Option& operator=(const Option& Source) = delete;

		constexpr Option& operator=(Option&& Right) noexcept = delete;
	private:

	};

	template<class T>
	inline constexpr Option<T>::Option(const char8_t* Name, const char8_t* Description)
		: Elysium::Core::CommandLine::Symbol::Symbol(Name, Description)
	{ }
}
#endif
