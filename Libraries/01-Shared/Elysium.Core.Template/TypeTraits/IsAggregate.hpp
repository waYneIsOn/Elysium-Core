/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISAGGREGATE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISAGGREGATE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T>
	struct IsAggregate 
		: public IntegralConstant<bool, __is_aggregate(T)>
	{
	};

	template <class T>
	inline constexpr bool IsAggregateValue = IsAggregate<T>::Value;
}
#endif
