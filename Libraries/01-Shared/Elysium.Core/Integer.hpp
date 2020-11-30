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

namespace Elysium::Core
{
	typedef char int8_t;
	typedef short int16_t;
	typedef int int32_t;
	typedef long long int64_t;

	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned int uint32_t;
	typedef unsigned long long uint64_t;

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
