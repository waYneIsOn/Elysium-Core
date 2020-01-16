/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_REFLECTION_FIELDATTRIBUTES
#define ELYSIUM_CORE_REFLECTION_FIELDATTRIBUTES

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Reflection
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class FieldAttributes : uint32_t
#elif defined(__ANDROID__)
	enum class FieldAttributes
#else
#error "undefined os"
#endif
	{
		//Assembly = 3,
		//FamANDAssem = 2,
		//Family = 4,
		//FamORAssem = 5,
		//FieldAccessMask = 7,
		HasDefault = 32768,
		//HasFieldMarshal = 4096,
		//HasFieldRVA = 256,
		InitOnly = 32,
		Literal = 64,
		//NotSerialized = 128,
		//PinvokeImpl = 8291,
		Private = 1,
		PrivateScope = 0,
		Public = 6,
		//ReservedMask = 38144,
		//RTSpecialName = 1024,
		//SpecialName = 512,
		Static = 16
	};

	inline FieldAttributes operator|(FieldAttributes lhs, FieldAttributes rhs)
	{
		return static_cast<FieldAttributes>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}
	inline FieldAttributes operator&(FieldAttributes lhs, FieldAttributes rhs)
	{
		return static_cast<FieldAttributes>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}
}
#endif
