/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ATOMICUSABLE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_ATOMICUSABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGRAL
#include "IsIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISPOINTER
#include "IsPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_SELECT
#include "Select.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	// @ToDo: use concepts for trivially copyable, copy constructible, move constructible, copy assignable and move assignable

	template<class T>
	concept AtomicUsable = TypeTraits::IsPointerValue<T> || TypeTraits::IsIntegralValue<T>;
}
#endif
