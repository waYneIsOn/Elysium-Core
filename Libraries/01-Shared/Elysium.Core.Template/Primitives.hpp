/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#define ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::System
{
	typedef char int8_t;
	typedef short int16_t;
	typedef int int32_t;
	typedef long long int64_t;

	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned int uint32_t;
	typedef unsigned long long uint64_t;

#if ELYSIUM_CORE_BITNESS == 32
	typedef uint32_t size;
#elif ELYSIUM_CORE_BITNESS == 64
	typedef uint64_t size;
	//typedef unsigned __int64 size;
#else
#error "unsupported os"
#endif

	/*
	enum class byte : unsigned char
	{};
	*/
	typedef uint8_t byte;
	typedef int8_t sbyte;
}
#endif
