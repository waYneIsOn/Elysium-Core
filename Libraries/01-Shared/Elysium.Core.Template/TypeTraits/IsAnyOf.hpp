/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_DISJUNCTION
#include "Disjunction.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "IsSame.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T, class... Other>
	inline constexpr bool IsAnyOfValue = DisjunctionValue<IsSame<T, Other>...>;
}
#endif
