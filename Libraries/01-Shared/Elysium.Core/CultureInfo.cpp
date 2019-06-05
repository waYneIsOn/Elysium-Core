#include "CultureInfo.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _WINNLS_
#include <WinNls.h>
#endif
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

Elysium::Core::CultureInfo::CultureInfo()
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	: Elysium::Core::CultureInfo::CultureInfo(GetSystemDefaultLCID())
	// ToDo: use GetUserDefaultLCID instead?
#elif defined(__ANDROID__)
	: Elysium::Core::CultureInfo::CultureInfo(0)
	// ToDo: how to get the current locale id on android? getDefaultLocale()?
#endif
{
}
Elysium::Core::CultureInfo::CultureInfo(int Culture)
	: _Culture(Culture)
{
}
Elysium::Core::CultureInfo::~CultureInfo()
{
}

void Elysium::Core::CultureInfo::GetName(String * Output) const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	*Output = String(LOCALE_NAME_MAX_LENGTH);
	if (LCIDToLocaleName((LCID)_Culture, (LPWSTR)Output->GetCharArray(), LOCALE_NAME_MAX_LENGTH, 0) == 0)
	{
		unsigned long LastError = GetLastError();
		// ToDo: throw specific exception
		throw Exception(L"couldn't get locale name from locale id");
	}
#elif defined(__ANDROID__)
	// ToDo: ...
#else
#error "undefined os"
#endif
}
int Elysium::Core::CultureInfo::GetLCID() const
{
	return _Culture;
}
