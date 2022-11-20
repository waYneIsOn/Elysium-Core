/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNEDINTEGER
#include "IsSignedInteger.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
	template<class T>
	concept SignedInteger = TypeTraits::IsSignedIntegerValue<T>;
}
#endif
