/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISPOINTER
#include "IsPointer.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Pointer = TypeTraits::IsPointer<T>::Value;
}
#endif
