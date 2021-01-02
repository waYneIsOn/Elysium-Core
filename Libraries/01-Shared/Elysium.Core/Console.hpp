/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CONSOLE
#define ELYSIUM_CORE_CONSOLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Console
	{
	public:
		Console() = delete;
		Console(const Console& Source) = delete;
		Console(Console&& Right) noexcept = delete;
		~Console() = delete;

		Console& operator=(const Console& Source) = delete;
		Console& operator=(Console&& Right) noexcept = delete;

		static const String ReadLine();

		static void WriteLine(const String& Value);
	};
}
#endif
