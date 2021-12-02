/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMEMBERFUNCTIONPOINTER
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMEMBERFUNCTIONPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    /*
    template <class T>
    inline constexpr bool IsMemberFunctionPointerValue = false;
    */
    /*
    template <class T, class ReturnType, ReturnType(T::*ActualMethod)()>
    inline constexpr bool IsMemberFunctionPointerValue = true;

    template <class T, class ReturnType, ReturnType(T::* ActualMethod)()>
    struct IsMemberFunctionPointer : IntegralConstant<bool, IsMemberFunctionPointerValue<T, ReturnType, ReturnType(T::*ActualMethod)()>>
    { };
    */
    template <class T>
    inline constexpr bool IsMemberFunctionPointerValue = false;

    template <class T, class U>
    inline constexpr bool IsMemberFunctionPointerValue<T U::*> = true;

    template <class T>
    struct IsMemberFunctionPointer : IntegralConstant<bool, IsMemberFunctionPointerValue<T>>
    { };
}
#endif
