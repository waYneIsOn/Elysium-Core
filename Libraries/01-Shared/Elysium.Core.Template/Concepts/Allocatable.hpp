/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ALLOCATABLE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_ALLOCATABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONSTANT
#include "../TypeTraits/IsConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFUNCTION
#include "../TypeTraits/IsFunction.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISREFERENCE
#include "../TypeTraits/IsReference.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Allocatable = !TypeTraits::IsConstantValue<T> && !TypeTraits::IsFunctionValue<T> && !TypeTraits::IsReferenceValue<T>;
}
#endif
