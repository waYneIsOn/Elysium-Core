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

namespace Elysium::Core::Template::Numeric
{
	/// <summary>
	/// 
	/// </summary>
	template <long long T1, long long T2>
	struct Ratio
	{ };
	/*
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
	*/
}
#endif
