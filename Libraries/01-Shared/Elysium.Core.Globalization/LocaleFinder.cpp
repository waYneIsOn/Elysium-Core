#include "LocaleFinder.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core.Template/System.hpp"
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
	Elysium::Core::Collections::Template::List<Elysium::Core::int32_t>* LCIDs = (Elysium::Core::Collections::Template::List<Elysium::Core::int32_t>*)Parameter;

	Elysium::Core::int32_t LCID = LocaleNameToLCID(Name, 0);
	if (LCID == 0)
	{
		return 0;
	}

	LCIDs->Add(LCID);
	return 1;
}
#endif
