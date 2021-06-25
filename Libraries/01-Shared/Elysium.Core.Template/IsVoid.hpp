/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ISVOID
#define ELYSIUM_CORE_TEMPLATE_ISVOID

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
	inline constexpr bool IsVoidValue = IsSame<T, void>::Value;

	template <class T>
	struct IsVoid : public IntegralConstant<bool, IsVoidValue<T>>
	{ };
}
#endif

