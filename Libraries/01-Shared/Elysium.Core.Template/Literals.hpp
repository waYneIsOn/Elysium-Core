/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#define ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

constexpr Elysium::Core::Template::System::int8_t operator "" _i8(const unsigned long long Value)
{
	// ToDo: assert
	return static_cast<Elysium::Core::Template::System::int8_t>(Value);
}

constexpr Elysium::Core::Template::System::int16_t operator "" _i16(const unsigned long long Value)
{
	// ToDo: assert
	return static_cast<Elysium::Core::Template::System::int16_t>(Value);
}

constexpr Elysium::Core::Template::System::int32_t operator "" _i32(const unsigned long long Value)
{
	// ToDo: assert
	return static_cast<Elysium::Core::Template::System::int32_t>(Value);
}

constexpr Elysium::Core::Template::System::int64_t operator "" _i64(const unsigned long long Value)
{
	// ToDo: assert
	return static_cast<Elysium::Core::Template::System::int64_t>(Value);
}

constexpr Elysium::Core::Template::System::uint8_t operator "" _ui8(const unsigned long long Value)
{
	//assert(Value >= 0u && Value <= 255u);
	return static_cast<Elysium::Core::Template::System::uint8_t>(Value);
}

constexpr Elysium::Core::Template::System::uint16_t operator "" _ui16(const unsigned long long Value)
{
	//assert(Value >= 0u && Value <= 65535u);
	return static_cast<Elysium::Core::Template::System::uint16_t>(Value);
}

constexpr Elysium::Core::Template::System::uint32_t operator "" _ui32(const unsigned long long Value)
{
	//assert(Value >= 0u && Value <= 4294967295u);
	return static_cast<Elysium::Core::Template::System::uint32_t>(Value);
}

constexpr Elysium::Core::Template::System::uint64_t operator "" _ui64(const unsigned long long Value)
{
	//assert(Value >= 0u && Value <= 18446744073709551615u);
	return static_cast<Elysium::Core::Template::System::uint64_t>(Value);
}

constexpr const unsigned char operator "" _uc(const char Value)
{
	// ToDo: assert
	return static_cast<const unsigned char>(Value);
}

constexpr const unsigned char* operator "" _uc(const char* Value, Elysium::Core::Template::System::size Length)
{
	// ToDo: assert
	return static_cast<const unsigned char*>(static_cast<const void*>(Value));


	//return (const unsigned char*)Value;
}

constexpr const signed char operator "" _sc(const char Value)
{
	// ToDo: assert
	return static_cast<const signed char>(Value);
}

constexpr const signed char* operator "" _sc(const char* Value, Elysium::Core::Template::System::size Length)
{
	// ToDo: assert
	return static_cast<const signed char*>(static_cast<const void*>(Value));
	//return (const signed char*)Value;
}
#endif
