/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#define ELYSIUM_CORE_TEMPLATE_MATH_MIN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASOPERATORGREATEROREQUAL
#include "../Concepts/HasOperatorGreaterOrEqual.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="Left"></param>
	/// <param name="Right"></param>
	/// <returns></returns>
	template<Elysium::Core::Template::Concepts::HasOperatorGreaterOrEqual T>
	inline constexpr T Min(const T Left, const T Right) noexcept(noexcept(Left <= Right))
	{
		if (Left <= Right)
		{
			return Left;
		}
		else
		{
			return Right;
		}
	}
}
#endif
