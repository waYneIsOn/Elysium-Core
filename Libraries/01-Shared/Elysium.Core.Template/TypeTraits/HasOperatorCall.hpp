/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORCALL
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORCALL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_DECLAREVALUE
#include "../Functional/DeclareValue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "../IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_VOIDTYPE
#include "../VoidType.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T, typename = void>
	struct HasOperatorCall
		: public IntegralConstant<bool, false>
	{
	};

	template <class T>
	struct HasOperatorCall<T, Elysium::Core::Template::TypeTraits::VoidType<decltype
	(
		&T::operator()
	)>>
		: public IntegralConstant<bool, true>
	{ };

	template <class T>
	inline constexpr bool HasOperatorCallValue = HasOperatorCall<T>::Value;
}
#endif
