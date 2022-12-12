/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_BOOLEAN
#define ELYSIUM_CORE_BOOLEAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Boolean final
	{
	public:
		Boolean() = delete;

		Boolean(const Boolean& Right) = delete;

		Boolean(Boolean&& Right) noexcept = delete;

		~Boolean() = delete;
	public:
		Boolean& operator=(const Boolean& Source) = delete;

		Boolean& operator=(Boolean&& Right) noexcept = delete;
	public:
		static constexpr const char8_t* TrueString = u8"True";
		static constexpr const char8_t* FalseString = u8"False";
	};
}
#endif
