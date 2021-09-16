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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_NUMERIC
#include "Numeric.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COMMON
#include "../Elysium.Core.Template/Common.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS
#include "../Elysium.Core.Template/TypeTraits.hpp"
#endif

namespace Elysium::Core
{
	template<class T>
	class Numeric<T, Elysium::Core::Template::EnableIf<Elysium::Core::Template::IsIntegralValue<T>, T>>
	{ };

	typedef Numeric<Elysium::Core::int8_t> Int8;
	typedef Numeric<Elysium::Core::uint8_t> UInt8;
	typedef Numeric<Elysium::Core::int16_t> Int16;
	typedef Numeric<Elysium::Core::uint16_t> UInt16;
	typedef Numeric<Elysium::Core::int32_t> Int32;
	typedef Numeric<Elysium::Core::uint32_t> UInt32;
	typedef Numeric<Elysium::Core::int64_t> Int64;
	typedef Numeric<Elysium::Core::uint64_t> UInt64;
}
#endif
