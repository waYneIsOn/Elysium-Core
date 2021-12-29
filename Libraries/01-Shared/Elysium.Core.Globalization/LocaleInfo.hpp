/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_INTERNAL_FALLBACK_LOCALEINFO
#define ELYSIUM_CORE_GLOBALIZATION_INTERNAL_FALLBACK_LOCALEINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_SYSTEM
#include "System.hpp"
#endif

#if defined ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION
namespace Elysium::Core::Globalization::Internal::Fallback
{
	class LocaleInfo final
	{
	public:
		LocaleInfo() = delete;
		LocaleInfo(Elysium::Core::int32_t&& Id, Elysium::Core::Utf8String&& Name);
		LocaleInfo(const LocaleInfo& Source) = delete;
		LocaleInfo(LocaleInfo&& Right) noexcept = delete;
		~LocaleInfo();

		LocaleInfo& operator=(const LocaleInfo& Source) = delete;
		LocaleInfo& operator=(LocaleInfo&& Right) noexcept = delete;
	private:
		// ToDo: all fields/properties of CultureInfo
		Elysium::Core::int32_t _Id;
		Elysium::Core::Utf8String _Name;

		// ToDo: all fields/properties of NumberFormatInfo
		//Elysium::Core::int32_t _CurrencyDecimalDigitsId;

		// ToDo: all fields/properties of RegionInfo
	};
}
#endif
#endif
