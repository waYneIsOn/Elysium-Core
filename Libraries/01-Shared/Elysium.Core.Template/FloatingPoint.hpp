/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLOATINGPOINT
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLOATINGPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLOATINGPOINT
#include "IsFloatingPoint.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept FloatingPoint = TypeTraits::IsFloatingPointValue<T>;
}
#endif
