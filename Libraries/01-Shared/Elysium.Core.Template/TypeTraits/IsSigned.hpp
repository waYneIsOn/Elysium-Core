/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNED
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLOATINGPOINT
#include "IsFloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGRAL
#include "IsIntegral.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T, bool = Elysium::Core::Template::TypeTraits::IsIntegralValue<T>>
	struct IsSignedHelper
	{
		using PlainT = Functional::RemoveConstVolatileType<T>;

		static constexpr bool Signed = static_cast<PlainT>(-1) < static_cast<PlainT>(0);
	};

	template <class T>
	struct IsSignedHelper<T, false>
	{
		static constexpr bool Signed = IsFloatingPointValue<T>;
	};

	template <class T>
	struct IsSigned : public IntegralConstant<bool, Elysium::Core::Template::TypeTraits::IsSignedHelper<T>::Signed>
	{ };
	
	template <class T>
	inline constexpr bool IsSignedValue = IsSigned<T>::Value;
}
#endif

