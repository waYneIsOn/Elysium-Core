/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLAGENUMERATION
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLAGENUMERATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLAGENUMERATION
#include "../TypeTraits/IsFlagEnumeration.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept FlagEnumeration = TypeTraits::IsFlagEnumerationValue<T>;
}
#endif
