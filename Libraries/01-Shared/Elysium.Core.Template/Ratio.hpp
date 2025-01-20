/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_RATIO
#define ELYSIUM_CORE_TEMPLATE_NUMERIC_RATIO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE
#include "Absolute.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_GREATESTCOMMONDIVISOR
#include "Math/GreatestCommonDivisor.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_SIGNOF
#include "Math/SignOf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Numeric
{
	/// <summary>
	/// Provides compile-time rational arithemtics support.
	/// </summary>
	template <Elysium::Core::Template::System::intMax_t Num, Elysium::Core::Template::System::intMax_t Denom = 1>
	struct Ratio
	{
		static_assert(Denom != 0, "Elysium::Core::Template::Numeric::Ratio<N, D>: Denominator musn't be 0!");
		static_assert(NumericTraits<System::intMax_t>::Maximum * -1 <= Num, "Elysium::Core::Template::Numeric::Ratio<N, D>: Numerator overflow!");
		static_assert(NumericTraits<System::intMax_t>::Maximum * -1 <= Denom, "Elysium::Core::Template::Numeric::Ratio<N, D>: Denominator overflow!");
	public:
		inline static constexpr const Elysium::Core::Template::System::intMax_t Numerator = 
			Elysium::Core::Template::Math::SignOf(Num) * Elysium::Core::Template::Math::SignOf(Denom) *
			Elysium::Core::Template::Math::Absolute(Num) / Elysium::Core::Template::Math::GreatestCommonDivisor(Num, Denom);
		inline static constexpr const Elysium::Core::Template::System::intMax_t Denominator =
			Elysium::Core::Template::Math::Absolute(Denom) / Elysium::Core::Template::Math::GreatestCommonDivisor(Num, Denom);
	public:
		using Type = Ratio<Numerator, Denominator>;
	};

	/*
	using Quecto = Ratio<1, 1'000'000'000'000'000'000'000'000'000'000>;
	using Ronto = Ratio<1, 1'000'000'000'000'000'000'000'000'000>;
	using Yocto = Ratio<1, 1'000'000'000'000'000'000'000'000>;
	using Zepto = Ratio<1, 1'000'000'000'000'000'000'000>;
	*/
	using Atto = Ratio<1, 1'000'000'000'000'000'000>;
	using Femto = Ratio<1, 1'000'000'000'000'000>;
	using Pico = Ratio<1, 1'000'000'000'000>;
	using Nano = Ratio<1, 1'000'000'000>;
	using Micro = Ratio<1, 1'000'000>;
	using Milli = Ratio<1, 1'000>;
	using Centi = Ratio<1, 100>;
	using Deci = Ratio<1, 10>;
	
	using Deca = Ratio<10, 1>;
	using Hecto = Ratio<100, 1>;
	using Kilo = Ratio<1'000, 1>;
	using Mega = Ratio<1'000'000, 1>;
	using Giga = Ratio<1'000'000'000, 1>;
	using Tera = Ratio<1'000'000'000'000, 1>;
	using Peta = Ratio<1'000'000'000'000'000, 1>;
	using Exa = Ratio<1'000'000'000'000'000'000, 1>;
	/*
	using Zetta = Ratio<1'000'000'000'000'000'000'000, 1>;
	using Yotta = Ratio<1'000'000'000'000'000'000'000'000, 1>;
	using Ronna = Ratio<1'000'000'000'000'000'000'000'000'000, 1>;
	using Quetta = Ratio<1'000'000'000'000'000'000'000'000'000'000, 1>;
	*/
}
#endif
