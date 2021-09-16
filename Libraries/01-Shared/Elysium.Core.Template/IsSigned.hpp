/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ISSIGNED
#define ELYSIUM_CORE_TEMPLATE_ISSIGNED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISFLOATINGPOINT
#include "IsFloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISINTEGRAL
#include "IsIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

namespace Elysium::Core::Template
{
	template <class T, bool = IsIntegralValue<T>>
	struct IsSignedHelper
	{
		using PlainT = RemoveConstVolatileType<T>;

		static constexpr bool Signed = static_cast<PlainT>(-1) < static_cast<PlainT>(0);
	};

	template <class T>
	struct IsSignedHelper<T, false>
	{
		static constexpr bool Signed = IsFloatingPointValue<T>;
	};

	template <class T>
	struct IsSigned : public IntegralConstant<bool, IsSignedHelper<T>::Signed>
	{ };
	
	template <class T>
	inline constexpr bool IsSignedValue = IsSigned<T>::Value;
}
#endif

