/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_VALUE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_VALUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVALUE
#include "IsValue.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Value = TypeTraits::IsValueValue<T>;
}
#endif
