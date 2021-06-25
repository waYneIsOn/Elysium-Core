/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISANYOF
#define ELYSIUM_CORE_TEMPLATE_ISANYOF

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISSAME
#include "IsSame.hpp"
#endif

namespace Elysium::Core::Template
{
	template <class, class...>
	inline constexpr bool IsAnyOfValue = false;

	template <class T, class... TFurther>
	struct IsAnyOf : public IntegralConstant<bool, IsAnyOfValue<T, TFurther>>
	{ };
	/*
	template <class T, class... TFurther>
	struct IsAnyOf : public IntegralConstant<bool, IsAnyOfValue<T, bool, char, char8_t, char16_t, char32_t, int, long, long long, short, signed char,
		unsigned char, unsigned int, unsigned long, unsigned long long, unsigned short, wchar_t>>
	{ };
	*/
}
#endif
