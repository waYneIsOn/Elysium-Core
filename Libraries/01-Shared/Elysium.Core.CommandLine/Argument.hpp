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

#ifndef ELYSIUM_CORE_COMMANDLINE_ARGUMENTARITY
#include "ArgumentArity.hpp"
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

		constexpr Argument(const char8_t* Name, const char8_t* Description = nullptr);

		constexpr Argument(const Argument& Source) = delete;

		constexpr Argument(Argument&& Right) noexcept = delete;

		constexpr virtual ~Argument() = default;
	public:
		constexpr Argument& operator=(const Argument& Source) = delete;

		constexpr Argument& operator=(Argument&& Right) noexcept = delete;
	public:
		ArgumentArity& GetArity();

		const ArgumentArity& GetArity() const;
	private:
		ArgumentArity _Arity;
		//T _DefaultValue;
	};

	template<class T>
	inline constexpr Argument<T>::Argument(const char8_t* Name, const char8_t* Description)
		: Elysium::Core::CommandLine::Symbol::Symbol(Name, Description),
		_Arity(0, 0)
	{ }

	template<class T>
	inline ArgumentArity& Argument<T>::GetArity()
	{
		return _Arity;
	}

	template<class T>
	inline const ArgumentArity& Argument<T>::GetArity() const
	{
		return _Arity;
	}
}
#endif
