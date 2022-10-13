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

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTURETYPES
#include "CultureTypes.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_VECTOROFINT32_T
#include "../Elysium.Core/VectorOfInt32_t.hpp"
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

		static const VectorOfInt32_t GetSystemLocaleIds(const CultureTypes& Types);
	private:
#if defined(ELYSIUM_CORE_OS_WINDOWS)
		static Elysium::Core::int32_t EnumerateSystemLocalesExCallback(wchar_t* Name, unsigned long Flags, LPARAM Parameter);
#endif
	};
}
#endif
