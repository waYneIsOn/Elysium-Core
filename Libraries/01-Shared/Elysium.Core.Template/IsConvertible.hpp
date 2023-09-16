/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONVERTIBLE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONVERTIBLE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class From, class To>
	struct IsConvertible : IntegralConstant<bool, __is_convertible_to(From, To)>
	{ };

	template <class From, class To>
	inline constexpr bool IsConvertibleValue = IsConvertible<From, To>::Value;
}
#endif
