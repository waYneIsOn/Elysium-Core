/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLAGENUMERATION
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLAGENUMERATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISENUMERATION
#include "../IsEnumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORBITWISEAND
#include "../TypeTraits/HasOperatorBitwiseAnd.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORBITWISEOR
#include "../TypeTraits/HasOperatorBitwiseOr.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	// @ToDo: think about whether I need to check for all defined values being power of two
	template<class T>
	concept FlagEnumeration = TypeTraits::IsEnumerationValue<T> && TypeTraits::HasOperatorBitwiseAndValue<T> &&
		TypeTraits::HasOperatorBitwiseOrValue<T>;
}
#endif
