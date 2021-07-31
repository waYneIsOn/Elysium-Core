/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISUNION
#define ELYSIUM_CORE_TEMPLATE_ISUNION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template
{
	template <class T>
	struct IsUnion : IntegralConstant<bool, __is_union(T)>
	{ };

	template <class T>
	inline constexpr bool IsUnionValue = IsUnion<T>::Value;
}
#endif
