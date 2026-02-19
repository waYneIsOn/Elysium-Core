/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNOTHROWINVOCABLE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNOTHROWINVOCABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_COMPOSITETYPE
#include "../Concepts/CompositeType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "../IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    /// <summary>
    /// As a default nothing is no throw invocable.
    /// </summary>
    template <class>
    inline constexpr bool IsNoThrowInvocableValue = false;

    /// <summary>
    /// Specialization for free-function/static method pointer via "decltype(&Function)".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    template <class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(*)(Args...) noexcept> = true;
    
    /// <summary>
    /// Specialization for free-function/static method raw type via "decltype(Function)". 
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    template <class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Args...) noexcept> = true;
    
    /// <summary>
    /// Specialization for member-function with qualifier "noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) noexcept> = true;
    
    /// <summary>
    /// Specialization for member-function with qualifiers "& noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) & noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "&& noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) && noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "const noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) const noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "const & noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) const & noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "const && noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) const && noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "volatile noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) volatile noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "volatile & noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) volatile & noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "volatile && noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) volatile && noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "const volatile noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) const volatile noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "const volatile & noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) const volatile & noexcept> = true;

    /// <summary>
    /// Specialization for member-function with qualifiers "const volatile && noexcept".
    /// </summary>
    /// <typeparam name="ReturnType"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <typeparam name="Type"></typeparam>
    template <Elysium::Core::Template::Concepts::CompositeType Type, class ReturnType, class ...Args>
    inline constexpr bool IsNoThrowInvocableValue<ReturnType(Type::*)(Args...) const volatile && noexcept> = true;
    /*
    template <class ReturnType, class ...Args>
    struct IsNoThrowInvocable : IntegralConstant<bool, IsNoThrowInvocableValue<ReturnType, Args...>>
    { };
    */
}
#endif
