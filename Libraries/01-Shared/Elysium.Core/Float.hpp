/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_FLOAT
#define ELYSIUM_CORE_FLOAT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NUMERIC
#include "Numeric.hpp"
#endif

namespace Elysium::Core
{
	template<class T>
	class Numeric<T, std::enable_if<std::is_floating_point<T>::value, T>>
	{ };

	typedef Numeric<float> Single;
	typedef Numeric<double> Double;
	//typedef Numeric<Decimal> Decimal;
}
#endif
