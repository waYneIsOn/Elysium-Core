/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE
#define ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLOATINGPOINT
#include "FloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER
#include "SignedInteger.hpp"
#endif
/*
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "UnsignedInteger.hpp"
#endif
*/
namespace Elysium::Core::Template::Math
{
	template<Concepts::FloatingPoint FP>
	constexpr FP Absolute(const FP Value) noexcept
	{
		return Value < 0 ? Value * -1 : Value;
	}

	template<Concepts::SignedInteger SI>
	constexpr SI Absolute(const SI Value) noexcept
	{ 
		return Value < 0 ? Value * -1 : Value;
	}
	/*
	template<Concepts::UnsignedInteger UI>
	constexpr UI Absolute(const UI Value) noexcept
	{
		return Value;
	}
	*/
}
#endif
