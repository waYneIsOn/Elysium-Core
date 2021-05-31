/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ISREFERENCE
#define ELYSIUM_CORE_TEMPLATE_ISREFERENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template
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
