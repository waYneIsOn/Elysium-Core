/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVALUE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVALUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class>
	inline constexpr bool IsValueValue = true;
	
	template <class T>
	inline constexpr bool IsValueValue<T&> = false;

	template <class T>
	inline constexpr bool IsValueValue<T&&> = false;
	
	template <class T>
	inline constexpr bool IsValueValue<T*> = false;

	template <class T>
	struct IsValue : public IntegralConstant<bool, IsValueValue<T>>
	{ };
}
#endif

