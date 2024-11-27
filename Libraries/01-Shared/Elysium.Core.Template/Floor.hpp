/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_FLOOR
#define ELYSIUM_CORE_TEMPLATE_MATH_FLOOR

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
	constexpr double Floor(const SI Value) noexcept
	{
		return static_cast<double>(Value);
	}
	
	constexpr float Floor(const float Value) noexcept
	{
		if (Value < 0)	// obviously cannot be evaluated at compile-time using concepts
		{
			return static_cast<float>(static_cast<System::int32_t>(Value - 1));
		}
		else
		{
			return static_cast<float>(static_cast<System::int32_t>(Value));
		}
	}

	constexpr double Floor(const double Value) noexcept
	{
		if (Value < 0)	// obviously cannot be evaluated at compile-time using concepts
		{
			return static_cast<double>(static_cast<System::int64_t>(Value - 1));
		}
		else
		{
			return static_cast<double>(static_cast<System::int64_t>(Value));
		}
	}
}
#endif
