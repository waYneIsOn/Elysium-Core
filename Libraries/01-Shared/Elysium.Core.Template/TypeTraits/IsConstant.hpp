/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONSTANT
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONSTANT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class>
	inline constexpr bool IsConstantValue = false;
	
	template <class T>
	inline constexpr bool IsConstantValue<const T> = true;
	
	template <class T>
	struct IsConstant : public IntegralConstant<bool, IsConstantValue<T>>
	{ };
}
#endif
