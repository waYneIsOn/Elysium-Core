/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_REGIONINFO_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_REGIONINFO_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "../Concepts/Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../Exceptions/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Text/Unicode/Utf16.hpp"
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
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
		inline constexpr RegionInfo() noexcept
			: _LocaleId(LOCALE_INVARIANT)
		{ }

		inline constexpr RegionInfo(const System::uint32_t LocaleId) noexcept
			: _LocaleId(LocaleId)
		{ }

		inline constexpr RegionInfo(ConstCharacterPointer Name)
			: _LocaleId(GetLocaleIdFromName(Name))
		{ }

		inline constexpr RegionInfo(const RegionInfo& Source) noexcept
			: _LocaleId(Source._LocaleId)
		{ }

		inline constexpr RegionInfo(RegionInfo&& Right) noexcept
			: _LocaleId(0)
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~RegionInfo() noexcept = default;
	public:
		inline constexpr RegionInfo<C>& operator=(const RegionInfo& Source) noexcept
		{
			if (this != &Source)
			{
				_LocaleId = Source._LocaleId;
			}
			return *this;
		}

		inline constexpr RegionInfo<C>& operator=(RegionInfo&& Right) noexcept
		{
			if (this != &Right)
			{
				_LocaleId = Elysium::Core::Template::Functional::Move(Right._LocaleId);

				Right._LocaleId = 0;
			}
			return *this;
		}
	public:
		constexpr const CorrespondingString GetDisplayName() const;

		constexpr const CorrespondingString GetEnglishName() const;

		inline constexpr const bool GetIsMetric() const
		{
			Elysium::Core::Template::System::uint32_t Result = -1;
			if (GetLocaleInfoW(_LocaleId, LOCALE_IMEASURE | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
			{
				throw Exceptions::SystemException();
			}

			return Result == 0;
		}

		constexpr const CorrespondingString GetNativeName() const;

		constexpr const CorrespondingString GetThreeLetterISORegionName() const;

		constexpr const CorrespondingString GetTwoLetterISORegionName() const;
	private:
		Elysium::Core::Template::System::uint32_t GetLocaleIdFromName(ConstCharacterPointer Name);
	private:
		Elysium::Core::Template::System::uint32_t _LocaleId;
	};

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<char>::CorrespondingString RegionInfo<char>::GetDisplayName() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SLOCALIZEDCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetDisplayName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SLOCALIZEDCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<Concepts::Character C>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<C>::CorrespondingString RegionInfo<C>::GetDisplayName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SLOCALIZEDCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<char>::CorrespondingString RegionInfo<char>::GetEnglishName() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SENGLISHCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetEnglishName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SENGLISHCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<Concepts::Character C>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<C>::CorrespondingString RegionInfo<C>::GetEnglishName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SENGLISHCOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<char>::CorrespondingString RegionInfo<char>::GetNativeName() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNATIVECOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetNativeName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNATIVECOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<Concepts::Character C>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<C>::CorrespondingString RegionInfo<C>::GetNativeName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNATIVECOUNTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<char>::CorrespondingString RegionInfo<char>::GetThreeLetterISORegionName() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SISO3166CTRYNAME2, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// three letters will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetThreeLetterISORegionName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SISO3166CTRYNAME2, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// three letters will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<C>::CorrespondingString RegionInfo<C>::GetThreeLetterISORegionName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SISO3166CTRYNAME2, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// three letters will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<char>::CorrespondingString RegionInfo<char>::GetTwoLetterISORegionName() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SISO3166CTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// two letters will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<wchar_t>::CorrespondingString RegionInfo<wchar_t>::GetTwoLetterISORegionName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SISO3166CTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// two letters will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline constexpr const Elysium::Core::Template::Globalization::RegionInfo<C>::CorrespondingString RegionInfo<C>::GetTwoLetterISORegionName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SISO3166CTRYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// two letters will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline System::uint32_t Elysium::Core::Template::Globalization::RegionInfo<wchar_t>::GetLocaleIdFromName(ConstCharacterPointer Name)
	{
		Elysium::Core::Template::System::uint32_t LocaleId = LocaleNameToLCID(Name, 0);
		if (LocaleId == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return LocaleId;
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint32_t Elysium::Core::Template::Globalization::RegionInfo<C>::GetLocaleIdFromName(ConstCharacterPointer Name)
	{
		Elysium::Core::Template::Text::String<wchar_t> WideName = 
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString<C>(Name, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Name));
		Elysium::Core::Template::System::uint32_t LocaleId = LocaleNameToLCID(&WideName[0], 0);
		if (LocaleId == 0)
		{
			throw Exceptions::SystemException();
		}

		return LocaleId;
	}
}
#endif
#endif
