/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOMPLETELYDEFINED
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOMPLETELYDEFINED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "../IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template<class T, Elysium::Core::Template::System::size = sizeof(T)>
    Elysium::Core::Template::TypeTraits::IntegralConstant<bool, true> IsCompletelyDefinedImplementation(int);

    template<class T>
    Elysium::Core::Template::TypeTraits::IntegralConstant<bool, false> IsCompletelyDefinedImplementation(...);

    template<class T>
    inline constexpr bool IsCompletelyDefinedValue = decltype(IsCompletelyDefinedImplementation<T>(0))::Value;
}
#endif
