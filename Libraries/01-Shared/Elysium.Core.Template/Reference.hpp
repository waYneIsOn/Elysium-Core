/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_REFERENCE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_REFERENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISREFERENCE
#include "IsReference.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Reference = TypeTraits::IsReferenceValue<T>;
}
#endif
