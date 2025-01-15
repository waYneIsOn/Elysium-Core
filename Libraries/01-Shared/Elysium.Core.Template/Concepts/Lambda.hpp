/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_LAMBDA
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_LAMBDA

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISLAMBDA
#include "../TypeTraits/IsLambda.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
    template <class T>
    concept Lambda = Elysium::Core::Template::TypeTraits::IsLambdaValue<T>;
}
#endif
