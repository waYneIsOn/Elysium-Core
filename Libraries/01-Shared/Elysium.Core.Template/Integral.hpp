/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGRAL
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGRAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGRAL
#include "IsIntegral.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Integral = TypeTraits::IsIntegralValue<T>;
}
#endif
