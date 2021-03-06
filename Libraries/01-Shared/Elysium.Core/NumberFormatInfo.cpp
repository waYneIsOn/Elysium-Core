#include "NumberFormatInfo.hpp"

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
#endif

Elysium::Core::Globalization::NumberFormatInfo Elysium::Core::Globalization::NumberFormatInfo::_InvariantInfo = Elysium::Core::Globalization::NumberFormatInfo();

Elysium::Core::Globalization::NumberFormatInfo::NumberFormatInfo()
	: _CurrencyDecimalDigits(2), _CurrencyDecimalSeparator(u8"."), _CurrencyGroupSeparator(u8","), _CurrencyNegativePattern(0),
	_CurrencyPositivePattern(0), _CurrencySymbol(u8"�"), _DigitSubstitution(DigitShapes::None), _IsReadOnly(false), _NaNSymbol(u8"NaN"),
	_NegativeInfinitySymbol(u8"-Infinity"), _NegativeSign(u8"-"), _NumberDecimalDigits(2), _NumberDecimalSeparator(u8"."), _NumberGroupSeparator(u8","),
	_PercentDecimalDigits(2), _PercentDecimalSeparator(u8"."), _PercentGroupSeparator(u8","),_PercentNegativePattern(0),
	_PercentPositivePattern(0), _PercentSymbol(u8"%"), _PerMilleSymbol(u8"�"), _PositiveInfinitySymbol(u8"Infinity"), _PositiveSign(u8"+")
{ }
Elysium::Core::Globalization::NumberFormatInfo::~NumberFormatInfo()
{ }

const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyDecimalDigits() const
{
	return _CurrencyDecimalDigits;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyDecimalSeparator() const
{
	return _CurrencyDecimalSeparator;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyGroupSeparator() const
{
	return _CurrencyGroupSeparator;
}
const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyNegativePattern() const
{
	return _CurrencyNegativePattern;
}
const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetCurrencyPositivePattern() const
{
	return _CurrencyPositivePattern;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetCurrencySymbol() const
{
	return _CurrencySymbol;
}
const Elysium::Core::Globalization::DigitShapes Elysium::Core::Globalization::NumberFormatInfo::GetDigitSubstitution() const
{
	return _DigitSubstitution;
}
const bool Elysium::Core::Globalization::NumberFormatInfo::GetIsReadOnly() const
{
	return _IsReadOnly;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetNaNSymbol() const
{
	return _NaNSymbol;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetNegativeInfinitySymbol() const
{
	return _NegativeInfinitySymbol;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetNegativeSign() const
{
	return _NegativeSign;
}
const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetNumberDecimalDigits() const
{
	return _NumberDecimalDigits;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetNumberDecimalSeparator() const
{
	return _NumberDecimalSeparator;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetNumberGroupSeparator() const
{
	return _NumberGroupSeparator;
}
const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetPercentDecimalDigits() const
{
	return _PercentDecimalDigits;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetPercentDecimalSeparator() const
{
	return _PercentDecimalSeparator;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetPercentGroupSeparator() const
{
	return _PercentGroupSeparator;
}
const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetPercentNegativePattern() const
{
	return _PercentNegativePattern;
}
const Elysium::Core::int32_t Elysium::Core::Globalization::NumberFormatInfo::GetPercentPositivePattern() const
{
	return _PercentPositivePattern;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetPercentSymbol() const
{
	return _PercentSymbol;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetPerMilleSymbol() const
{
	return _PerMilleSymbol;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetPositiveInfinitySymbol() const
{
	return _PositiveInfinitySymbol;
}
const Elysium::Core::String & Elysium::Core::Globalization::NumberFormatInfo::GetPositiveSign() const
{
	return _PositiveSign;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyDecimalDigits(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_CurrencyDecimalDigits = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyDecimalSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_CurrencyDecimalSeparator = Value;
}

void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyGroupSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_CurrencyGroupSeparator = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyNegativePattern(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_CurrencyNegativePattern = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencyPositivePattern(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_CurrencyPositivePattern = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetCurrencySymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_CurrencySymbol = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetDigitSubstitution(const DigitShapes Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_DigitSubstitution = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetNaNSymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_NaNSymbol = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetNegativeInfinitySymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_NegativeInfinitySymbol = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetNegativeSign(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_NegativeSign = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetNumberDecimalDigits(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_NumberDecimalDigits = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetNumberDecimalSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_NumberDecimalSeparator = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetNumberGroupSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_NumberGroupSeparator = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetPercentDecimalDigits(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_PercentDecimalDigits = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetPercentDecimalSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_PercentDecimalSeparator = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetPercentGroupSeparator(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_PercentGroupSeparator = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetPercentNegativePattern(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_PercentNegativePattern = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetPercentPositivePattern(const Elysium::Core::int32_t Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_PercentPositivePattern = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetPercentSymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_PercentSymbol = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetPerMilleSymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_PerMilleSymbol = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetPositiveInfinitySymbol(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_PositiveInfinitySymbol = Value;
}
void Elysium::Core::Globalization::NumberFormatInfo::SetPositiveSign(const String & Value)
{
	if (_IsReadOnly)
	{
		throw InvalidOperationException();
	}
	_PositiveSign = Value;
}

const Elysium::Core::Globalization::NumberFormatInfo & Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo()
{
	return _InvariantInfo;
}
