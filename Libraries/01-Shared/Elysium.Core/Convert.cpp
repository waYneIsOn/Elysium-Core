#include "Convert.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICLIMITS
#include "../Elysium.Core.Template/NumericLimits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

#ifndef _STRING_
#include <string>
#endif

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(Elysium::Core::int8_t Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	Elysium::Core::uint8_t RequiredNumberOfCharacters = 0;
	Elysium::Core::uint8_t Index = 0;
	if (Value < 0)
	{
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const Elysium::Core::uint8_t NegativeSignLength = static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength());
		Value *= -1;

		RequiredNumberOfCharacters += NegativeSignLength + static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase))) + 1_ui8;
		Index += NegativeSignLength;
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);
		for (Elysium::Core::size i = 0; i < NegativeSignLength; i++)
		{
			Result[i] = NegativeSign[i];
		}

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
	else
	{
		RequiredNumberOfCharacters += static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::int8_t Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::int8_t Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(Elysium::Core::int16_t Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	Elysium::Core::uint8_t RequiredNumberOfCharacters = 0;
	Elysium::Core::uint8_t Index = 0;
	if (Value < 0)
	{
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const Elysium::Core::uint8_t NegativeSignLength = static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength());
		Value *= -1;

		RequiredNumberOfCharacters += NegativeSignLength + static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase))) + 1_ui8;
		Index += NegativeSignLength;
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);
		for (Elysium::Core::size i = 0; i < NegativeSignLength; i++)
		{
			Result[i] = NegativeSign[i];
		}

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
	else
	{
		RequiredNumberOfCharacters += static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::int16_t Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::int16_t Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(Elysium::Core::int32_t Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	Elysium::Core::uint8_t RequiredNumberOfCharacters = 0;
	Elysium::Core::uint8_t Index = 0;
	if (Value < 0)
	{
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const Elysium::Core::uint8_t NegativeSignLength = static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength());
		Value *= -1;

		RequiredNumberOfCharacters += NegativeSignLength + static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase))) + 1_ui8;
		Index += NegativeSignLength;
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);
		for (Elysium::Core::size i = 0; i < NegativeSignLength; i++)
		{
			Result[i] = NegativeSign[i];
		}

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
	else
	{
		RequiredNumberOfCharacters += static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::int32_t Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::int32_t Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(Elysium::Core::int64_t Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	Elysium::Core::uint8_t RequiredNumberOfCharacters = 0;
	Elysium::Core::uint8_t Index = 0;
	if (Value < 0)
	{
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const Elysium::Core::uint8_t NegativeSignLength = static_cast<Elysium::Core::uint8_t>(NegativeSign.GetLength());
		Value *= -1;

		RequiredNumberOfCharacters += NegativeSignLength + static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase))) + 1_ui8;
		Index += NegativeSignLength;
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);
		for (Elysium::Core::size i = 0; i < NegativeSignLength; i++)
		{
			Result[i] = NegativeSign[i];
		}

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
	else
	{
		RequiredNumberOfCharacters += static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::int64_t Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::int64_t Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(Elysium::Core::uint8_t Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	Elysium::Core::uint8_t RequiredNumberOfCharacters = 0;
	Elysium::Core::uint8_t Index = 0;
	RequiredNumberOfCharacters += static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
	Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);

	while (Index < RequiredNumberOfCharacters)
	{
		Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
		Elysium::Core::int16_t NumericalValue = Value / BaseValue;

		if (NumericalValue < 10)
		{
			Result[Index++] = NumericalValue + u8'0';
		}
		else
		{
			Result[Index++] = NumericalValue - 10 + u8'A';
		}

		Value -= BaseValue * NumericalValue;
	}

	return Result;
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::uint8_t Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::uint8_t Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(Elysium::Core::uint16_t Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	Elysium::Core::uint8_t RequiredNumberOfCharacters = 0;
	Elysium::Core::uint8_t Index = 0;
	RequiredNumberOfCharacters += static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
	Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);

	while (Index < RequiredNumberOfCharacters)
	{
		Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
		Elysium::Core::int16_t NumericalValue = Value / BaseValue;

		if (NumericalValue < 10)
		{
			Result[Index++] = NumericalValue + u8'0';
		}
		else
		{
			Result[Index++] = NumericalValue - 10 + u8'A';
		}

		Value -= BaseValue * NumericalValue;
	}

	return Result;
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::uint16_t Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::uint16_t Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(Elysium::Core::uint32_t Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	Elysium::Core::uint8_t RequiredNumberOfCharacters = 0;
	Elysium::Core::uint8_t Index = 0;
	RequiredNumberOfCharacters += static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
	Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);

	while (Index < RequiredNumberOfCharacters)
	{
		Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
		Elysium::Core::int16_t NumericalValue = Value / BaseValue;

		if (NumericalValue < 10)
		{
			Result[Index++] = NumericalValue + u8'0';
		}
		else
		{
			Result[Index++] = NumericalValue - 10 + u8'A';
		}

		Value -= BaseValue * NumericalValue;
	}

	return Result;
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::uint32_t Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::uint32_t Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(Elysium::Core::uint64_t Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	Elysium::Core::uint8_t RequiredNumberOfCharacters = 0;
	Elysium::Core::uint8_t Index = 0;
	RequiredNumberOfCharacters += static_cast<Elysium::Core::uint8_t>(floor(log(Value) / log(ToBase)) + 1_ui8);
	Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);

	while (Index < RequiredNumberOfCharacters)
	{
		Elysium::Core::int16_t BaseValue = static_cast<Elysium::Core::int16_t>(pow(ToBase, static_cast<double>(RequiredNumberOfCharacters) - Index - 1_ui8));
		Elysium::Core::int16_t NumericalValue = Value / BaseValue;

		if (NumericalValue < 10)
		{
			Result[Index++] = NumericalValue + u8'0';
		}
		else
		{
			Result[Index++] = NumericalValue - 10 + u8'A';
		}

		Value -= BaseValue * NumericalValue;
	}

	return Result;
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::uint64_t Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::uint64_t Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const float Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	// ToDo: Encoding::Unicode()
	std::string StringValue = std::to_string(Value);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)StringValue.c_str(), StringValue.length());
	/*
	// ToDo: Encoding::Unicode()
	std::string StringValue = std::to_string(Value);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)StringValue.c_str(), StringValue.length());
	/*
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	Elysium::Core::uint8_t RequiredNumberOfCharacters = 0;
	Elysium::Core::uint8_t Index = 0;
	if (Value < 0)
	{
		const Elysium::Core::Utf8String NegativeSign = FormatInfo.GetNegativeSign();
		const Elysium::Core::size NegativeSignLength = NegativeSign.GetLength();
		Value *= -1;

		//FormatInfo.GetPercentDecimalSeparator();
		//FormatInfo.GetPercentDecimalDigits();

		RequiredNumberOfCharacters += NegativeSignLength + floor(log(Value) / log(ToBase)) + 1;
		Index += NegativeSignLength;
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);
		for (Elysium::Core::size i = 0; i < NegativeSignLength; i++)
		{
			Result[i] = NegativeSign[i];
		}

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = pow(ToBase, RequiredNumberOfCharacters - Index - 1);
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
	else
	{
		RequiredNumberOfCharacters += floor(log(Value) / log(ToBase)) + 1;
		Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredNumberOfCharacters);

		while (Index < RequiredNumberOfCharacters)
		{
			Elysium::Core::int16_t BaseValue = pow(ToBase, RequiredNumberOfCharacters - Index - 1);
			Elysium::Core::int16_t NumericalValue = Value / BaseValue;

			if (NumericalValue < 10)
			{
				Result[Index++] = NumericalValue + u8'0';
			}
			else
			{
				Result[Index++] = NumericalValue - 10 + u8'A';
			}

			Value -= BaseValue * NumericalValue;
		}

		return Result;
	}
	*/
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const float Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const float Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const double Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}
	
	// ToDo: Encoding::Unicode()
	std::string StringValue = std::to_string(Value);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)StringValue.c_str(), StringValue.length());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const double Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const double Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::Decimal Value, const Elysium::Core::uint8_t ToBase, const Elysium::Core::Globalization::NumberFormatInfo& FormatInfo)
{
	if (ToBase != 2 && ToBase != 8 && ToBase != 10 && ToBase != 16)
	{
		throw Elysium::Core::ArgumentException(u8"ToBase");
	}

	if (Value == 0)
	{
		return Elysium::Core::Utf8String(u8"0");
	}

	throw 1;
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::Decimal Value, const Elysium::Core::uint8_t ToBase)
{
	return ToString(Value, ToBase, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

const Elysium::Core::Utf8String Elysium::Core::Convert::ToString(const Elysium::Core::Decimal Value)
{
	return ToString(Value, 10, Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo());
}

Elysium::Core::Container::VectorOfByte Elysium::Core::Convert::FromBase64String(const Elysium::Core::Utf8String& Base64String)
{	// https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp
	/*
	base64.cpp and base64.h

	Copyright (C) 2004-2008 René Nyffenegger

	This source code is provided 'as-is', without any express or implied
	warranty. In no event will the author be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this source code must not be misrepresented; you must not
		claim that you wrote the original source code. If you use this source code
		in a product, an acknowledgment in the product documentation would be
		appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original source code.

	3. This notice may not be removed or altered from any source distribution.

	René Nyffenegger rene.nyffenegger@adp-gmbh.ch
	*/
	Elysium::Core::Container::VectorOfByte Result;
	Elysium::Core::size InputLength = Base64String.GetLength();
	int i = 0;
	int j = 0;
	int Index = 0;
	byte Array4[4];
	byte Array3[3];

	while (InputLength-- && (Base64String[Index] != u8'=' && IsBase64(Base64String[Index])))
	{
		Array4[i++] = Base64String[Index];
		Index++;

		if (i == 4)
		{
			for (i = 0; i < 4; i++)
			{
				Array4[i] = static_cast<Elysium::Core::byte>(_Base64Chars.IndexOf(Array4[i]));
			}

			Array3[0] = (Array4[0] << 2) + ((Array4[1] & 0x30) >> 4);
			Array3[1] = ((Array4[1] & 0xF) << 4) + ((Array4[2] & 0x3C) >> 2);
			Array3[2] = ((Array4[2] & 0x3) << 6) + Array4[3];

			Result.PushBackRange(&Array3[0], 3);
			i = 0;
		}
	}

	if (i)
	{
		for (j = 0; j < i; j++)
		{
			Array4[j] = static_cast<Elysium::Core::byte>(_Base64Chars.IndexOf(Array4[j]));
		}

		Array3[0] = (Array4[0] << 2) + ((Array4[1] & 0x30) >> 4);
		Array3[1] = ((Array4[1] << 0xF) << 4) + ((Array4[2] & 0x3C) >> 2);

		for (j = 0; j < i - 1; j++)
		{
			Result.PushBack(Array3[j]);
		}
	}

	return Result;
}

Elysium::Core::Utf8String Elysium::Core::Convert::ToBase64String(const Elysium::Core::byte * Bytes, const Elysium::Core::uint32_t Length)
{	// https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp
	/*
	base64.cpp and base64.h

	Copyright (C) 2004-2008 René Nyffenegger

	This source code is provided 'as-is', without any express or implied
	warranty. In no event will the author be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this source code must not be misrepresented; you must not
		claim that you wrote the original source code. If you use this source code
		in a product, an acknowledgment in the product documentation would be
		appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original source code.

	3. This notice may not be removed or altered from any source distribution.

	René Nyffenegger rene.nyffenegger@adp-gmbh.ch
	*/
	Elysium::Core::size in_len = Length;
	int c = 0;
	int i = 0;
	int j = 0;
	byte Array3[3];
	byte Array4[4];

	Elysium::Core::Container::VectorOfByte Result = Elysium::Core::Container::VectorOfByte();

	while (in_len--)
	{
		Array3[i++] = Bytes[c++];
		if (i == 3)
		{
			Array4[0] = (Array3[0] & 0xFC) >> 2;
			Array4[1] = ((Array3[0] & 0x03) << 4) + ((Array3[1] & 0xF0) >> 4);
			Array4[2] = ((Array3[1] & 0x0F) << 2) + ((Array3[2] & 0xC0) >> 6);
			Array4[3] = Array3[2] & 0x3F;

			for (i = 0; i < 4; i++)
			{
				Result.PushBack(_Base64Chars[Array4[i]]);
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
		{
			Array3[j] = u8'\0';
		}

		Array4[0] = (Array3[0] & 0xFC) >> 2;
		Array4[1] = ((Array3[0] & 0x03) << 4) + ((Array3[1] & 0xF0) >> 4);
		Array4[2] = ((Array3[1] & 0x0F) << 2) + ((Array3[2] & 0xC0) >> 6);
		Array4[3] = Array3[2] & 0x3F;

		for (j = 0; j < i + 1; j++)
		{
			Result.PushBack(_Base64Chars[Array4[j]]);
		}

		while (i++ < 3)
		{
			Result.PushBack(u8'=');
		}
	}

	return Elysium::Core::Text::Encoding::Default().GetString(&Result[0], Result.GetLength());
}

Elysium::Core::int32_t Elysium::Core::Convert::ToInt32(const char8_t* Value, const Elysium::Core::size Length, const Elysium::Core::uint8_t FromBase)
{
	switch (FromBase)
	{
	case 10:
		return ToInt32FromBase10(Value, Length);
	case 16:
		return ToInt32FromBase16(Value, Length);
	default:
		throw NotImplementedException();
	}
}

Elysium::Core::int32_t Elysium::Core::Convert::ToInt32(const Elysium::Core::Utf8String& Value, const Elysium::Core::uint8_t FromBase)
{
	return ToInt32(&Value[0], Value.GetLength(), FromBase);
}

Elysium::Core::int32_t Elysium::Core::Convert::ToInt32(const Elysium::Core::Utf8StringView Value, const Elysium::Core::uint8_t FromBase)
{
	return ToInt32(&Value[0], Value.GetLength(), FromBase);
}

Elysium::Core::uint8_t Elysium::Core::Convert::ToUInt8(const char8_t * Value, const Elysium::Core::uint8_t FromBase)
{
	Elysium::Core::int16_t Sign = 1;
	Elysium::Core::uint16_t i = 0;
	Elysium::Core::uint16_t Base = 0;

	// eat all whitespaces
	while (Value[i] == u8' ')
	{
		i++;
	}

	// sign
	if (Value[i] == u8'-' || Value[i] == u8'+')
	{
		Sign = 1 - 2 * (Value[i++] == u8'-');
	}

	// check for valid input
	while (Value[i] >= u8'0' && Value[i] <= u8'9')
	{
		// handle overflow cases
		if (Base > Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum / 10 || 
			(Base == Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum / 10 && Value[i] - u8'0' > 7))
		{
			return Sign == 1 ? Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum : 
				Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Minimum;
		}
		Base = 10 * Base + (Value[i++] - u8'0');
	}
	return Base * Sign;
}

Elysium::Core::uint16_t Elysium::Core::Convert::ToUInt16(const char8_t* Value, const Elysium::Core::uint8_t FromBase)
{
	Elysium::Core::int16_t Sign = 1;
	Elysium::Core::uint16_t i = 0;
	Elysium::Core::uint16_t Base = 0;

	// eat all whitespaces
	while (Value[i] == u8' ')
	{
		i++;
	}

	// sign
	if (Value[i] == u8'-' || Value[i] == u8'+')
	{
		Sign = 1 - 2 * (Value[i++] == u8'-');
	}

	// check for valid input
	while (Value[i] >= u8'0' && Value[i] <= u8'9')
	{
		// handle overflow cases
		if (Base > Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum / 10 ||
			(Base == Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum / 10 && Value[i] - u8'0' > 7))
		{
			return Sign == 1 ? Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum :
				Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Minimum;
		}
		Base = 10 * Base + (Value[i++] - u8'0');
	}
	return Base * Sign;
}

float Elysium::Core::Convert::ToSingle(const char8_t * Value)
{
	return ToSingle(Utf8String(Value));
}

float Elysium::Core::Convert::ToSingle(const Elysium::Core::Utf8String& Value)
{	// https://referencesource.microsoft.com/#mscorlib/system/number.cs,04291cc3a0b10032
	/*
	static const Elysium::Core::Globalization::NumberFormatInfo& InvariantInfo = Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo();

	for (Elysium::Core::size i = 0; i < Value.GetLength(); i++)
	{
		switch (Value[i])
		{
		case u8' ':
			break;
		case u8'-':
			break;
		case u8'0':
		case u8'1':
		case u8'2':
		case u8'3':
		case u8'4':
		case u8'5':
		case u8'6':
		case u8'7':
		case u8'8':
		case u8'9':
			break;
		}
	}
	*/
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = Elysium::Core::Text::Encoding::Default().GetBytes(&Value[0], Value.GetLength());
	std::string ByteString((char*)&Bytes[0]);
	return std::stof(ByteString);
}

const Elysium::Core::int32_t Elysium::Core::Convert::ToInt32FromBase10(const char8_t* Value, const Elysium::Core::size Length)
{
	// https://www.geeksforgeeks.org/write-your-own-atoi/
	int16_t Sign = 1;
	int32_t i = 0;
	int32_t Base = 0;

	// eat all whitespaces
	while (Value[i] == u8' ')
	{
		i++;
	}

	// sign
	if (Value[i] == u8'-' || Value[i] == u8'+')
	{
		Sign = 1 - 2 * (Value[i++] == u8'-');
	}

	// check for valid input
	while (Value[i] >= u8'0' && Value[i] <= u8'9' && i < Length)
	{
		// handle overflow cases
		if (Base > Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum / 10 ||
			(Base == Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum / 10 && Value[i] - u8'0' > 7))
		{
			return Sign == 1 ? Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Maximum :
				Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::int32_t>::Minimum;
		}
		Base = 10 * Base + (Value[i++] - u8'0');
	}
	return Base * Sign;
}

const Elysium::Core::int32_t Elysium::Core::Convert::ToInt32FromBase16(const char8_t* Value, const Elysium::Core::size Length)
{
	Elysium::Core::int32_t Result = 0;

	for (Elysium::Core::size i = 0; i < Length; i++)
	{

	}

	return Result;
}

const Elysium::Core::uint32_t Elysium::Core::Convert::ToUInt32FromBase10(const char8_t* Value, const Elysium::Core::size Length)
{
	if (Length == 0)
	{
		return 0;
	}
	if (Value == nullptr)
	{
		throw ArgumentNullException(u8"Value");
	}

	// use Elysium::Core::UInt32 to check for overflow-errors etc. 
	Elysium::Core::UInt32 Result = 0;
	Elysium::Core::uint8_t CurrentValue;

	for (Elysium::Core::size i = 0; i < Length; i++)
	{
		char8_t CurrentChar = Value[i];
		if (CurrentChar >= u8'0' && CurrentChar <= u8'9')
		{
			CurrentValue = (CurrentChar - u8'0');
		}
		else if (CurrentChar >= u8'A' && CurrentChar <= u8'F')
		{
			CurrentValue = 10 + (CurrentChar - u8'A');
		}
		else if (CurrentChar >= u8'a' && CurrentChar <= u8'f')
		{
			CurrentValue = 10 + (CurrentChar - u8'a');
		}
		else
		{
			break;
		}

		// multiply by 16
		Result <<= 4;

		// add current value
		Result |= CurrentValue;
	}

	return static_cast<const Elysium::Core::uint32_t>(Result);
}

bool Elysium::Core::Convert::IsBase64(const char8_t Char)
{
	return (isalnum(Char) || (Char == u8'+') || (Char == u8'/'));
}
