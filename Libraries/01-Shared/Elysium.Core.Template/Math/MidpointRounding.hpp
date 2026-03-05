/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIDPOINTROUNDING
#define ELYSIUM_CORE_TEMPLATE_MATH_MIDPOINTROUNDING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	/// <summary>
	/// Specifies the strategy that mathematical rounding methods should use to round a number.
	/// </summary>
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class MidpointRounding : System::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class MidpointRounding
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// The strategy of rounding to the nearest number, and when a number is halfway between two others, it's rounded toward the nearest even number.
		/// </summary>
		ToEven = 0,

		/// <summary>
		/// The strategy of rounding to the nearest number, and when a number is halfway between two others, 
		/// it's rounded toward the nearest number that's away from zero.
		/// </summary>
		AwayFromZero = 1,

		/// <summary>
		/// The strategy of directed rounding toward zero, with the result closest to and no greater in magnitude than the infinitely precise result.
		/// </summary>
		ToZero = 2,

		/// <summary>
		/// The strategy of downwards-directed rounding, with the result closest to and no greater than the infinitely precise result.
		/// </summary>
		ToNegativeInfinity = 3,

		/// <summary>
		/// The strategy of upwards-directed rounding, with the result closest to and no less than the infinitely precise result.
		/// </summary>
		ToPositiveInfinity = 4
	};
}
#endif
