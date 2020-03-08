/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_ENUM
#define ELYSIUM_CORE_ENUM

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Enum final
	{
	public:
		Enum() = delete;
		Enum(const Enum& Source) = delete;
		Enum(Enum&& Right) noexcept = delete;
		~Enum() = delete;

		Enum& operator=(const Enum& Source) = delete;
		Enum& operator=(Enum&& Right) noexcept = delete;

		//static String ToString();
	private:
	};
}
#endif
