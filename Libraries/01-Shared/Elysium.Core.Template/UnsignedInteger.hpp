/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISUNSIGNEDINTEGER
#include "IsUnsignedInteger.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept UnsignedInteger = TypeTraits::IsUnsignedIntegerValue<T>;
}
#endif
