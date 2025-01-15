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

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORCALL
#include "../TypeTraits/HasOperatorCall.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCLASS
#include "../IsClass.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFUNCTION
#include "../IsFunction.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISLAMBDA
#include "../TypeTraits/IsLambda.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
    template <class T>
    concept Lambda = Elysium::Core::Template::TypeTraits::IsLambdaValue<T>;
    /*
    template <class T>
    concept Lambda = Elysium::Core::Template::TypeTraits::HasOperatorCallValue<T> &&
        !Elysium::Core::Template::TypeTraits::IsFunctionValue<T> && !Elysium::Core::Template::TypeTraits::IsFunctionValue<T>;
    */
}
#endif
