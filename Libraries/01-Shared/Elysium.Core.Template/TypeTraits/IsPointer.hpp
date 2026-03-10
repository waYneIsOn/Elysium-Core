/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISPOINTER
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class>
	inline constexpr bool IsPointerValue = false;

	template <class T>
	inline constexpr bool IsPointerValue<T*> = true;

	template <class T>
	struct IsPointer : public IntegralConstant<bool, IsPointerValue<T>>
	{ };
}
#endif

