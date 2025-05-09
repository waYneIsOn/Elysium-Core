/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLAGENUMERATION
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLAGENUMERATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COMMON_ENABLEIF
#include "../EnableIf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_DECLAREVALUE
#include "../Functional/DeclareValue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "../IsSame.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
	template <class T, class = void>
	struct IsFlagEnumeration
		: IntegralConstant<bool, false>
	{ };

	template <class T>
	struct IsFlagEnumeration<T, 
		Common::EnableIfType<
			__is_enum(T) &&
			TypeTraits::IsSameValue<decltype(Functional::DeclareValue<T>() & Functional::DeclareValue<T>()), T> &&
			TypeTraits::IsSameValue<decltype(Functional::DeclareValue<T>() | Functional::DeclareValue<T>()), T>
		>
	>
		: IntegralConstant<bool, true>
	{ };

	template <class T>
	inline constexpr bool IsFlagEnumerationValue = IsFlagEnumeration<T>::Value;
}
#endif
