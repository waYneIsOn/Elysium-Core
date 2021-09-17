/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISCONSTANT
#include "IsConstant.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept NonConstant = !TypeTraits::IsConstant<T>::Value;
}
#endif
