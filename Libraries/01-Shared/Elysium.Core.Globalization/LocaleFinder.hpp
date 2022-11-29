/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_INTERNAL_LOCALEFINDER
#define ELYSIUM_CORE_GLOBALIZATION_INTERNAL_LOCALEFINDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFINTEGER
#include "../Elysium.Core/VectorOfInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTURETYPES
#include "../Elysium.Core.Template/CultureTypes.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _WINNLS_
#include <WinNls.h>
#endif
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else
#error "undefined os"
#endif

namespace Elysium::Core::Globalization::Internal
{
	class LocaleFinder final
	{
	public:
		LocaleFinder() = delete;
		LocaleFinder(const LocaleFinder& Source) = delete;
		LocaleFinder(LocaleFinder&& Right) noexcept = delete;
		~LocaleFinder() = delete;

		LocaleFinder& operator=(const LocaleFinder& Source) = delete;
		LocaleFinder& operator=(LocaleFinder&& Right) noexcept = delete;

		static const Elysium::Core::Container::VectorOfInt32_t GetSystemLocaleIds(const Template::Globalization::CultureTypes Types);
	private:
#if defined(ELYSIUM_CORE_OS_WINDOWS)
		static Elysium::Core::int32_t EnumerateSystemLocalesExCallback(wchar_t* Name, unsigned long Flags, LPARAM Parameter);
#endif
	};
}
#endif
