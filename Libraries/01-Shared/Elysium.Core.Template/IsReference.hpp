/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISREFERENCE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISREFERENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class>
	inline constexpr bool IsReferenceValue = false;

	template <class T>
	inline constexpr bool IsReferenceValue<T&> = true;

	template <class T>
	inline constexpr bool IsReferenceValue<T&&> = true;

	template <class T>
	struct IsReference : public IntegralConstant<bool, IsReferenceValue<T>>
	{ };
}
#endif
