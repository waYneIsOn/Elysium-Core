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

#ifndef ELYSIUM_CORE_TEMPLATE_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

#ifndef _INC_STDDEF
#define __cplusplus
#include <stddef.h>
#endif

namespace Elysium::Core::Template
{
	template <class T>
	inline constexpr bool IsNullPointerValue = IsSameValue<RemoveConstVolatileType<T>, std::nullptr_t>;

	template <class T>
	struct IsNullPointer : public IntegralConstant<bool, IsNullPointerValue<T>>
	{ };
}
#endif
