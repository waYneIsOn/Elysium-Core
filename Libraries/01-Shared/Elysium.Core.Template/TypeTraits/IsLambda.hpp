/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISLAMBDA
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISLAMBDA

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORCALL
#include "HasOperatorCall.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "../IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISAGGREGATE
#include "IsAggregate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCLASS
#include "../IsClass.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFUNCTION
#include "../IsFunction.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "../IsSame.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T>
	struct IsLambda
		: public Elysium::Core::Template::TypeTraits::IntegralConstant<bool, 
			Elysium::Core::Template::TypeTraits::IsClassValue<T> &&
			Elysium::Core::Template::TypeTraits::HasOperatorCallValue<T> &&
			!Elysium::Core::Template::TypeTraits::IsFunctionValue<T> &&
			!Elysium::Core::Template::TypeTraits::IsSameValue<T, decltype([](){})> &&
			!Elysium::Core::Template::TypeTraits::IsAggregateValue<T>
		>
	{
	};

	template <typename T>
	constexpr bool IsLambdaValue = IsLambda<T>::Value;
}
#endif
