/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISCONSTANT
#define ELYSIUM_CORE_TEMPLATE_ISCONSTANT

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template
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
