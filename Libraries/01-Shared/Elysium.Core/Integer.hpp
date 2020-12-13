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

namespace Elysium::Core
{
	template<class T>
	class Numeric<T, std::enable_if<std::is_integral<T>::value, T>>
	{ };

	typedef Numeric<int16_t> Int16;
	typedef Numeric<uint16_t> UInt16;
	typedef Numeric<int32_t> Int32;
	typedef Numeric<uint32_t> UInt32;
	typedef Numeric<int64_t> Int64;
	typedef Numeric<uint64_t> UInt64;
}
#endif
