/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_LESSOREQUAL
#define ELYSIUM_CORE_TEMPLATE_OPERATORS_LESSOREQUAL

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Operators
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T = void>
	struct LessOrEqual
	{
		constexpr bool operator()(const T& Left, const T& Right) const
		{
			return Left <= Right;
		}
	};
}
#endif
