/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_GREATESTCOMMONDIVISOR
#define ELYSIUM_CORE_TEMPLATE_MATH_GREATESTCOMMONDIVISOR

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

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ABSOLUTE
#include "../Absolute.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../Compiler.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	template<Concepts::FloatingPoint FP>
	constexpr FP GreatestCommonDivisor(FP A, FP B) noexcept
	{
		if (A == 0 && B == 0) ELYSIUM_CORE_PATH_UNLIKELY
		{	// prevent division by 0
			return 1;
		}

		A = Elysium::Core::Template::Math::Absolute(A);
		B = Elysium::Core::Template::Math::Absolute(B);

		while (B != 0)
		{
			const FP TemporaryA = A;
			A = B;
			B = TemporaryA % B;
		}

		return A;
	}

	template<Concepts::SignedInteger SI>
	constexpr SI GreatestCommonDivisor(SI A, SI B) noexcept
	{
		if (A == 0 && B == 0) ELYSIUM_CORE_PATH_UNLIKELY
		{	// prevent division by 0
			return 1;
		}

		A = Elysium::Core::Template::Math::Absolute(A);
		B = Elysium::Core::Template::Math::Absolute(B);

		while(B != 0)
		{
			const SI TemporaryA = A;
			A = B;
			B = TemporaryA % B;
		}

		return A;
	}

	template<Concepts::UnsignedInteger UI>
	constexpr UI GreatestCommonDivisor(UI A, UI B) noexcept
	{
		if (A == 0 && B == 0) ELYSIUM_CORE_PATH_UNLIKELY
		{	// prevent division by 0
			return 1;
		}

		while (B != 0)
		{
			const UI TemporaryA = A;
			A = B;
			B = TemporaryA % B;
		}

		return A;
	}
}
#endif
