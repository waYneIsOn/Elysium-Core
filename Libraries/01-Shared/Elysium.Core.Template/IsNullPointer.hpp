/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISNULLPOINTER
#define ELYSIUM_CORE_TEMPLATE_ISNULLPOINTER

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
	template <class T>
	inline constexpr bool IsNullPointerValue = IsSame<T, nullptr_t>::Value;

	template <class T>
	struct IsNullPointer : public IntegralConstant<bool, IsNullPointerValue<T>>
	{ };
}
#endif
