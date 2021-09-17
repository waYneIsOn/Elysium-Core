/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ADDRIGHTVALUEREFERENCE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ADDRIGHTVALUEREFERENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ADDREFERENCE
#include "AddReference.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    struct AddRightValueReference
    {
        using Type = typename AddReference<T>::RightValue;
    };

    template <class T>
    using AddRightValueReferenceType = typename AddReference<T>::RightValue;
}
#endif
