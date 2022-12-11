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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER
#include "SignedInteger.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	template<Concepts::SignedInteger SI>
	constexpr SI Ceiling(const SI Value) noexcept
	{
		if (Value < 0)	// obviously cannot be evaluated at compile-time using concepts
		{
			return Value;
		}
		else
		{
			return Value + 1;
		}
	}
	
	constexpr float Ceiling(const float Value) noexcept
	{
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
