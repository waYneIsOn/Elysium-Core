/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ARITHMETIC
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_ARITHMETIC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISARITHMETIC
#include "IsArithemtic.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept Arithmetic = TypeTraits::IsArithmeticValue<T>;
}
#endif
