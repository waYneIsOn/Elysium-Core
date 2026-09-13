/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_NUMBERFORMATINFO_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_NUMBERFORMATINFO_WINDOWS

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

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDOPERATIONEXCEPTION
#include "../Exceptions/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../Exceptions/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_DIGITSHAPES
#include "DigitShapes.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_FLOOR
#include "../Math/Floor.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_LOGARITHM
#include "../Math/Logarithm.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_POWER
#include "../Math/Power.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Text/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Text/Unicode/Utf16.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Text/String.hpp"
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace Elysium::Core::Template::Globalization
{
	template <Concepts::Character C>
	class NumberFormatInfo
	{
	public:
		using ConstCharacterPointer = const C*;

		using CorrespondingString = Elysium::Core::Template::Text::String<C>;
	public:
		inline constexpr NumberFormatInfo(const Elysium::Core::Template::System::uint32_t LocaleId, const bool ReadOnly) noexcept
			: _LocaleId(LocaleId), _IsReadOnly(ReadOnly)
		{ }

		inline constexpr NumberFormatInfo(const NumberFormatInfo& Source) noexcept
			: _LocaleId(Source._LocaleId), _IsReadOnly(Source._IsReadOnly)
		{ }

		inline constexpr NumberFormatInfo(NumberFormatInfo&& Right) noexcept
			: _LocaleId(0), _IsReadOnly(false)
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~NumberFormatInfo() noexcept = default;
	public:
		inline constexpr NumberFormatInfo<C>& operator=(const NumberFormatInfo& Source) noexcept
		{
			if (this != &Source)
			{
				_LocaleId = Source._LocaleId;
				_IsReadOnly = Source._IsReadOnly;
			}
			return *this;
		}

		inline constexpr NumberFormatInfo<C>& operator=(NumberFormatInfo&& Right) noexcept
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
	public:
		inline static constexpr const NumberFormatInfo GetCurrentInfo()
		{
			return NumberFormatInfo<C>(LOCALE_CUSTOM_DEFAULT, true);
		}

		inline static constexpr const NumberFormatInfo GetInvariantInfo()
		{
			return NumberFormatInfo<C>(LOCALE_INVARIANT, true);
		}
	public:
		inline constexpr const bool GetIsReadOnly() const
		{
			return _IsReadOnly;
		}
	public:
		inline const Elysium::Core::Template::System::uint32_t GetCurrencyDecimalDigits() const
		{
			Elysium::Core::Template::System::uint32_t Result = -1;
			if (GetLocaleInfoW(_LocaleId, LOCALE_ICURRDIGITS | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Result;
		}

		inline const Elysium::Core::Template::System::uint32_t GetCurrencyNegativePattern() const
		{
			Elysium::Core::Template::System::uint32_t Result = -1;
			if (GetLocaleInfoW(_LocaleId, LOCALE_INEGCURR | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Result;
		}

		inline const Elysium::Core::Template::System::uint32_t GetCurrencyPositivePattern() const
		{
			Elysium::Core::Template::System::uint32_t Result = -1;
			if (GetLocaleInfoW(_LocaleId, LOCALE_ICURRENCY | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Result;
		}

		inline const Elysium::Core::Template::System::uint32_t GetNumberDecimalDigits() const
		{
			Elysium::Core::Template::System::uint32_t Result = -1;
			if (GetLocaleInfoW(_LocaleId, LOCALE_INEGNUMBER | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Result;
		}

		inline const Elysium::Core::Template::System::uint32_t GetPercentDecimalDigits() const
		{
			Elysium::Core::Template::System::uint32_t Result = -1;
			if (GetLocaleInfoW(_LocaleId, LOCALE_IDIGITS | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Result;
		}

		inline const Elysium::Core::Template::System::uint32_t GetPercentNegativePattern() const
		{
			Elysium::Core::Template::System::uint32_t Result = -1;
			if (GetLocaleInfoW(_LocaleId, LOCALE_INEGATIVEPERCENT | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Result;
		}

		inline const Elysium::Core::Template::System::uint32_t GetPercentPositivePattern() const
		{
			Elysium::Core::Template::System::uint32_t Result = -1;
			if (GetLocaleInfoW(_LocaleId, LOCALE_IPOSITIVEPERCENT | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Result;
		}

		inline const DigitShapes GetDigitSubstitution() const
		{
			Elysium::Core::Template::System::uint32_t Result = -1;
			if (GetLocaleInfoW(_LocaleId, LOCALE_IDIGITSUBSTITUTION | LOCALE_RETURN_NUMBER, (LPWSTR)&Result, sizeof(Result)) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return static_cast<DigitShapes>(Result);
		}

		const CorrespondingString GetCurrencyDecimalSeparator() const;

		const CorrespondingString GetCurrencyGroupSeparator() const;

		const CorrespondingString GetCurrencySymbol() const;

		const CorrespondingString GetNaNSymbol() const;

		const CorrespondingString GetNegativeInfinitySymbol() const;

		const CorrespondingString GetNegativeSign() const;

		const CorrespondingString GetNumberDecimalSeparator() const;

		const CorrespondingString GetNumberGroupSeparator() const;

		const CorrespondingString GetPercentDecimalSeparator() const;

		const CorrespondingString GetPercentGroupSeparator() const;

		const CorrespondingString GetPercentSymbol() const;

		const CorrespondingString GetPerMilleSymbol() const;

		const CorrespondingString GetPositiveInfinitySymbol() const;

		const CorrespondingString GetPositiveSign() const;
	public:
		inline void SetCurrencyDecimalDigits(const Elysium::Core::Template::System::uint32_t Value)
		{
			if (_IsReadOnly)
			{
				throw Elysium::Core::Template::Exceptions::InvalidOperationException();
			}

			Elysium::Core::Template::Text::String<char> StringValue = ToString(Value);
			if (SetLocaleInfoA(_LocaleId, LOCALE_ICURRDIGITS, &StringValue[0]) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}

		inline void SetCurrencyNegativePattern(const Elysium::Core::Template::System::uint32_t Value)
		{
			if (_IsReadOnly)
			{
				throw Elysium::Core::Template::Exceptions::InvalidOperationException();
			}

			Elysium::Core::Template::Text::String<char> StringValue = ToString(Value);
			if (SetLocaleInfoA(_LocaleId, LOCALE_INEGCURR, &StringValue[0]) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}

		inline void SetCurrencyPositivePattern(const Elysium::Core::Template::System::uint32_t Value)
		{
			if (_IsReadOnly)
			{
				throw Exceptions::InvalidOperationException();
			}

			Elysium::Core::Template::Text::String<char> StringValue = ToString(Value);
			if (SetLocaleInfoA(_LocaleId, LOCALE_ICURRENCY, &StringValue[0]) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}

		inline void SetNumberDecimalDigits(const Elysium::Core::Template::System::uint32_t Value)
		{
			if (_IsReadOnly)
			{
				throw Elysium::Core::Template::Exceptions::InvalidOperationException();
			}

			Elysium::Core::Template::Text::String<char> StringValue = ToString(Value);
			if (SetLocaleInfoA(_LocaleId, LOCALE_INEGNUMBER, &StringValue[0]) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}

		inline void SetPercentDecimalDigits(const Elysium::Core::Template::System::uint32_t Value)
		{
			if (_IsReadOnly)
			{
				throw Elysium::Core::Template::Exceptions::InvalidOperationException();
			}

			Elysium::Core::Template::Text::String<char> StringValue = ToString(Value);
			if (SetLocaleInfoA(_LocaleId, LOCALE_IDIGITS, &StringValue[0]) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}

		inline void SetPercentNegativePattern(const Elysium::Core::Template::System::uint32_t Value)
		{
			if (_IsReadOnly)
			{
				throw Elysium::Core::Template::Exceptions::InvalidOperationException();
			}

			Elysium::Core::Template::Text::String<char> StringValue = ToString(Value);
			if (SetLocaleInfoA(_LocaleId, LOCALE_INEGATIVEPERCENT, &StringValue[0]) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}

		inline void SetPercentPositivePattern(const Elysium::Core::Template::System::uint32_t Value)
		{
			if (_IsReadOnly)
			{
				throw Elysium::Core::Template::Exceptions::InvalidOperationException();
			}

			Elysium::Core::Template::Text::String<char> StringValue = ToString(Value);
			if (SetLocaleInfoA(_LocaleId, LOCALE_IPOSITIVEPERCENT, &StringValue[0]) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}

		inline void SetDigitSubstitution(const DigitShapes Value)
		{
			if (_IsReadOnly)
			{
				throw Elysium::Core::Template::Exceptions::InvalidOperationException();
			}

			Elysium::Core::Template::Text::String<char> StringValue = ToString(static_cast<Elysium::Core::Template::System::uint32_t>(Value));
			if (SetLocaleInfoA(_LocaleId, LOCALE_IDIGITSUBSTITUTION, &StringValue[0]) == 0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}

		void SetCurrencyDecimalSeparator(const ConstCharacterPointer Value);

		void SetCurrencyGroupSeparator(const ConstCharacterPointer Value);

		void SetCurrencySymbol(const ConstCharacterPointer Value);

		void SetNaNSymbol(const ConstCharacterPointer Value);

		void SetNegativeInfinitySymbol(const ConstCharacterPointer Value);

		void SetNegativeSign(const ConstCharacterPointer Value);

		void SetNumberDecimalSeparator(const ConstCharacterPointer Value);

		void SetNumberGroupSeparator(const ConstCharacterPointer Value);

		void SetPercentDecimalSeparator(const ConstCharacterPointer Value);

		void SetPercentGroupSeparator(const ConstCharacterPointer Value);

		void SetPercentSymbol(const ConstCharacterPointer Value);

		void SetPerMilleSymbol(const ConstCharacterPointer Value);

		void SetPositiveInfinitySymbol(const ConstCharacterPointer Value);

		void SetPositiveSign(const ConstCharacterPointer Value);
	private:
		Elysium::Core::Template::Text::String<char> ToString(Elysium::Core::Template::System::uint32_t Value);
	private:
		Elysium::Core::Template::System::uint32_t _LocaleId;
		bool _IsReadOnly;
	};

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetCurrencyDecimalSeparator() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SMONDECIMALSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetCurrencyDecimalSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SMONDECIMALSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetCurrencyDecimalSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SMONDECIMALSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetCurrencyGroupSeparator() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SMONTHOUSANDSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetCurrencyGroupSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SMONTHOUSANDSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetCurrencyGroupSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SMONTHOUSANDSEP, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetCurrencySymbol() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SCURRENCY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetCurrencySymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SCURRENCY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetCurrencySymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SCURRENCY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNaNSymbol() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNAN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNaNSymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNAN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNaNSymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNAN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNegativeInfinitySymbol() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNEGINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNegativeInfinitySymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNEGINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNegativeInfinitySymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNEGINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNegativeSign() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SNEGATIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNegativeSign() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNEGATIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNegativeSign() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SNEGATIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNumberDecimalSeparator() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNumberDecimalSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNumberDecimalSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetNumberGroupSeparator() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetNumberGroupSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetNumberGroupSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPercentDecimalSeparator() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPercentDecimalSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPercentDecimalSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPercentGroupSeparator() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_STHOUSAND, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPercentGroupSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPercentGroupSeparator() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPercentSymbol() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SPERCENT, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPercentSymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPERCENT, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPercentSymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPERCENT, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPerMilleSymbol() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SPERMILLE, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPerMilleSymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPERMILLE, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPerMilleSymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPERMILLE, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPositiveInfinitySymbol() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SPOSINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPositiveInfinitySymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPOSINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPositiveInfinitySymbol() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPOSINFINITY, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<char>::CorrespondingString NumberFormatInfo<char>::GetPositiveSign() const
	{
		Elysium::Core::Template::Text::String<char> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoA(_LocaleId, LOCALE_SPOSITIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		char* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<char>(Data, Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Data));
	}

	template<>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::CorrespondingString NumberFormatInfo<wchar_t>::GetPositiveSign() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPOSITIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I copy the string here
		wchar_t* Data = &Buffer[0];
		return Elysium::Core::Template::Text::String<wchar_t>(Data, Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Data));
	}

	template<Concepts::Character C>
	inline const Elysium::Core::Template::Globalization::NumberFormatInfo<C>::CorrespondingString NumberFormatInfo<C>::GetPositiveSign() const
	{
		Elysium::Core::Template::Text::String<wchar_t> Buffer(LOCALE_NAME_MAX_LENGTH);
		if (GetLocaleInfoW(_LocaleId, LOCALE_SPOSITIVESIGN, &Buffer[0], LOCALE_NAME_MAX_LENGTH) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		// in most cases the string will fit onto the stack which is why I get the actual length here
		return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<C>(&Buffer[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&Buffer[0]));
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetCurrencyDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SMONDECIMALSEP, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetCurrencyDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SMONDECIMALSEP, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetCurrencyDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString = 
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SMONDECIMALSEP, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetCurrencyGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SMONTHOUSANDSEP, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetCurrencyGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SMONTHOUSANDSEP, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetCurrencyGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString = 
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SMONTHOUSANDSEP, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetCurrencySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SCURRENCY, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetCurrencySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SCURRENCY, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetCurrencySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString = 
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SCURRENCY, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetNaNSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SNAN, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetNaNSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SNAN, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetNaNSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString = 
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SNAN, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetNegativeInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SNEGINFINITY, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetNegativeInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SNEGINFINITY, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetNegativeInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString = 
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SNEGINFINITY, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetNegativeSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SNEGATIVESIGN, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetNegativeSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SNEGATIVESIGN, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetNegativeSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString =
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SNEGATIVESIGN, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetNumberDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetNumberDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetNumberDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString = 
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetNumberGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_STHOUSAND, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetNumberGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetNumberGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString =
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetPercentDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SDECIMAL, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetPercentDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetPercentDecimalSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString =
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SDECIMAL, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetPercentGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_STHOUSAND, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetPercentGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetPercentGroupSeparator(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString =
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_STHOUSAND, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetPercentSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SPERCENT, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetPercentSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SPERCENT, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetPercentSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString =
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPERCENT, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetPerMilleSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SPERMILLE, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetPerMilleSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SPERMILLE, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetPerMilleSymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString =
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPERMILLE, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetPositiveInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SPOSINFINITY, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetPositiveInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SPOSINFINITY, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetPositiveInfinitySymbol(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString = 
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPOSINFINITY, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<char>::SetPositiveSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoA(_LocaleId, LOCALE_SPOSITIVESIGN, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>::SetPositiveSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		if (SetLocaleInfoW(_LocaleId, LOCALE_SPOSITIVESIGN, Value) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline void Elysium::Core::Template::Globalization::NumberFormatInfo<C>::SetPositiveSign(const ConstCharacterPointer Value)
	{
		if (_IsReadOnly)
		{
			throw Elysium::Core::Template::Exceptions::InvalidOperationException();
		}

		Elysium::Core::Template::Text::String<wchar_t> WideString = 
			Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(Value, Elysium::Core::Template::Text::CharacterTraits<C>::GetLength(Value));
		if (SetLocaleInfoW(_LocaleId, LOCALE_SPOSITIVESIGN, &WideString[0]) == 0)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}
	}

	template<Concepts::Character C>
	inline Text::String<char> NumberFormatInfo<C>::ToString(System::uint32_t Value)
	{
		const Elysium::Core::Template::System::uint8_t RequiredNumberOfCharacters =
			static_cast<Elysium::Core::Template::System::uint8_t>(Elysium::Core::Template::Math::Logarithm(Value) / Elysium::Core::Template::Math::Logarithm(10) + 1_ui8);
		Elysium::Core::Template::Text::String<char> Result(RequiredNumberOfCharacters);

		Elysium::Core::Template::System::uint8_t Index = 0;
		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::Template::System::int16_t BaseValue = static_cast<Elysium::Core::Template::System::int16_t>(Math::Power(10,
				static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::Template::System::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + Elysium::Core::Template::Text::CharacterTraits<C>::ZeroCharacter;
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + Elysium::Core::Template::Text::CharacterTraits<C>::UpperACharacter;
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
}
#endif
#endif
