/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISCLASS
#define ELYSIUM_CORE_TEMPLATE_ISCLASS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template
{
	template <class T>
	struct IsClass : IntegralConstant<bool, __is_class(T)>
	{ };

	template <class T>
	inline constexpr bool IsClassValue = IsClass<T>::Value;
}
#endif
