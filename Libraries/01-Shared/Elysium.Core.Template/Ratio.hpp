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
	template <Elysium::Core::Template::System::intMax_t N, Elysium::Core::Template::System::intMax_t D = 1>
	struct Ratio
	{
		static_assert(D != 0, "Elysium::Core::Template::Numeric::Ratio<N, D>: Denominator musn't be 0!");
		static_assert(NumericTraits<System::intMax_t>::Maximum * -1 <= N, "Elysium::Core::Template::Numeric::Ratio<N, D>: Numerator overflow!");
		static_assert(NumericTraits<System::intMax_t>::Maximum * -1 <= D, "Elysium::Core::Template::Numeric::Ratio<N, D>: Denominator overflow!");
	/*
	public:
		inline static constexpr const Elysium::Core::Template::System::intMax_t Numerator = 0;
		inline static constexpr const Elysium::Core::Template::System::intMax_t Denominator = 0;
	public:
		using Type = Ratio<Numerator, Denominator>;
	*/
	};
	/*
	Ratio<1, 1'000'000'000'000'000'000'000'000'000'000> Quecto;
	Ratio<1, 1'000'000'000'000'000'000'000'000'000> Ronto;
	Ratio<1, 1'000'000'000'000'000'000'000'000> Yocto;
	Ratio<1, 1'000'000'000'000'000'000'000> Zepto;
	Ratio<1, 1'000'000'000'000'000'000> Atto;
	Ratio<1, 1'000'000'000'000'000> Femto;
	Ratio<1, 1'000'000'000'000> Pico;
	Ratio<1, 1'000'000'000> Nano;
	Ratio<1, 1'000'000> Micro;
	Ratio<1, 1'000> Milli;
	Ratio<1, 100> Centi;
	Ratio<1, 10> Deci;
	
	Ratio<10, 1> Deca;
	Ratio<100, 1> Hecto;
	Ratio<1'000, 1> Kilo;
	Ratio<1'000'000, 1> Mega;
	Ratio<1'000'000'000, 1> Giga;
	Ratio<1'000'000'000'000, 1> Tera;
	Ratio<1'000'000'000'000'000, 1> Peta;
	Ratio<1'000'000'000'000'000'000, 1> Exa;
	Ratio<1'000'000'000'000'000'000'000, 1> Zetta;
	Ratio<1'000'000'000'000'000'000'000'000, 1> Yotta;
	Ratio<1'000'000'000'000'000'000'000'000'000, 1> Ronna;
	Ratio<1'000'000'000'000'000'000'000'000'000'000, 1> Quetta;
	*/
}
#endif
