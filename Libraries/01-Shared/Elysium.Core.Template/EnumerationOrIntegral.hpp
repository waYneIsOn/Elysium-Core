/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATIONORINTEGRAL
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATIONORINTEGRAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISENUMERATION
#include "IsEnumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGRAL
#include "IsIntegral.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept EnumerationOrIntegral = TypeTraits::IsEnumerationValue<T> || TypeTraits::IsIntegralValue<T>;
}
#endif
