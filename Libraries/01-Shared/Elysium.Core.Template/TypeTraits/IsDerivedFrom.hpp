/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISDERIVEDFROM
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISDERIVEDFROM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class Base, class PotentiallyDerived>
	struct IsDerivedFrom 
		: IntegralConstant<bool, __is_base_of(Base, PotentiallyDerived)>
	{
	};

	template <class Base, class PotentiallyDerived>
	inline constexpr bool IsDerivedFromValue = IsDerivedFrom<Base, PotentiallyDerived>::Value;
}
#endif
