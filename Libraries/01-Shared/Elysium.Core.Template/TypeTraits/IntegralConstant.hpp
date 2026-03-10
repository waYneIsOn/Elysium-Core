/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T, T _Value>
	struct IntegralConstant
	{
		typedef T ValueType;
		typedef IntegralConstant Type;

		static constexpr const T Value = _Value;

		constexpr operator const ValueType() const noexcept
		{
			return Value;
		}

		constexpr const ValueType operator()() const noexcept
		{
			return Value;
		}
	};
}
#endif
