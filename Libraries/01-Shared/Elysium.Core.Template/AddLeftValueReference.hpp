/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ADDLEFTVALUEREFERENCE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ADDLEFTVALUEREFERENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ADDREFERENCE
#include "AddReference.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    struct AddLeftValueReference
    {
        using Type = typename AddReference<T>::LeftValue;
    };

    template <class T>
    using AddLeftValueReferenceType = typename AddReference<T>::LeftValue;
}
#endif
