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
		static constexpr const Elysium::Core::uint8_t ByteLength = sizeof(T);

		/// <summary>
		/// 
		/// </summary>
		static constexpr const bool IsSigned = Elysium::Core::Template::TypeTraits::IsSignedValue<T>;

		/// <summary>
		/// 
		/// </summary>
		static constexpr ConstValue Minimum = IsSigned ? static_cast<ConstValue>(1 << (ByteLength * 8 - 1)) : 0;

		/// <summary>
		/// 
		/// </summary>
		static constexpr ConstValue Maximum = IsSigned ? static_cast<ConstValue>(((1 << (ByteLength * 8 - 1)) + 1) * -1) : -1;
	};
}
#endif
