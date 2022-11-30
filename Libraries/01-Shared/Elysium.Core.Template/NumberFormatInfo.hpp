/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_NUMBERFORMATINFO
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_NUMBERFORMATINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_DIGITSHAPES
#include "DigitShapes.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_POWER
#include "Power.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "Utf16.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
#else
#error "undefined os"
#endif

#ifndef _CMATH_
#include <cmath>
#endif

namespace Elysium::Core::Template::Globalization
{
	template <Concepts::Character C>
	class NumberFormatInfo
	{
	public:
		using ConstCharacterPointer = const C*;

		using CorrespondingString = Text::String<C>;
	public:
		NumberFormatInfo(const System::uint32_t LocaleId, const bool ReadOnly) noexcept;

		NumberFormatInfo(const NumberFormatInfo& Source) noexcept;

		NumberFormatInfo(NumberFormatInfo&& Right) noexcept;

		~NumberFormatInfo() noexcept;
	public:
		NumberFormatInfo<C>& operator=(const NumberFormatInfo& Source) noexcept;

		NumberFormatInfo<C>& operator=(NumberFormatInfo&& Right) noexcept;
	public:
		static constexpr const NumberFormatInfo GetCurrentInfo();

		static constexpr const NumberFormatInfo GetInvariantInfo();
	public:
		const bool GetIsReadOnly() const;
	public:
		const System::uint32_t GetCurrencyDecimalDigits() const;

		const CorrespondingString GetCurrencyDecimalSeparator() const;

		const CorrespondingString GetCurrencyGroupSeparator() const;

		const System::uint32_t GetCurrencyNegativePattern() const;

		const System::uint32_t GetCurrencyPositivePattern() const;

		const CorrespondingString GetCurrencySymbol() const;

		const DigitShapes GetDigitSubstitution() const;

		const CorrespondingString GetNaNSymbol() const;

		const CorrespondingString GetNegativeInfinitySymbol() const;

		const CorrespondingString GetNegativeSign() const;

		const System::uint32_t GetNumberDecimalDigits() const;

		const CorrespondingString GetNumberDecimalSeparator() const;

		const CorrespondingString GetNumberGroupSeparator() const;

		const System::uint32_t GetPercentDecimalDigits() const;

		const CorrespondingString GetPercentDecimalSeparator() const;

		const CorrespondingString GetPercentGroupSeparator() const;

		const System::uint32_t GetPercentNegativePattern() const;

		const System::uint32_t GetPercentPositivePattern() const;

		const CorrespondingString GetPercentSymbol() const;

		const CorrespondingString GetPerMilleSymbol() const;

		const CorrespondingString GetPositiveInfinitySymbol() const;

		const CorrespondingString GetPositiveSign() const;
	public:
		void SetCurrencyDecimalDigits(const System::uint32_t Value);

		void SetCurrencyDecimalSeparator(const ConstCharacterPointer Value);

		void SetCurrencyGroupSeparator(const ConstCharacterPointer Value);

		void SetCurrencyNegativePattern(const System::uint32_t Value);

		void SetCurrencyPositivePattern(const System::uint32_t Value);

		void SetCurrencySymbol(const ConstCharacterPointer Value);

		void SetDigitSubstitution(const DigitShapes Value);

		void SetNaNSymbol(const ConstCharacterPointer Value);

		void SetNegativeInfinitySymbol(const ConstCharacterPointer Value);

		void SetNegativeSign(const ConstCharacterPointer Value);

		void SetNumberDecimalDigits(const System::uint32_t Value);

		void SetNumberDecimalSeparator(const ConstCharacterPointer Value);

		void SetNumberGroupSeparator(const ConstCharacterPointer Value);

		void SetPercentDecimalDigits(const System::uint32_t Value);

		void SetPercentDecimalSeparator(const ConstCharacterPointer Value);

		void SetPercentGroupSeparator(const ConstCharacterPointer Value);

		void SetPercentNegativePattern(const System::uint32_t Value);

		void SetPercentPositivePattern(const System::uint32_t Value);

		void SetPercentSymbol(const ConstCharacterPointer Value);

		void SetPerMilleSymbol(const ConstCharacterPointer Value);

		void SetPositiveInfinitySymbol(const ConstCharacterPointer Value);

		void SetPositiveSign(const ConstCharacterPointer Value);
	private:
		Text::String<char> ToString(System::uint32_t Value);

		Text::String<wchar_t> ToWideString(System::uint32_t Value);
	private:
		System::uint32_t _LocaleId;
		bool _IsReadOnly;
	};

	template<Concepts::Character C>
	Elysium::Core::Template::Globalization::NumberFormatInfo<C>::NumberFormatInfo(const System::uint32_t LocaleId, const bool ReadOnly) noexcept
		: _LocaleId(LocaleId), _IsReadOnly(ReadOnly)
	{ }

	template<Concepts::Character C>
	Elysium::Core::Template::Globalization::NumberFormatInfo<C>::NumberFormatInfo(const NumberFormatInfo& Source) noexcept
		: _LocaleId(Source._LocaleId), _IsReadOnly(Source._IsReadOnly)
	{ }

	template<Concepts::Character C>
	Elysium::Core::Template::Globalization::NumberFormatInfo<C>::NumberFormatInfo(NumberFormatInfo && Right) noexcept
		: _LocaleId(0), _IsReadOnly(false)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	template<Concepts::Character C>
	Elysium::Core::Template::Globalization::NumberFormatInfo<C>::~NumberFormatInfo() noexcept
	{ }

	template<Concepts::Character C>
	Elysium::Core::Template::Globalization::NumberFormatInfo<C>& Elysium::Core::Template::Globalization::NumberFormatInfo<C>::operator=(const NumberFormatInfo& Source) noexcept
	{
		if (this != &Source)
		{
			_LocaleId = Source._LocaleId;
			_IsReadOnly = Source._IsReadOnly;
		}
		return *this;
	}

	template<Concepts::Character C>
	Elysium::Core::Template::Globalization::NumberFormatInfo<C>& Elysium::Core::Template::Globalization::NumberFormatInfo<C>::operator=(NumberFormatInfo&& Right) noexcept
	{
		if (this != &Right)
		{
			_LocaleId = Elysium::Core::Template::Functional::Move(Right._LocaleId);
			_IsReadOnly = Elysium::Core::Template::Functional::Move(Right._IsReadOnly);

			Right._LocaleId = 0;
			Right._IsReadOnly = false;
		}
		return *this;
	}

	template<Concepts::Character C>
	constexpr const Elysium::Core::Template::Globalization::NumberFormatInfo<C> Elysium::Core::Template::Globalization::NumberFormatInfo<C>::GetCurrentInfo()
	{
		return NumberFormatInfo<C>(LOCALE_CUSTOM_DEFAULT, true);
	}

	template<Concepts::Character C>
	constexpr const Elysium::Core::Template::Globalization::NumberFormatInfo<C> Elysium::Core::Template::Globalization::NumberFormatInfo<C>::GetInvariantInfo()
	{
		return NumberFormatInfo<C>(LOCALE_INVARIANT, true);
	}

	template<Concepts::Character C>
	inline const bool NumberFormatInfo<C>::GetIsReadOnly() const
	{
		return _IsReadOnly;
	}

	template<Concepts::Character C>
	inline const System::uint32_t NumberFormatInfo<C>::GetCurrencyDecimalDigits() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t Result = -1;
		if (GetLocaleInfoW(_LocaleId, LOCALE_ICURRDIGITS | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
		{
			throw SystemException();
		}

		return Result;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetCurrencyDecimalSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SMONDECIMALSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetCurrencyDecimalSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SMONDECIMALSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetCurrencyDecimalSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SMONDECIMALSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetCurrencyGroupSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SMONTHOUSANDSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetCurrencyGroupSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SMONTHOUSANDSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetCurrencyGroupSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SMONTHOUSANDSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const System::uint32_t NumberFormatInfo<C>::GetCurrencyNegativePattern() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t Result = -1;
		if (GetLocaleInfoW(_LocaleId, LOCALE_INEGCURR | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
		{
			throw SystemException();
		}

		return Result;
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const System::uint32_t NumberFormatInfo<C>::GetCurrencyPositivePattern() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t Result = -1;
		if (GetLocaleInfoW(_LocaleId, LOCALE_ICURRENCY | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
		{
			throw SystemException();
		}

		return Result;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetCurrencySymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SCURRENCY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetCurrencySymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SCURRENCY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetCurrencySymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SCURRENCY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const DigitShapes NumberFormatInfo<C>::GetDigitSubstitution() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t Result = -1;
		if (GetLocaleInfoW(_LocaleId, LOCALE_IDIGITSUBSTITUTION | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
		{
			throw SystemException();
		}

		return static_cast<DigitShapes>(Result);
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNaNSymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNAN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNaNSymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNAN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNaNSymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNAN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNegativeInfinitySymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNEGINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNegativeInfinitySymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNEGINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNegativeInfinitySymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNEGINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNegativeSign() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNEGATIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNegativeSign() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNEGATIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNegativeSign() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNEGATIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const System::uint32_t NumberFormatInfo<C>::GetNumberDecimalDigits() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t Result = -1;
		if (GetLocaleInfoW(_LocaleId, LOCALE_INEGNUMBER | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
		{
			throw SystemException();
		}

		return Result;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNumberDecimalSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNumberDecimalSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNumberDecimalSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNumberGroupSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNumberGroupSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNumberGroupSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const System::uint32_t NumberFormatInfo<C>::GetPercentDecimalDigits() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t Result = -1;
		if (GetLocaleInfoW(_LocaleId, LOCALE_IDIGITS | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
		{
			throw SystemException();
		}

		return Result;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPercentDecimalSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPercentDecimalSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPercentDecimalSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPercentGroupSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_STHOUSAND, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPercentGroupSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPercentGroupSeparator() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const System::uint32_t NumberFormatInfo<C>::GetPercentNegativePattern() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t Result = -1;
		if (GetLocaleInfoW(_LocaleId, LOCALE_INEGATIVEPERCENT | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
		{
			throw SystemException();
		}

		return Result;
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const System::uint32_t NumberFormatInfo<C>::GetPercentPositivePattern() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		System::uint32_t Result = -1;
		if (GetLocaleInfoW(_LocaleId, LOCALE_IPOSITIVEPERCENT | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
		{
			throw SystemException();
		}

		return Result;
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPercentSymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SPERCENT, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPercentSymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPERCENT, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPercentSymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPERCENT, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPerMilleSymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SPERMILLE, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPerMilleSymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPERMILLE, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPerMilleSymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPERMILLE, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPositiveInfinitySymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SPOSINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPositiveInfinitySymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPOSINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPositiveInfinitySymbol() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPOSINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline const NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPositiveSign() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> Buffer = Text::String<char>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SPOSITIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Text::String<char>(Data, Text::CharacterTraits<char>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<>
	inline const NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPositiveSign() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPOSITIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Text::String<wchar_t>(Data, Text::CharacterTraits<wchar_t>::GetLength(Data));
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline const NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPositiveSign() const
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> Buffer = Text::String<wchar_t>(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPOSITIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
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
	inline void NumberFormatInfo<C>::SetCurrencyDecimalDigits(const System::uint32_t Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> StringValue = ToString(Value);
		if (SetLocaleInfoA(_LocaleId, LOCALE_ICURRDIGITS, &StringValue[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif

	}

	template<>
	inline void NumberFormatInfo<char>::SetCurrencyDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SMONDECIMALSEP, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetCurrencyDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SMONDECIMALSEP, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetCurrencyDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SMONDECIMALSEP, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetCurrencyGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SMONTHOUSANDSEP, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetCurrencyGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SMONTHOUSANDSEP, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetCurrencyGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SMONTHOUSANDSEP, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetCurrencyNegativePattern(const System::uint32_t Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> StringValue = ToString(Value);
		if (SetLocaleInfoA(_LocaleId, LOCALE_INEGCURR, &StringValue[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetCurrencyPositivePattern(const System::uint32_t Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> StringValue = ToString(Value);
		if (SetLocaleInfoA(_LocaleId, LOCALE_ICURRENCY, &StringValue[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetCurrencySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SCURRENCY, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetCurrencySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SCURRENCY, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetCurrencySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SCURRENCY, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetDigitSubstitution(const DigitShapes Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = ToWideString(Value);
		if (SetLocaleInfoW(_LocaleId, LOCALE_IDIGITSUBSTITUTION, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetNaNSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SNAN, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetNaNSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SNAN, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetNaNSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SNAN, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetNegativeInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SNEGINFINITY, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetNegativeInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SNEGINFINITY, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetNegativeInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SNEGINFINITY, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetNegativeSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SNEGATIVESIGN, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetNegativeSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SNEGATIVESIGN, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetNegativeSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SNEGATIVESIGN, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetNumberDecimalDigits(const System::uint32_t Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> StringValue = ToString(Value);
		if (SetLocaleInfoA(_LocaleId, LOCALE_INEGNUMBER, &StringValue[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetNumberDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetNumberDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetNumberDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetNumberGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_STHOUSAND, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetNumberGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetNumberGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetPercentDecimalDigits(const System::uint32_t Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> StringValue = ToString(Value);
		if (SetLocaleInfoA(_LocaleId, LOCALE_IDIGITS, &StringValue[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetPercentDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetPercentDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetPercentDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetPercentGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_STHOUSAND, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetPercentGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetPercentGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetPercentNegativePattern(const System::uint32_t Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> StringValue = ToString(Value);
		if (SetLocaleInfoA(_LocaleId, LOCALE_INEGATIVEPERCENT, &StringValue[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetPercentPositivePattern(const System::uint32_t Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<char> StringValue = ToString(Value);
		if (SetLocaleInfoA(_LocaleId, LOCALE_IPOSITIVEPERCENT, &StringValue[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetPercentSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SPERCENT, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetPercentSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPERCENT, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetPercentSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPERCENT, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetPerMilleSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SPERMILLE, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetPerMilleSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPERMILLE, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetPerMilleSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPERMILLE, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetPositiveInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SPOSINFINITY, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetPositiveInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPOSINFINITY, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetPositiveInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPOSINFINITY, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<char>::SetPositiveSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoA(_LocaleId, LOCALE_SPOSITIVESIGN, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<>
	inline void NumberFormatInfo<wchar_t>::SetPositiveSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPOSITIVESIGN, Value) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline void NumberFormatInfo<C>::SetPositiveSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw InvalidOperationException();
		}

#if defined ELYSIUM_CORE_OS_WINDOWS
		Text::String<wchar_t> WideString = Text::Unicode::Utf16::SafeToWideString(Value, Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPOSITIVESIGN, &WideString[0]) == 0)
		{
			throw SystemException();
		}
#else
#error "undefined os"
#endif
	}

	template<Concepts::Character C>
	inline Text::String<char> NumberFormatInfo<C>::ToString(System::uint32_t Value)
	{
		const System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(floor(log(Value) / log(10)) + 1_ui8);
		Text::String<char> Result = Text::String<char>(RequiredNumberOfCharacters);

		System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(Math::Power(10,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + Text::CharacterTraits<C>::ZeroCharacter;
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + Text::CharacterTraits<C>::UpperACharacter;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
}
#endif
