/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_REGIONINFO
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_REGIONINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
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
	class RegionInfo final
	{
	public:
		using ConstCharacterPointer = const C*;

		using CorrespondingString = Text::String<C>;
	public:
		RegionInfo() noexcept;

		RegionInfo(const System::uint32_t LocaleId) noexcept;

		RegionInfo(ConstCharacterPointer Name);

		RegionInfo(const RegionInfo& Source) noexcept;

		RegionInfo(RegionInfo&& Right) noexcept;

		~RegionInfo() noexcept;
	public:
		RegionInfo<C>& operator=(const RegionInfo& Source) noexcept;

		RegionInfo<C>& operator=(RegionInfo&& Right) noexcept;
	public:
		const CorrespondingString GetDisplayName() const;

		const CorrespondingString GetEnglishName() const;

		const bool GetIsMetric() const;

		const CorrespondingString GetNativeName() const;

		const CorrespondingString GetThreeLetterISORegionName() const;

		const CorrespondingString GetTwoLetterISORegionName() const;
	private:
		System::uint32_t GetLocaleIdFromName(ConstCharacterPointer Name);
	private:
		System::uint32_t _LocaleId;
	};

	template<Concepts::Character C>
	inline RegionInfo<C>::RegionInfo() noexcept
		: _LocaleId(LOCALE_INVARIANT)
	{ }

	template<Concepts::Character C>
	inline RegionInfo<C>::RegionInfo(const System::uint32_t LocaleId) noexcept
		: _LocaleId(LocaleId)
	{ }

	template<Concepts::Character C>
	inline RegionInfo<C>::RegionInfo(ConstCharacterPointer Name)
		: _LocaleId(GetLocaleIdFromName(Name))
	{ }

	template<Concepts::Character C>
	inline RegionInfo<C>::RegionInfo(const RegionInfo& Source) noexcept
		: _LocaleId(Source._LocaleId)
	{ }

	template<Concepts::Character C>
	inline RegionInfo<C>::RegionInfo(RegionInfo&& Right) noexcept
		: _LocaleId(0)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<Concepts::Character C>
	inline RegionInfo<C>::~RegionInfo() noexcept
	{ }

	template<Concepts::Character C>
	inline RegionInfo<C>& Elysium::Core::Template::Globalization::RegionInfo<C>::operator=(const RegionInfo& Source) noexcept
	{
		if (this != &Source)
		{
			_LocaleId = Source._LocaleId;
		}
		return *this;
	}

	template<Concepts::Character C>
	inline RegionInfo<C>& Elysium::Core::Template::Globalization::RegionInfo<C>::operator=(RegionInfo&& Right) noexcept
	{
		if (this != &Right)
		{
			_LocaleId = Elysium::Core::Template::Functional::Move(Right._LocaleId);

			Right._LocaleId = 0;
		}
		return *this;
	}

	template<>
	inline const RegionInfo<char>::CorrespondingString RegionInfo<char>::GetDisplayName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SLOCALIZEDCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetDisplayName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SLOCALIZEDCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const RegionInfo<C>::CorrespondingString RegionInfo<C>::GetDisplayName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SLOCALIZEDCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const RegionInfo<char>::CorrespondingString RegionInfo<char>::GetEnglishName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SENGLISHCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetEnglishName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SENGLISHCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const RegionInfo<C>::CorrespondingString RegionInfo<C>::GetEnglishName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SENGLISHCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const bool RegionInfo<C>::GetIsMetric() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t Result = -1;
		if (GetLocaleInfoW(_LocaleId, LOCALE_IMEASURE | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
		{
			throw SystemException();
		}

		return Result == 0;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const RegionInfo<char>::CorrespondingString RegionInfo<char>::GetNativeName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNATIVECOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetNativeName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNATIVECOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		return Buffer;
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const RegionInfo<C>::CorrespondingString RegionInfo<C>::GetNativeName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNATIVECOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const RegionInfo<char>::CorrespondingString RegionInfo<char>::GetThreeLetterISORegionName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SISO3166CTRYNAME2, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// three letters will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetThreeLetterISORegionName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SISO3166CTRYNAME2, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// three letters will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const RegionInfo<C>::CorrespondingString RegionInfo<C>::GetThreeLetterISORegionName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SISO3166CTRYNAME2, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// three letters will fit onto the stack which is why I get the actual length here
		return Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const RegionInfo<char>::CorrespondingString RegionInfo<char>::GetTwoLetterISORegionName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SISO3166CTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// two letters will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetTwoLetterISORegionName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SISO3166CTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// two letters will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const RegionInfo<C>::CorrespondingString RegionInfo<C>::GetTwoLetterISORegionName() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SISO3166CTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// two letters will fit onto the stack which is why I get the actual length here
		return Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
#else
#error "undefined os"
#endif
	}

	template<>
	inline System::uint32_t RegionInfo<wchar_t>::GetLocaleIdFromName(ConstCharacterPointer Name)
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
	inline System::uint32_t RegionInfo<C>::GetLocaleIdFromName(ConstCharacterPointer Name)
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
