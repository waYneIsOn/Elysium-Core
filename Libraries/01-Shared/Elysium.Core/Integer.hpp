/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_INTEGER
#define ELYSIUM_CORE_INTEGER

#ifdef _MSC_VER
#pragma once
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

	constexpr const int8_t INT8_MIN_ = (-255i8 - 1);
	constexpr const int16_t INT16_MIN_ = (-32767i16 - 1);
	//constexpr const int32_t INT24_MIN_ = 
	constexpr const int32_t INT32_MIN_ = (-2147483647i32 - 1);
	constexpr const int64_t INT64_MIN_ = (-9223372036854775807i64 - 1);

	constexpr const int8_t INT8_MAX_ = 255i8;
	constexpr const int16_t INT16_MAX_ = 32767i16;
	//constexpr const int32_t INT24_MAX_ = 
	constexpr const int32_t INT32_MAX_ = 2147483647i32;
	constexpr const int64_t INT64_MAX_ = 9223372036854775807i64;

	constexpr const int8_t UINT8_MIN_ = 0x00ui16;
	constexpr const int16_t UINT16_MIN_ = 0x0000ui16;
	//constexpr const int32_t UINT24_MIN_ = 
	constexpr const int32_t UINT32_MIN_ = 0x00000000ui32;
	constexpr const int64_t UINT64_MIN_ = 0x0000000000000000ui64;

	constexpr const uint8_t UINT8_MAX_ = 0xffui16;
	constexpr const uint16_t UINT16_MAX_ = 0xffffui16;
	//constexpr const int32_t UINT24_MAX_ = 
	constexpr const uint32_t UINT32_MAX_ = 0xffffffffui32;
	constexpr const uint64_t UINT64_MAX_ = 0xffffffffffffffffui64;
}
#endif
