/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_NONCONSTANT
#define ELYSIUM_CORE_TEMPLATE_NONCONSTANT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISCONSTANT
#include "IsConstant.hpp"
#endif

namespace Elysium::Core::Template
{
	template<class T>
	concept NonConstant = !IsConstant<T>::Value;
}
#endif
