/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISVOLATILE
#define ELYSIUM_CORE_TEMPLATE_ISVOLATILE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template
{
	template <class>
	inline constexpr bool IsVolatileValue = false;

	template <class T>
	inline constexpr bool IsVolatileValue<volatile T> = true;

	template <class T>
	struct IsVolatile : public IntegralConstant<bool, IsVolatileValue<T>>
	{ };
}
#endif
