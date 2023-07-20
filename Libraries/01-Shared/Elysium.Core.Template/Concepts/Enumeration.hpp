/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATION
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISENUMERATION
#include "IsEnumeration.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Enumeration = TypeTraits::IsEnumerationValue<T>;
}
#endif
