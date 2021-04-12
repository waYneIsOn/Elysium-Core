#include "LocaleFinder.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

const Elysium::Core::Collections::Template::List<Elysium::Core::int32_t> Elysium::Core::Globalization::Internal::LocaleFinder::GetSystemLocaleIds(const CultureTypes& Types)
{
	Elysium::Core::Collections::Template::List<Elysium::Core::int32_t> LCIDs = Elysium::Core::Collections::Template::List<Elysium::Core::int32_t>();

#if defined(ELYSIUM_CORE_OS_WINDOWS)
	// ToDo: convert Types to second parameter correctly! (example: LOCALE_ALL = 0)
	while (EnumSystemLocalesEx(EnumerateSystemLocalesExCallback, static_cast<unsigned long>(Types), (LPARAM)&LCIDs, nullptr) == 0)
	{ }
#else
#error "undefined os"
#endif

	return LCIDs;
}

Elysium::Core::int32_t Elysium::Core::Globalization::Internal::LocaleFinder::EnumerateSystemLocalesExCallback(wchar_t* Name, unsigned long Flags, LPARAM Parameter)
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	Elysium::Core::Collections::Template::List<Elysium::Core::int32_t>* LCIDs = (Elysium::Core::Collections::Template::List<Elysium::Core::int32_t>*)Parameter;

	Elysium::Core::int32_t LCID = LocaleNameToLCID(Name, 0);
	if (LCID == 0)
	{
		return 0;
	}

	LCIDs->Add(LCID);
#else
#error "undefined os"
#endif
	return 1;
}
