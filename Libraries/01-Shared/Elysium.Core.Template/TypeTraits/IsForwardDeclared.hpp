/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFORWARDDECLARED
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFORWARDDECLARED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template<class T, Elysium::Core::Template::System::size = sizeof(T)>
    Elysium::Core::Template::TypeTraits::IntegralConstant<bool, false> IsForwardDeclaredImplementation(int);

    template<class T>
    Elysium::Core::Template::TypeTraits::IntegralConstant<bool, true> IsForwardDeclaredImplementation(...);

    template<class T>
    inline constexpr bool IsForwardDeclaredValue = decltype(IsForwardDeclaredImplementation<T>(0))::Value;

    template <class T, class... Other>
    struct IsForwardDeclared
        : public IntegralConstant<bool, IsForwardDeclaredValue<T>>
    {};
}
#endif
#pragma once
