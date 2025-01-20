/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DURATION
#define ELYSIUM_CORE_TEMPLATE_CHRONO_DURATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ARITHMETIC
#include "../Arithmetic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_RATIO
#include "../Ratio.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Primitives.hpp"
#endif

namespace Elysium::Core::Template::Chrono
{
    /// <summary>
    /// Represents a time interval.
    /// </summary>
    /// <typeparam name="Representation"></typeparam>
    /// <typeparam name="LocalPeriodInSeconds"></typeparam>
    template <Elysium::Core::Template::Concepts::Arithmetic Representation, class Period = Numeric::Ratio<1>>
    class Duration
    {
	public:
		using RepresentationType = Representation;
		using PeriodType = Period;
	public:
		constexpr Duration() = delete;

		constexpr Duration(const Representation Value) noexcept;

		constexpr Duration(const Duration& Source) noexcept;

		constexpr Duration(Duration&& Right) noexcept;

		constexpr ~Duration() noexcept;
	public:
		constexpr Duration& operator=(const Duration& Source);

		constexpr Duration& operator=(Duration&& Right) noexcept;
	public:
		constexpr const Representation GetCount() const noexcept;
	private:
		Representation _Value;
    };

	using NanoSeconds = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Nano>;
	using MicroSeconds = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Micro>;
	using MilliSeconds = Duration < Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Milli>;
	using Seconds = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Ratio<1>>;
	using Minutes = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Ratio<60>>;
	using Hours = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Ratio<3600>>;
	using Days = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Ratio<86400>>;
	using Weeks = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Ratio<604800>>;

	/// <summary>
	/// Uses an average and equals 30.436875 days (exactly 1/12 of years).
	/// </summary>
	using Months = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Ratio<2629746>>;

	/// <summary>
	/// Uses an average and equals 365.2425 days (the average length of a Gregorian year).
	/// </summary>
	using Years = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Ratio<31556952>>;

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class Period>
	inline constexpr Duration<Representation, Period>::Duration(const Representation Value) noexcept
		: _Value(Value)
	{ }

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class Period>
	inline constexpr Duration<Representation, Period>::Duration(const Duration & Source) noexcept
		: _Value(Source._Value)
	{ }

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class Period>
	inline constexpr Duration<Representation, Period>::Duration(Duration && Right) noexcept
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class Period>
	inline constexpr Duration<Representation, Period>::~Duration() noexcept
	{ }

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class Period>
	inline constexpr Duration<Representation, Period>& Duration<Representation, Period>::operator=(const Duration & Source)
	{
		if (this != &Source)
		{
			_Value = Source._Value;
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class Period>
	inline constexpr Duration<Representation, Period>& Duration<Representation, Period>::operator=(Duration&& Right) noexcept
	{
		if (this != &Right)
		{
			_Value = Elysium::Core::Template::Functional::Move(Right._Value);
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class Period>
	inline constexpr const Representation Duration<Representation, Period>::GetCount() const noexcept
	{
		return _Value;
	}
}
#endif
