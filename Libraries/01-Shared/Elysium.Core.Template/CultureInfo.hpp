/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTUREINFO
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTUREINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTURETYPES
#include "CultureTypes.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_NUMBERFORMATINFO
#include "NumberFormatInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
#else
#error "undefined os"
#endif

namespace Elysium::Core::Template::Globalization
{
	template <Concepts::Character C>
	class CultureInfo final
	{
	public:
		using ConstCharacterPointer = const C*;

		using CorrespondingString = Text::String<C>;
	public:
		CultureInfo() noexcept;

		CultureInfo(const System::uint32_t LocaleId, const bool UseUserOverride) noexcept;

		CultureInfo(ConstCharacterPointer Name, const bool UseUserOverride);

		CultureInfo(const CultureInfo& Source) noexcept;

		CultureInfo(CultureInfo&& Right) noexcept;

		~CultureInfo() noexcept;
	public:
		CultureInfo<C>& operator=(const CultureInfo& Source) noexcept;

		CultureInfo<C>& operator=(CultureInfo&& Right) noexcept;
	public:
		static const CultureInfo<C> GetInvariantCulture();

		static const Container::Vector<CultureInfo<C>> GetCultures(const CultureTypes& Types);
	public:
		const CorrespondingString GetDisplayName() const;

		const CorrespondingString GetEnglishName() const;

		const CorrespondingString GetName() const;

		const System::uint32_t& GetLCID() const;

		const NumberFormatInfo<C> GetNumberFormatInfo() const;
	public:
		NumberFormatInfo<C> GetNumberFormatInfo();
	private:
		static System::int32_t EnumerateSystemLocalesExCallback(wchar_t* Name, unsigned long Flags, LPARAM Parameter);
	private:
		System::uint32_t GetLocaleIdFromName(ConstCharacterPointer Name);
	private:
		System::uint32_t _LocaleId;
		bool _UseUserOverride;
	};

	template<Concepts::Character C>
	inline CultureInfo<C>::CultureInfo() noexcept
		: _LocaleId(LOCALE_INVARIANT), _UseUserOverride(false)
	{ }

	template<Concepts::Character C>
	inline CultureInfo<C>::CultureInfo(const System::uint32_t LocaleId, const bool UseUserOverride) noexcept
		: _LocaleId(LocaleId), _UseUserOverride(UseUserOverride)
	{ }

	template<Concepts::Character C>
	inline CultureInfo<C>::CultureInfo(ConstCharacterPointer Name, const bool UseUserOverride)
		: _LocaleId(GetLocaleIdFromName(Name)), _UseUserOverride(UseUserOverride)
	{ }

	template<Concepts::Character C>
	inline CultureInfo<C>::CultureInfo(const CultureInfo&Source) noexcept
		: _LocaleId(Source._LocaleId), _UseUserOverride(Source._UseUserOverride)
	{ }

	template<Concepts::Character C>
	inline CultureInfo<C>::CultureInfo(CultureInfo&& Right) noexcept
		: _LocaleId(0), _UseUserOverride(false)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<Concepts::Character C>
	inline CultureInfo<C>::~CultureInfo() noexcept
	{ }

	template<Concepts::Character C>
	inline CultureInfo<C>& Elysium::Core::Template::Globalization::CultureInfo<C>::operator=(const CultureInfo& Source) noexcept
	{
		if (this != &Source)
		{
			_LocaleId = Source._LocaleId;
			_UseUserOverride = Source._UseUserOverride;
		}
		return *this;
	}

	template<Concepts::Character C>
	inline CultureInfo<C>& Elysium::Core::Template::Globalization::CultureInfo<C>::operator=(CultureInfo&& Right) noexcept
	{
		if (this != &Right)
		{
			_LocaleId = Elysium::Core::Template::Functional::Move(Right._LocaleId);
			_UseUserOverride = Elysium::Core::Template::Functional::Move(Right._UseUserOverride);

			Right._LocaleId = 0;
			Right._UseUserOverride = false;
		}
		return *this;
	}

	template<Concepts::Character C>
	inline const CultureInfo<C> Elysium::Core::Template::Globalization::CultureInfo<C>::GetInvariantCulture()
	{
		return CultureInfo(LOCALE_INVARIANT, false);
	}

	template<Concepts::Character C>
	inline const Container::Vector<CultureInfo<C>> CultureInfo<C>::GetCultures(const CultureTypes& Types)
	{	// I can assume at least one installed language pack
		Container::Vector<System::uint32_t> LocaleIds = Container::Vector<System::uint32_t>(1);
#if defined ELYSIUM_CORE_OS_WINDOWS
		// ToDo: convert Types to second parameter correctly! (example: LOCALE_ALL = 0)
		while (EnumSystemLocalesEx(EnumerateSystemLocalesExCallback, static_cast<unsigned long>(Types), (LPARAM)&LocaleIds, nullptr) == 0)
		{ }

		const System::size LocaleIdsLength = LocaleIds.GetLength();
		Container::Vector<CultureInfo<C>> Locales = Container::Vector<CultureInfo<C>>(LocaleIdsLength);
		for (System::size i = 0; i < LocaleIdsLength; i++)
		{
			Locales[i] = CultureInfo<C>(LocaleIds[i], true);
		}

#else
#error "undefined os"
#endif
		return Locales;
	}

	template<>
	inline const CultureInfo<char>::CorrespondingString CultureInfo<char>::GetDisplayName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNATIVEDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const CultureInfo<wchar_t>::CorrespondingString CultureInfo<wchar_t>::GetDisplayName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNATIVEDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const CultureInfo<C>::CorrespondingString CultureInfo<C>::GetDisplayName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNATIVEDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const CultureInfo<char>::CorrespondingString CultureInfo<char>::GetEnglishName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SENGLISHDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const CultureInfo<wchar_t>::CorrespondingString CultureInfo<wchar_t>::GetEnglishName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SENGLISHDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const CultureInfo<C>::CorrespondingString CultureInfo<C>::GetEnglishName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SENGLISHDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const CultureInfo<wchar_t>::CorrespondingString CultureInfo<wchar_t>::GetName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (LCIDToLocaleName(_LocaleId, (LPWSTR)&Buffer[0], LOCALE_NAME_MAX_LENGTH, 0) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const CultureInfo<C>::CorrespondingString CultureInfo<C>::GetName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (LCIDToLocaleName(_LocaleId, (LPWSTR)&Buffer[0], LOCALE_NAME_MAX_LENGTH, 0) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const System::uint32_t& CultureInfo<C>::GetLCID() const
	{
		return _LocaleId;
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C> CultureInfo<C>::GetNumberFormatInfo() const
	{
		return NumberFormatInfo<C>(_LocaleId, false);
	}

	template<Concepts::Character C>
	inline NumberFormatInfo<C> CultureInfo<C>::GetNumberFormatInfo()
	{
		return NumberFormatInfo<C>(_LocaleId, false);
	}

	template<Concepts::Character C>
	inline System::int32_t CultureInfo<C>::EnumerateSystemLocalesExCallback(wchar_t* Name, unsigned long Flags, LPARAM Parameter)
	{
		System::uint32_t LocaleId = LocaleNameToLCID(Name, 0);
		if (LocaleId == 0)
		{
			return 0;
		}

		((Container::Vector<System::uint32_t>*)Parameter)->PushBack(LocaleId);

		return 1;
	}

	template<>
	inline System::uint32_t CultureInfo<wchar_t>::GetLocaleIdFromName(ConstCharacterPointer Name)
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t LocaleId = LocaleNameToLCID(Name, 0);
		if (LocaleId == 0)
		{
			throw SystemException();
		}

		return LocaleId;
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline System::uint32_t CultureInfo<C>::GetLocaleIdFromName(ConstCharacterPointer Name)
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideName = Text::Unicode::Utf16::SafeToWideString<C>(Name, Text::CharacterTraits<C>::GetLength(Name));
		System::uint32_t LocaleId = LocaleNameToLCID(&WideName[0], 0);
		if (LocaleId == 0)
		{
			throw SystemException();
		}

		return LocaleId;
#else
#error "undefined os"
#endif
	}
}
#endif
