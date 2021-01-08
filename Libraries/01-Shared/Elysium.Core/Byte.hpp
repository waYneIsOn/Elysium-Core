/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_BYTE
#define ELYSIUM_CORE_BYTE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

namespace Elysium::Core
{
	/*
	enum class byte : unsigned char
	{};
	*/

	typedef uint8_t byte;

	typedef int8_t sbyte;
}
#endif
