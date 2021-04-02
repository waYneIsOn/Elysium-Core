#include "RegionInfo.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _WINNLS_
#include <WinNls.h>
#endif
#else
#error "undefined os"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef _XSTRING_
#include <xstring>	// std::char_traits
#endif

Elysium::Core::Globalization::RegionInfo::RegionInfo(const Elysium::Core::int32_t Culture)
	: _LCID(Culture)
{ }
Elysium::Core::Globalization::RegionInfo::RegionInfo(const Elysium::Core::String Name)
	: _LCID(GetLocaleIdFromName(Name))
{ }
Elysium::Core::Globalization::RegionInfo::RegionInfo(const RegionInfo& Source)
	: _LCID(Source._LCID)
{ }
Elysium::Core::Globalization::RegionInfo::RegionInfo(RegionInfo&& Right) noexcept
	: _LCID(0)
{
	*this = std::move(Right);
}
Elysium::Core::Globalization::RegionInfo::~RegionInfo()
{ }

Elysium::Core::Globalization::RegionInfo& Elysium::Core::Globalization::RegionInfo::operator=(const RegionInfo& Source)
{
	if (this != &Source)
	{
		_LCID = Source._LCID;
	}
	return *this;
}

Elysium::Core::Globalization::RegionInfo& Elysium::Core::Globalization::RegionInfo::operator=(RegionInfo&& Right) noexcept
{
	if (this != &Right)
	{
		_LCID = std::move(Right._LCID);
	}
	return *this;
}

const Elysium::Core::String Elysium::Core::Globalization::RegionInfo::GetDisplayName() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SLOCALIZEDCOUNTRYNAME, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, std::char_traits<wchar_t>::length(Value) * sizeof(wchar_t));
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::RegionInfo::GetEnglishName() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SENGLISHCOUNTRYNAME, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, std::char_traits<wchar_t>::length(Value) * sizeof(wchar_t));
#else
#error "undefined os"
#endif
}

const bool Elysium::Core::Globalization::RegionInfo::GetIsMetric() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	Elysium::Core::int32_t Value = 48;
	if (GetLocaleInfo((LCID)_LCID, LOCALE_IMEASURE, (LPWSTR)&Value, sizeof(Value) / sizeof(wchar_t)) == 0)
	{
		throw SystemException();
	}

	return (Value - 48) == 0;
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::RegionInfo::GetNativeName() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SNATIVECOUNTRYNAME, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, std::char_traits<wchar_t>::length(Value) * sizeof(wchar_t));
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::RegionInfo::GetThreeLetterISORegionName() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SISO3166CTRYNAME2, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, std::char_traits<wchar_t>::length(Value) * sizeof(wchar_t));
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::RegionInfo::GetTwoLetterISORegionName() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SISO3166CTRYNAME, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, std::char_traits<wchar_t>::length(Value) * sizeof(wchar_t));
#else
#error "undefined os"
#endif
}

Elysium::Core::int32_t Elysium::Core::Globalization::RegionInfo::GetLocaleIdFromName(const Elysium::Core::String& Name)
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes =
		Elysium::Core::Text::Encoding::UTF16LE().GetBytes(&Name[0], Name.GetLength(), sizeof(char16_t));
	Elysium::Core::int32_t LCID = LocaleNameToLCID((LPCWSTR)&Bytes[0], 0);
	if (LCID == 0)
	{
		throw SystemException();
	}

	return LCID;
#else
#error "undefined os"
#endif
}
