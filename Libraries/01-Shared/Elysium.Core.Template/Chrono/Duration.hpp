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

namespace Elysium::Core::Template::Chrono
{
    /// <summary>
    /// Represents a time interval.
    /// </summary>
    /// <typeparam name="Representation"></typeparam>
    /// <typeparam name="LocalPeriodInSeconds"></typeparam>
    template <Elysium::Core::Template::Concepts::Arithmetic Representation, class LocalPeriodInSeconds = Numeric::Ratio<1>>
    class Duration
    {
	public:
		constexpr Duration() = delete;

		constexpr Duration(const Representation Value);

		constexpr Duration(const Duration& Source);

		constexpr Duration(Duration&& Right) noexcept;

		constexpr ~Duration();
	public:
		constexpr Duration& operator=(const Duration& Source);

		constexpr Duration& operator=(Duration&& Right) noexcept;
	public:
		constexpr const Representation GetCount() const;
	private:
		Representation _Value;
    };

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class LocalPeriodInSeconds>
	inline constexpr Duration<Representation, LocalPeriodInSeconds>::Duration(const Representation Value)
		: _Value(Value)
	{ }

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class LocalPeriodInSeconds>
	inline constexpr Duration<Representation, LocalPeriodInSeconds>::Duration(const Duration & Source)
		: _Value(Source._Value)
	{ }

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class LocalPeriodInSeconds>
	inline constexpr Duration<Representation, LocalPeriodInSeconds>::Duration(Duration && Right) noexcept
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class LocalPeriodInSeconds>
	inline constexpr Duration<Representation, LocalPeriodInSeconds>::~Duration()
	{ }

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class LocalPeriodInSeconds>
	inline constexpr Duration<Representation, LocalPeriodInSeconds>& Duration<Representation, LocalPeriodInSeconds>::operator=(const Duration & Source)
	{
		if (this != &Source)
		{
			_Value = Source._Value;
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class LocalPeriodInSeconds>
	inline constexpr Duration<Representation, LocalPeriodInSeconds>& Duration<Representation, LocalPeriodInSeconds>::operator=(Duration&& Right) noexcept
	{
		if (this != &Right)
		{
			_Value = Elysium::Core::Template::Functional::Move(Right._Value);
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::Arithmetic Representation, class LocalPeriodInSeconds>
	inline constexpr const Representation Duration<Representation, LocalPeriodInSeconds>::GetCount() const
	{
		return _Value;
	}
}
#endif
