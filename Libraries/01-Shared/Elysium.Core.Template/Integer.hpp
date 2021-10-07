/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGER
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGER
#include "IsInteger.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Integer = TypeTraits::IsIntegerValue<T>;
}
#endif
