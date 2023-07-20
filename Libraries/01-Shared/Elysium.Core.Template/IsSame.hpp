/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class, class>
	inline constexpr bool IsSameValue = false;

	template <class T>
	inline constexpr bool IsSameValue<T, T> = true;
	
	template <class TFirst, class TSecond>
	struct IsSame : public IntegralConstant<bool, IsSameValue<TFirst, TSecond>>
	{ };
}
#endif

