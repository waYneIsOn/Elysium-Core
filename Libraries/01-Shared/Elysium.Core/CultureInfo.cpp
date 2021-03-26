#include "CultureInfo.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "SystemException.hpp"
#endif

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

Elysium::Core::Globalization::CultureInfo::CultureInfo(const Elysium::Core::int32_t Culture, const bool UseUserOverride)
	: _LCID(Culture), _UseUserOverride(UseUserOverride)
{ }
Elysium::Core::Globalization::CultureInfo::CultureInfo(const Elysium::Core::String Name, const bool UseUserOverride)
	: _LCID(GetLocaleIdFromName(Name)), _UseUserOverride(UseUserOverride)
{ }
Elysium::Core::Globalization::CultureInfo::CultureInfo(const CultureInfo & Source)
	: _LCID(Source._LCID), _UseUserOverride(Source._UseUserOverride)
{ }
Elysium::Core::Globalization::CultureInfo::CultureInfo(CultureInfo && Right) noexcept
	: _LCID(0), _UseUserOverride()
{
	*this = std::move(Right);
}
Elysium::Core::Globalization::CultureInfo::~CultureInfo()
{ }

Elysium::Core::Globalization::CultureInfo & Elysium::Core::Globalization::CultureInfo::operator=(const CultureInfo & Source)
{
	if (this != &Source)
	{
		_LCID = Source._LCID;
		_UseUserOverride = Source._UseUserOverride;
	}
	return *this;
}
Elysium::Core::Globalization::CultureInfo & Elysium::Core::Globalization::CultureInfo::operator=(CultureInfo && Right) noexcept
{
	if (this != &Right)
	{
		_LCID = std::move(Right._LCID);
		_UseUserOverride = std::move(Right._UseUserOverride);
	}
	return *this;
}

const Elysium::Core::Globalization::CultureInfo Elysium::Core::Globalization::CultureInfo::GetInvariantCulture()
{
	return CultureInfo(LOCALE_INVARIANT, false);
}

const Elysium::Core::String Elysium::Core::Globalization::CultureInfo::GetDisplayName() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SNATIVEDISPLAYNAME, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, std::char_traits<wchar_t>::length(Value) * sizeof(wchar_t));
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::CultureInfo::GetEnglishName() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SENGLISHDISPLAYNAME, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, std::char_traits<wchar_t>::length(Value) * sizeof(wchar_t));
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::CultureInfo::GetName() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (LCIDToLocaleName((LCID)_LCID, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH, 0) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, std::char_traits<wchar_t>::length(Value) * sizeof(wchar_t));
#else
#error "undefined os"
#endif
}

const Elysium::Core::int32_t & Elysium::Core::Globalization::CultureInfo::GetLCID() const
{
	return _LCID;
}

Elysium::Core::Globalization::NumberFormatInfo Elysium::Core::Globalization::CultureInfo::GetNumberFormatInfo() const
{
	return Elysium::Core::Globalization::NumberFormatInfo(_LCID, false);
}

Elysium::Core::int32_t Elysium::Core::Globalization::CultureInfo::GetLocaleIdFromName(const Elysium::Core::String& Name)
{
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes =
		Elysium::Core::Text::Encoding::UTF16LE().GetBytes(&Name[0], Name.GetLength(), sizeof(char16_t));
	Elysium::Core::int32_t LCID = LocaleNameToLCID((LPCWSTR)&Bytes[0], 0);
	if (LCID == 0)
	{
		throw SystemException();
	}

	return LCID;
}
