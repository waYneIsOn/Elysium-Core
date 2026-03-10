/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISENUMERATION
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISENUMERATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T>
	struct IsEnumeration : IntegralConstant<bool, __is_enum(T)>
	{ };

	template <class T>
	inline constexpr bool IsEnumerationValue = IsEnumeration<T>::Value;
}
#endif
