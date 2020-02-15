/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_INTEGER
#define ELYSIUM_CORE_INTEGER

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
	/*
	//constexpr const int16_t INT16_MIN = (-32767i16 - 1);
	//constexpr const int32_t INT32_MIN = (-2147483647i32 - 1);
	//constexpr const int64_t INT64_MIN = (-9223372036854775807i64 - 1);

	constexpr const int16_t INT16_MAX = 32767i16;
	constexpr const int32_t INT32_MAX = 2147483647i32;
	constexpr const int64_t INT64_MAX = 9223372036854775807i64;

	constexpr const uint16_t UINT16_MAX = 0xffffui16;
	constexpr const uint32_t UINT32_MAX = 0xffffffffui32;
	constexpr const uint64_t UINT64_MAX = 0xffffffffffffffffui64;
	*/
}
#endif
