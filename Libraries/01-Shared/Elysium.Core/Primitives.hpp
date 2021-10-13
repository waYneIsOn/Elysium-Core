/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_PRIMITIVES
#define ELYSIUM_CORE_PRIMITIVES

#ifdef _MSC_VER
#pragma once
#endif

#include <cassert>

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

	constexpr Elysium::Core::int8_t operator "" _i8(const unsigned long long Value)
	{
		// ToDo: assert
		return static_cast<Elysium::Core::int8_t>(Value);
	}

	constexpr Elysium::Core::int16_t operator "" _i16(const unsigned long long Value)
	{
		// ToDo: assert
		return static_cast<Elysium::Core::int16_t>(Value);
	}

	constexpr Elysium::Core::int32_t operator "" _i32(const unsigned long long Value)
	{
		// ToDo: assert
		return static_cast<Elysium::Core::int32_t>(Value);
	}

	constexpr Elysium::Core::int64_t operator "" _i64(const unsigned long long Value)
	{
		// ToDo: assert
		return static_cast<Elysium::Core::int64_t>(Value);
	}

	constexpr Elysium::Core::uint8_t operator "" _ui8(const unsigned long long Value)
	{
		assert(Value >= 0u && Value <= 255u);
		return static_cast<Elysium::Core::uint8_t>(Value);
	}

	constexpr Elysium::Core::uint16_t operator "" _ui16(const unsigned long long Value)
	{
		assert(Value >= 0u && Value <= 65535u);
		return static_cast<Elysium::Core::uint16_t>(Value);
	}

	constexpr Elysium::Core::uint32_t operator "" _ui32(const unsigned long long Value)
	{
		assert(Value >= 0u && Value <= 4294967295u);
		return static_cast<Elysium::Core::uint32_t>(Value);
	}

	constexpr Elysium::Core::uint64_t operator "" _ui64(const unsigned long long Value)
	{
		assert(Value >= 0u && Value <= 18446744073709551615u);
		return static_cast<Elysium::Core::uint64_t>(Value);
	}
}
#endif
