/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSCOPEDENUMERATION
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSCOPEDENUMERATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATION
#include "Concepts/Enumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONVERTIBLE
#include "IsConvertible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_UNDERLYINGTYPE
#include "UnderlyingType.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <Elysium::Core::Template::Concepts::Enumeration T>
	struct IsScopedEnumeration : public IntegralConstant<bool, !IsConvertible<T, UnderlyingTypeType<T>>::Value>
	{ };

    template <Elysium::Core::Template::Concepts::Enumeration T>
    inline constexpr bool IsScopedEnumerationValue = IsScopedEnumeration<T>::Value;
}
#endif
