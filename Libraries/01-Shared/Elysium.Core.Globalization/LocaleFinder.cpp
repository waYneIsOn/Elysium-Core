#include "LocaleFinder.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

const VectorOfInt32_t Elysium::Core::Globalization::Internal::LocaleFinder::GetSystemLocaleIds(const CultureTypes& Types)
{
	VectorOfInt32_t LCIDs = VectorOfInt32_t();

#if defined(ELYSIUM_CORE_OS_WINDOWS)
	// ToDo: convert Types to second parameter correctly! (example: LOCALE_ALL = 0)
	while (EnumSystemLocalesEx(EnumerateSystemLocalesExCallback, static_cast<unsigned long>(Types), (LPARAM)&LCIDs, nullptr) == 0)
	{ }
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	throw 1;
#else
#error "undefined os"
#endif

	return LCIDs;
}

#if defined(ELYSIUM_CORE_OS_WINDOWS)
Elysium::Core::int32_t Elysium::Core::Globalization::Internal::LocaleFinder::EnumerateSystemLocalesExCallback(wchar_t* Name, unsigned long Flags, LPARAM Parameter)
{
	VectorOfInt32_t* LCIDs = (VectorOfInt32_t*)Parameter;

	Elysium::Core::int32_t LCID = LocaleNameToLCID(Name, 0);
	if (LCID == 0)
	{
		return 0;
	}

	LCIDs->PushBack(LCID);
	return 1;
}
#endif
