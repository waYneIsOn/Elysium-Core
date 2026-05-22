/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORGREATEROREQUAL
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORGREATEROREQUAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_DECLAREVALUE
#include "../Functional/DeclareValue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_VOIDTYPE
#include "../VoidType.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T, typename = void>
	struct HasOperatorGreaterOrEqual
		: public IntegralConstant<bool, false>
	{};

	template <class T>
	struct HasOperatorGreaterOrEqual<T, Elysium::Core::Template::TypeTraits::VoidType<decltype
	(
		Elysium::Core::Template::Functional::DeclareValue<T>() >= Elysium::Core::Template::Functional::DeclareValue<T>()
	)>>
		: public IntegralConstant<bool, true>
	{ };

	template <class T>
	inline constexpr bool HasOperatorGreaterOrEqualValue = HasOperatorGreaterOrEqual<T>::Value;
}
#endif
