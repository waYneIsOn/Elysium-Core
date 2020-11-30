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

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Boolean final
	{
	public:
		Boolean() = delete;
		Boolean(const Boolean& Right) = delete;
		Boolean(Boolean&& Right) noexcept = delete;
		~Boolean() = delete;

		Boolean& operator=(const Boolean& Source) = delete;
		Boolean& operator=(Boolean&& Right) noexcept = delete;

		static constexpr const char8_t* TrueString = u8"True";
		static constexpr const char8_t* FalseString = u8"False";
	};
}
#endif
