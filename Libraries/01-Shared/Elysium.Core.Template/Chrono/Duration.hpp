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
#include "../Concepts/Arithmetic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_RATIO
#include "../Numeric/Ratio.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
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
		constexpr Duration() = default;

		inline constexpr Duration(const Representation Value) noexcept
			: _Value(Value)
		{ }

		constexpr Duration(const Duration& Source) noexcept = default;

		constexpr Duration(Duration&& Right) noexcept = default;

		constexpr ~Duration() noexcept = default;
	public:
		constexpr Duration& operator=(const Duration& Source) = default;

		constexpr Duration& operator=(Duration&& Right) noexcept = default;
	public:
		inline constexpr const bool operator<=(const Duration Other)
		{
			return _Value <= Other._Value;
		}
	public:
		inline constexpr const bool operator<=(const RepresentationType Value)
		{
			return _Value <= Value;
		}
	public:
		inline constexpr const Representation GetCount() const noexcept
		{
			return _Value;
		}
	private:
		Representation _Value;
    };

	using NanoSeconds = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Nano>;
	using MicroSeconds = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Micro>;
	using MilliSeconds = Duration<Elysium::Core::Template::System::intMax_t, Elysium::Core::Template::Numeric::Milli>;
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
}
#endif
