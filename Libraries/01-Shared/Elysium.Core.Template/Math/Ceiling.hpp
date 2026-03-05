/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_CEILING
#define ELYSIUM_CORE_TEMPLATE_MATH_CEILING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER
#include "SignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	template<Concepts::SignedInteger SI>
	constexpr double Ceiling(const SI Value) noexcept
	{
		return static_cast<double>(Value);
	}
	
	constexpr float Ceiling(const float Value) noexcept
	{
		if (Value >= Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Maximum ||
			Value <= Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int32_t>::Minimum ||
			Elysium::Core::Template::Numeric::NumericTraits<float>::IsNaN(Value))
		{	// too large, infinite or NaN
			return Value;
		}
		
		if (Value < 0)	// obviously cannot be evaluated at compile-time using concepts
		{
			return static_cast<float>(static_cast<System::int32_t>(Value));
		}
		else
		{
			return static_cast<float>(static_cast<System::int32_t>(Value + 1));
		}
	}

	constexpr double Ceiling(const double Value) noexcept
	{
		if (Value >= Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int64_t>::Maximum ||
			Value <= Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::int64_t>::Minimum ||
			Elysium::Core::Template::Numeric::NumericTraits<double>::IsNaN(Value))
		{	// too large, infinite or NaN
			return Value;
		}
		
		if (Value < 0)	// obviously cannot be evaluated at compile-time using concepts
		{
			return static_cast<double>(static_cast<System::int64_t>(Value));
		}
		else
		{
			return static_cast<double>(static_cast<System::int64_t>(Value + 1));
		}
	}
}
#endif
