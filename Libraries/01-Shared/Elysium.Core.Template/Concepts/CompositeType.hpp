/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_COMPOSITETYPE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_COMPOSITETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCLASS
#include "IsClass.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept CompositeType = TypeTraits::IsClassValue<T>;
}
#endif
