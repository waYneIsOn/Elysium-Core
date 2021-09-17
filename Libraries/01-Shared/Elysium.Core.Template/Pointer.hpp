/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_POINTER
#define ELYSIUM_CORE_TEMPLATE_POINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISPOINTER
#include "IsPointer.hpp"
#endif

namespace Elysium::Core::Template
{
	template<class T>
	concept Pointer = IsPointer<T>::Value;
}
#endif
