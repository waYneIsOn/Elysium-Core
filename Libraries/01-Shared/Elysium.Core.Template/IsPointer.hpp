/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ISPOINTER
#define ELYSIUM_CORE_TEMPLATE_ISPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template
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
