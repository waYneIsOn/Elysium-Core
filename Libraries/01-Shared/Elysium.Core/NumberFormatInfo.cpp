#include "NumberFormatInfo.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
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

Elysium::Core::Globalization::NumberFormatInfo::NumberFormatInfo()
	: NumberFormatInfo(LOCALE_INVARIANT, false)
{ }
Elysium::Core::Globalization::NumberFormatInfo::NumberFormatInfo(const Elysium::Core::int32_t Culture, const bool ReadOnly)
	: _LCID(Culture), _IsReadOnly(ReadOnly)
{ }
Elysium::Core::Globalization::NumberFormatInfo::NumberFormatInfo(const NumberFormatInfo & Source)
	: _LCID(Source._LCID), _IsReadOnly(Source._IsReadOnly)
{ }
Elysium::Core::Globalization::NumberFormatInfo::NumberFormatInfo(NumberFormatInfo&& Right) noexcept
	: _LCID(LOCALE_INVARIANT), _IsReadOnly(false)
{
	*this = std::move(Right);
}
Elysium::Core::Globalization::NumberFormatInfo::~NumberFormatInfo()
{ }

Elysium::Core::Globalization::NumberFormatInfo& Elysium::Core::Globalization::NumberFormatInfo::operator=(const NumberFormatInfo & Source)
{
	if (this != &Source)
	{
		_LCID = Source._LCID;
		_IsReadOnly = Source._IsReadOnly;
	}
	return *this;
}

Elysium::Core::Globalization::NumberFormatInfo& Elysium::Core::Globalization::NumberFormatInfo::operator=(NumberFormatInfo&& Right) noexcept
{
	if (this != &Right)
	{
		_LCID = std::move(Right._LCID);
		_IsReadOnly = std::move(Right._IsReadOnly);
	}
	return *this;
}

const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyDecimalDigits() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	Elysium::Core::int32_t Value = 48;
	if (GetLocaleInfo((LCID)_LCID, LOCALE_ICURRDIGITS, (LPWSTR)&Value, sizeof(Value) / sizeof(wchar_t)) == 0)
	{
		throw SystemException();
	}
	
	return Value - 48;
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyDecimalSeparator() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyGroupSeparator() const
{
	throw 1;
}

const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyNegativePattern() const
{
	throw 1;
}

const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyPositivePattern() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetCurrencySymbol() const
{
	throw 1;
}

const Elysium::Core::Globalization::DigitShapes Elysium::Core::Globalization::NumberFormatInfo::GetDigitSubstitution() const
{
	throw 1;
}

const bool Elysium::Core::Globalization::NumberFormatInfo::GetIsReadOnly() const
{
	return _IsReadOnly;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetNaNSymbol() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetNegativeInfinitySymbol() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetNegativeSign() const
{
	throw 1;
}

const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetNumberDecimalDigits() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetNumberDecimalSeparator() const
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	wchar_t Value[LOCALE_NAME_MAX_LENGTH];
	if (GetLocaleInfo((LCID)_LCID, LOCALE_SDECIMAL, (LPWSTR)&Value[0], LOCALE_NAME_MAX_LENGTH) == 0)
	{
		throw SystemException();
	}

	return Elysium::Core::Text::Encoding::UTF16LE().GetString((Elysium::Core::byte*)Value, std::char_traits<wchar_t>::length(Value) * sizeof(wchar_t));
#else
#error "undefined os"
#endif
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetNumberGroupSeparator() const
{
	throw 1;
}

const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetPercentDecimalDigits() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetPercentDecimalSeparator() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetPercentGroupSeparator() const
{
	throw 1;
}

const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetPercentNegativePattern() const
{
	throw 1;
}

const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetPercentPositivePattern() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetPercentSymbol() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetPerMilleSymbol() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetPositiveInfinitySymbol() const
{
	throw 1;
}

const Elysium::Core::String Elysium::Core::Globalization::NumberFormatInfo::GetPositiveSign() const
{
	throw 1;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyDecimalDigits(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_CurrencyDecimalDigits = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyDecimalSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_CurrencyDecimalSeparator = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyGroupSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_CurrencyGroupSeparator = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyNegativePattern(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_CurrencyNegativePattern = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyPositivePattern(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_CurrencyPositivePattern = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencySymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_CurrencySymbol = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetDigitSubstitution(const DigitShapes Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_DigitSubstitution = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetNaNSymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_NaNSymbol = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetNegativeInfinitySymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_NegativeInfinitySymbol = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetNegativeSign(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_NegativeSign = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetNumberDecimalDigits(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_NumberDecimalDigits = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetNumberDecimalSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_NumberDecimalSeparator = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetNumberGroupSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_NumberGroupSeparator = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetPercentDecimalDigits(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_PercentDecimalDigits = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetPercentDecimalSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_PercentDecimalSeparator = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetPercentGroupSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_PercentGroupSeparator = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetPercentNegativePattern(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_PercentNegativePattern = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetPercentPositivePattern(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_PercentPositivePattern = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetPercentSymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_PercentSymbol = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetPerMilleSymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_PerMilleSymbol = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetPositiveInfinitySymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_PositiveInfinitySymbol = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetPositiveSign(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	//_PositiveSign = Value;
}
