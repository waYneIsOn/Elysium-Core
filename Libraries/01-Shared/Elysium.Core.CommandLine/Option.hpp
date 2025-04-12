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

#ifndef ELYSIUM_CORE_COMMANDLINE_ARGUMENT
#include "Argument.hpp"
#endif

#ifndef ELYSIUM_CORE_COMMANDLINE_ARGUMENTARITY
#include "ArgumentArity.hpp"
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
	class IOption
	{
	public:
		constexpr virtual ~IOption() = default;
	};

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class Option
		: public IOption, Symbol
	{
		friend class Command;
	public:
		constexpr Option() = delete;
	private:
		constexpr Option(const char8_t* Name, const char8_t* Description);
	public:
		constexpr Option(const Option& Source) = delete;

		constexpr Option(Option&& Right) noexcept = delete;

		constexpr virtual ~Option() = default;
	public:
		constexpr Option& operator=(const Option& Source) = delete;

		constexpr Option& operator=(Option&& Right) noexcept = delete;
	public:
		ArgumentArity& GetArity();
	public:
		/*
		template <class T>
		Argument<T>& AddArgument() noexcept;
		*/
	private:
		Argument<T> _Argument;
	};

	template<class T>
	inline constexpr Option<T>::Option(const char8_t* Name, const char8_t* Description)
		: Elysium::Core::CommandLine::Symbol::Symbol(Name, Description),
		_Argument(Name, Description)
	{ }

	template<class T>
	inline ArgumentArity& Option<T>::GetArity()
	{
		return _Argument.GetArity();
	}
}
#endif
