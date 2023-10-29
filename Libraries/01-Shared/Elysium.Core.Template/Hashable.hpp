/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASHABLE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASHABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGER
#include "IsInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMEMBERFUNCTIONPOINTER
#include "IsMemberFunctionPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	/*
	template<class T>
	concept Hashable = TypeTraits::IsIntegerValue<T> || TypeTraits::HasMethod<...>;
	*/

	// @ToDo: for now everything's hashable
	template<class T>
	concept Hashable = Elysium::Core::Template::TypeTraits::IntegralConstant<bool, true>::Value;
}
#endif
