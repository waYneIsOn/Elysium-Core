/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_LEMPELZIV_LZ77TOKEN
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_LEMPELZIV_LZ77TOKEN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::LempelZiv
{
    template <class T>
    struct LZ77Token
    {
        Elysium::Core::Template::System::uint16_t _Length = 0;
        Elysium::Core::Template::System::uint16_t _Distance = 0;
        T _Literal = {};
    };
}
#endif
