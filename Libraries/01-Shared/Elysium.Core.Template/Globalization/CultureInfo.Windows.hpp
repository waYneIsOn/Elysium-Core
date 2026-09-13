/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTUREINFO_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTUREINFO_WINDOWS

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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTURETYPES
#include "CultureTypes.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_NUMBERFORMATINFO
#include "NumberFormatInfo.hpp"
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
	class CultureInfo final
	{
	public:
		using ConstCharacterPointer = const C*;

		using CorrespondingString = Text::String<C>;
	public:
		inline constexpr CultureInfo() noexcept
			: _LocaleId(LOCALE_INVARIANT), _UseUserOverride(false)
		{ }

		inline constexpr CultureInfo(const System::uint32_t LocaleId, const bool UseUserOverride) noexcept
			: _LocaleId(LocaleId), _UseUserOverride(UseUserOverride)
		{ }

		inline constexpr CultureInfo(ConstCharacterPointer Name, const bool UseUserOverride)
			: _LocaleId(GetLocaleIdFromName(Name)), _UseUserOverride(UseUserOverride)
		{ }

		inline constexpr CultureInfo(const CultureInfo& Source) noexcept
			: _LocaleId(Source._LocaleId), _UseUserOverride(Source._UseUserOverride)
		{ }

		inline constexpr CultureInfo(CultureInfo&& Right) noexcept
			: _LocaleId(0), _UseUserOverride(false)
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~CultureInfo() noexcept = default;
	public:
		inline constexpr CultureInfo<C>& operator=(const CultureInfo& Source) noexcept
		{
			if (this != &Source)
			{
				_LocaleId = Source._LocaleId;
				_UseUserOverride = Source._UseUserOverride;
			}
			return *this;
		}

		inline constexpr CultureInfo<C>& operator=(CultureInfo&& Right) noexcept
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
	public:
		inline static const CultureInfo<C> GetInvariantCulture()
		{
			return CultureInfo(LOCALE_INVARIANT, false);
		}

		inline static const Elysium::Core::Template::Container::Vector<CultureInfo<C>> GetCultures(const CultureTypes& Types)
		{	// I can assume at least one installed language pack
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::uint32_t> LocaleIds(1);

			// @ToDo: convert Types to second parameter correctly! (example: LOCALE_ALL = 0)
			while (EnumSystemLocalesEx(EnumerateSystemLocalesExCallback, static_cast<unsigned long>(Types), (LPARAM)&LocaleIds, nullptr) == 0)
			{ }

			const Elysium::Core::Template::System::size LocaleIdsLength = LocaleIds.GetLength();
			Elysium::Core::Template::Container::Vector<CultureInfo<C>> Locales(LocaleIdsLength);
			for (Elysium::Core::Template::System::size i = 0; i < LocaleIdsLength; i++)
			{
				Locales[i] = CultureInfo<C>(LocaleIds[i], true);
			}

			return Locales;
		}
	public:
		constexpr const CorrespondingString GetDisplayName() const;

		constexpr const CorrespondingString GetEnglishName() const;

		constexpr const CorrespondingString GetName() const;

		inline constexpr const Elysium::Core::Template::System::uint32_t& GetLCID() const
		{
			return _LocaleId;
		}

		inline constexpr const NumberFormatInfo<C> GetNumberFormatInfo() const
		{
			return NumberFormatInfo<C>(_LocaleId, false);
		}

		inline constexpr const NumberFormatInfo<C> GetNumberFormatInfo()
		{
			return NumberFormatInfo<C>(_LocaleId, false);
		}
	private:
		inline static Elysium::Core::Template::System::int32_t EnumerateSystemLocalesExCallback(wchar_t* Name, unsigned long Flags, LPARAM Parameter)
		{
			LCID LocaleId = LocaleNameToLCID(Name, 0);
			if (0 == LocaleId)
			{
				return 0;
			}

			((Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::uint32_t>*)Parameter)->PushBack(LocaleId);

			return 1;
		}
	private:
		Elysium::Core::Template::System::uint32_t GetLocaleIdFromName(ConstCharacterPointer Name);
	private:
		Elysium::Core::Template::System::uint32_t _LocaleId;
		bool _UseUserOverride;
	};

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::CultureInfo<char>::CorrespondingString CultureInfo<char>::GetDisplayName() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNATIVEDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::CultureInfo<wchar_t>::CorrespondingString CultureInfo<wchar_t>::GetDisplayName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNATIVEDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<Concepts::Character C>
	inline constexpr const Elysium::Core::Template::Globalization::CultureInfo<C>::CorrespondingString CultureInfo<C>::GetDisplayName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNATIVEDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::CultureInfo<char>::CorrespondingString CultureInfo<char>::GetEnglishName() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SENGLISHDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::CultureInfo<wchar_t>::CorrespondingString CultureInfo<wchar_t>::GetEnglishName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SENGLISHDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return Buffer;
	}

	template<Concepts::Character C>
	inline constexpr const Elysium::Core::Template::Globalization::CultureInfo<C>::CorrespondingString CultureInfo<C>::GetEnglishName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SENGLISHDISPLAYNAME, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline constexpr const Elysium::Core::Template::Globalization::CultureInfo<wchar_t>::CorrespondingString CultureInfo<wchar_t>::GetName() const
	{
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (LCIDToLocaleName(_LocaleId, (LPWSTR)&Buffer[0], LOCALE_NAME_MAX_LENGTH, 0) == 0)
		{
			throw Exceptions::SystemException();
		}

		return Buffer;
	}

	template<Concepts::Character C>
	inline constexpr const Elysium::Core::Template::Globalization::CultureInfo<C>::CorrespondingString CultureInfo<C>::GetName() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (LCIDToLocaleName(_LocaleId, (LPWSTR)&Buffer[0], LOCALE_NAME_MAX_LENGTH, 0) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline Elysium::Core::Template::System::uint32_t Elysium::Core::Template::Globalization::CultureInfo<wchar_t>::GetLocaleIdFromName(ConstCharacterPointer Name)
	{
		Elysium::Core::Template::System::uint32_t LocaleId = LocaleNameToLCID(Name, 0);
		if (LocaleId == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return LocaleId;
	}

	template<Concepts::Character C>
	inline Elysium::Core::Template::System::uint32_t Elysium::Core::Template::Globalization::CultureInfo<C>::GetLocaleIdFromName(ConstCharacterPointer Name)
	{
		Elysium::Core::Template::Text::String<wchar_t> WideName = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString<C>(Name,
			Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Name));
		Elysium::Core::Template::System::uint32_t LocaleId = LocaleNameToLCID(&WideName[0], 0);
		if (LocaleId == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		return LocaleId;
	}
}
#endif
#endif
