/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ADDLEFTVALUEREFERENCE
#define ELYSIUM_CORE_TEMPLATE_ADDLEFTVALUEREFERENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ADDREFERENCE
#include "AddReference.hpp"
#endif

namespace Elysium::Core::Template
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
