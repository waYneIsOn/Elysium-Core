/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_SIGNOF
#define ELYSIUM_CORE_TEMPLATE_MATH_SIGNOF

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLOATINGPOINT
#include "FloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER
#include "SignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "UnsignedInteger.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	template<Concepts::FloatingPoint FP>
	constexpr FP SignOf(const FP Value) noexcept
	{
		return Value < 0 ? -1 : 1;
	}

	template<Concepts::SignedInteger SI>
	constexpr SI SignOf(const SI Value) noexcept
	{
		return Value < 0 ? -1 : 1;
	}

	template<Concepts::UnsignedInteger UI>
	constexpr UI SignOf(const UI Value) noexcept
	{
		return 1;
	}
}
#endif
