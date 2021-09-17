/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CONSTANT
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_CONSTANT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONSTANT
#include "IsConstant.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Constant = TypeTraits::IsConstant<T>::Value;
}
#endif
