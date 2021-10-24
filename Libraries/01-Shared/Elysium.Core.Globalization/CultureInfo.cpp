#include "CultureInfo.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGTRAITS
#include "../Elysium.Core.Template/StringTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_INTERNAL_LOCALEFINDER
#include "LocaleFinder.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_SYSTEM
#include "System.hpp"
#endif

#if defined ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION
#ifndef ELYSIUM_CORE_GLOBALIZATION_INTERNAL_FALLBACK_LOCALEREPOSITORY
#include "LocaleRepository.hpp"
#endif
#endif

Elysium::Core::Globalization::CultureInfo::CultureInfo()
	: _LCID(ELYSIUM_CORE_GLOBALIZATION_LOCALE_INVARIANT), _UseUserOverride(false)
{ }

Elysium::Core::Globalization::CultureInfo::CultureInfo(const Elysium::Core::int32_t Culture, const bool UseUserOverride)
	: _LCID(Culture), _UseUserOverride(UseUserOverride)
{ }

Elysium::Core::Globalization::CultureInfo::CultureInfo(const Elysium::Core::String& Name, const bool UseUserOverride)
	: _LCID(GetLocaleIdFromName(Name)), _UseUserOverride(UseUserOverride)
{ }

Elysium::Core::Globalization::CultureInfo::CultureInfo(const CultureInfo & Source)
	: _LCID(Source._LCID), _UseUserOverride(Source._UseUserOverride)
{ }

Elysium::Core::Globalization::CultureInfo::CultureInfo(CultureInfo && Right) noexcept
	: _LCID(-1), _UseUserOverride()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
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
		_LCID = Elysium::Core::Template::Functional::Move(Right._LCID);
		_UseUserOverride = Elysium::Core::Template::Functional::Move(Right._UseUserOverride);
	}
	return *this;
}

const Elysium::Core::Globalization::CultureInfo Elysium::Core::Globalization::CultureInfo::GetInvariantCulture()
{
	return CultureInfo();
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::Globalization::CultureInfo> Elysium::Core::Globalization::CultureInfo::GetCultures(const CultureTypes& Types)
{
	const Elysium::Core::Collections::Template::List<Elysium::Core::int32_t> LCIDs = Internal::LocaleFinder::GetSystemLocaleIds(Types);
	Elysium::Core::Collections::Template::Array<CultureInfo> CultureInfos = Elysium::Core::Collections::Template::Array<CultureInfo>(LCIDs.GetCount());
	for (Elysium::Core::size i = 0; i < CultureInfos.GetLength(); i++)
	{
		CultureInfos[i]._LCID = LCIDs[i];
	}

	return CultureInfos;
}

const Elysium::Core::String Elysium::Core::Globalization::CultureInfo::GetDisplayName() const
{
#if defined (ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION)
	throw 1;
#elif defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SNATIVEDISPLAYNAME, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, Elysium::Core::Template::Text::StringTraits<wchar_t>::GetByteLength(Value));
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::CultureInfo::GetEnglishName() const
{
#if defined (ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION)
	throw 1;
#elif defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SENGLISHDISPLAYNAME, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, Elysium::Core::Template::Text::StringTraits<wchar_t>::GetByteLength(Value));
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::CultureInfo::GetName() const
{
#if defined (ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION)
	return Internal::Fallback::LocaleRepository::GetNameFromId(_LCID);
#elif defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (LCIDToLocaleName((LCID)_LCID, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH, 0) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, Elysium::Core::Template::Text::StringTraits<wchar_t>::GetByteLength(Value));
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
#if defined (ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION)
	throw 1;
#elif defined(ELYSIUM_CORE_OS_WINDOWS)
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
