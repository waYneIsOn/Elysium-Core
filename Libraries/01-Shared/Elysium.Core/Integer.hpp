/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_INTEGER
#define ELYSIUM_CORE_INTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NUMERIC
#include "Numeric.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COMMON_ENABLEIF
#include "../Elysium.Core.Template/Common/EnableIf.hpp"
#endif

namespace Elysium::Core
{
	using Int8 = Numeric<Elysium::Core::int8_t>;
	using UInt8 = Numeric<Elysium::Core::uint8_t>;
	using Int16 = Numeric<Elysium::Core::int16_t>;
	using UInt16 = Numeric<Elysium::Core::uint16_t>;
	using Int32 = Numeric<Elysium::Core::int32_t>;
	using UInt32 = Numeric<Elysium::Core::uint32_t>;
	using Int64 = Numeric<Elysium::Core::int64_t>;
	using UInt64 = Numeric<Elysium::Core::uint64_t>;
}
#endif
