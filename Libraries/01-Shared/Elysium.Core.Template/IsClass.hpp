/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCLASS
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCLASS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T>
	struct IsClass : IntegralConstant<bool, __is_class(T)>
	{ };

	template <class T>
	inline constexpr bool IsClassValue = IsClass<T>::Value;
}
#endif
