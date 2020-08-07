#include "CultureInfo.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _WINNLS_
#include <WinNls.h>
#endif
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "Exception.hpp"
#endif

Elysium::Core::Globalization::CultureInfo::CultureInfo()
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	: Elysium::Core::Globalization::CultureInfo::CultureInfo(GetSystemDefaultLCID())
	// ToDo: use GetUserDefaultLCID instead?
#elif defined(__ANDROID__)
	: Elysium::Core::Globalization::CultureInfo::CultureInfo(0)
	// ToDo: how to get the current locale id on android? getDefaultLocale()?
#endif
{
}
Elysium::Core::Globalization::CultureInfo::CultureInfo(int Culture)
	: _LCID(Culture)
{
}
Elysium::Core::Globalization::CultureInfo::CultureInfo(const CultureInfo & Source)
	: _LCID(Source._LCID)
{
}
Elysium::Core::Globalization::CultureInfo::CultureInfo(CultureInfo && Right) noexcept
	: _LCID(0)
{
	*this = std::move(Right);
}
Elysium::Core::Globalization::CultureInfo::~CultureInfo()
{
}

Elysium::Core::Globalization::CultureInfo & Elysium::Core::Globalization::CultureInfo::operator=(const CultureInfo & Source)
{
	if (this != &Source)
	{
		_LCID = int(Source._LCID);
	}
	return *this;
}
Elysium::Core::Globalization::CultureInfo & Elysium::Core::Globalization::CultureInfo::operator=(CultureInfo && Right) noexcept
{
	if (this != &Right)
	{
		_LCID = Right._LCID;

		Right._LCID = 0;
	}
	return *this;
}

void Elysium::Core::Globalization::CultureInfo::GetName(String * Output) const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	*Output = String(LOCALE_NAME_MAX_LENGTH);
	if (LCIDToLocaleName((LCID)_LCID, (LPWSTR)Output->GetCharArray(), LOCALE_NAME_MAX_LENGTH, 0) == 0)
	{
		unsigned long LastError = GetLastError();
		// ToDo: throw specific exception
		throw Exception(u8"couldn't get locale name from locale id");
	}
#elif defined(__ANDROID__)
	// ToDo: ...
#else
#error "undefined os"
#endif
}
int Elysium::Core::Globalization::CultureInfo::GetLCID() const
{
	return _LCID;
}
