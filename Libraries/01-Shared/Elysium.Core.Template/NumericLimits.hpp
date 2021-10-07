/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICLIMITS
#define ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICLIMITS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNED
#include "IsSigned.hpp"
#endif

namespace Elysium::Core::Template::Numeric
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	struct NumericLimits
	{
	public:
		using Value = T;
		using ConstValue = const T;
	public:
		/// <summary>
		/// Returns the number of bytes required to represent this integer-type.
		/// </summary>
		static constexpr const size_t ByteLength = sizeof(T);

		/// <summary>
		/// 
		/// </summary>
		static constexpr ConstValue Minimum = Elysium::Core::Template::TypeTraits::IsSignedValue<T> ? ((2 << (ByteLength * 7)) / 2) * -1 : 0;

		/// <summary>
		/// 
		/// </summary>
		static constexpr ConstValue Maximum = Elysium::Core::Template::TypeTraits::IsSignedValue<T> ? ((2 << (ByteLength * 7)) / 2) - 1 : -1;
	};
}
#endif
