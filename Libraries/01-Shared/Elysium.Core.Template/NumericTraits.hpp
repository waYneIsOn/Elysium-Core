/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#define ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS

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
	struct NumericTraits
	{
	public:
		using Value = T;
		using ConstValue = const T;
	public:
		static constexpr const bool IsPositive(ConstValue Value);

		static constexpr const bool IsPrimeNumber(ConstValue Value);
	};

	template<class T>
	inline constexpr const bool NumericTraits<T>::IsPositive(ConstValue Value)
	{
		return Value > 0;
	}

	template<class T>
	inline constexpr const bool NumericTraits<T>::IsPrimeNumber(ConstValue Input)
	{	
		if (Input < 0x02)
		{
			return false;
		}
		
		for (Value i = 2; i <= Input / 2; i++)
		{
			if (Input % i == 0)
			{
				return false;
			}
		}

		return true;
	}
}
#endif
