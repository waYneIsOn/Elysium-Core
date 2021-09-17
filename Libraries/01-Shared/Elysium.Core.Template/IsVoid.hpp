/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVOID
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVOID

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "IsSame.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T>
	inline constexpr bool IsVoidValue = IsSame<T, void>::Value;

	template <class T>
	struct IsVoid : public IntegralConstant<bool, IsVoidValue<T>>
	{ };
}
#endif

