#include "Convert.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

#ifndef _INC_LIMITS
#include <limits.h>
#endif

#ifndef _STRING_
#include <string>
#endif

Elysium::Core::Convert::~Convert()
{
}

Elysium::Core::String Elysium::Core::Convert::ToString(const uint32_t Value, const int32_t FromBase)
{
	char Buffer[33];
	errno_t ErrorNumber = _itoa_s(Value, Buffer, FromBase);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)Buffer, strlen(Buffer));
}
Elysium::Core::String Elysium::Core::Convert::ToString(const int32_t Value, const int32_t FromBase)
{	// ToDo: Encoding::Unicode()
	char Buffer[33];
	errno_t ErrorNumber = _itoa_s(Value, Buffer, FromBase);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)Buffer, strlen(Buffer));
}
Elysium::Core::String Elysium::Core::Convert::ToString(const float Value, const int32_t FromBase)
{	// ToDo: Encoding::Unicode()
	std::string StringValue = std::to_string(Value);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)StringValue.c_str(), StringValue.length());
}
Elysium::Core::String Elysium::Core::Convert::ToString(const double Value, const int32_t FromBase)
{	// ToDo: Encoding::Unicode()
	std::string StringValue = std::to_string(Value);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)StringValue.c_str(), StringValue.length());
}

int32_t Elysium::Core::Convert::ToInt32(const char16_t * Value, const int32_t FromBase)
{	// https://www.geeksforgeeks.org/write-your-own-atoi/ - this function only works for base10 atm
	int16_t Sign = 1;
	int32_t i = 0;
	int32_t Base = 0;
	
	// eat all whitespaces
	while (Value[i] == u' ')
	{
		i++;
	}

	// sign
	if (Value[i] == u'-' || Value[i] == u'+')
	{
		Sign = 1 - 2 * (Value[i++] == '-');
	}

	// check for valid input
	while (Value[i] >= u'0' && Value[i] <= '9')
	{
		// handle overflow cases
		if (Base > INT_MAX / 10 || (Base == INT_MAX / 10 && Value[i] - u'0' > 7))
		{
			return Sign == 1 ? INT_MAX : INT_MIN;
		}
		Base = 10 * Base + (Value[i++] - u'0');
	}
	return Base * Sign;
}
int32_t Elysium::Core::Convert::ToInt32(const Elysium::Core::String & Value, const int32_t FromBase)
{	// https://www.geeksforgeeks.org/write-your-own-atoi/ - this function only works for base10 atm
	int16_t Sign = 1;
	int32_t i = 0;
	int32_t Base = 0;

	// eat leading whitespaces
	while (Value[i] == u' ')
	{
		i++;
	}

	// sign
	if (Value[i] == u'-' || Value[i] == u'+')
	{
		Sign = 1 - 2 * (Value[i++] == '-');
	}

	// check for valid input
	while (Value[i] >= u'0' && Value[i] <= '9')
	{
		// handle overflow cases
		if (Base > INT_MAX / 10 || (Base == INT_MAX / 10 && Value[i] - u'0' > 7))
		{
			return Sign == 1 ? INT_MAX : INT_MIN;
		}
		Base = 10 * Base + (Value[i++] - u'0');
	}
	return Base * Sign;
}

float Elysium::Core::Convert::ToSingle(const char16_t * Value)
{
	return ToSingle(String(Value));
}
float Elysium::Core::Convert::ToSingle(const Elysium::Core::String & Value)
{	// https://referencesource.microsoft.com/#mscorlib/system/number.cs,04291cc3a0b10032
	/*
	static const Elysium::Core::Globalization::NumberFormatInfo& InvariantInfo = Elysium::Core::Globalization::NumberFormatInfo::GetInvariantInfo();

	for (size_t i = 0; i < Value.GetLength(); i++)
	{
		switch (Value[i])
		{
		case u' ':
			break;
		case u'-':
			break;
		case u'0':
		case u'1':
		case u'2':
		case u'3':
		case u'4':
		case u'5':
		case u'6':
		case u'7':
		case u'8':
		case u'9':
			break;
		}
	}
	*/
	Elysium::Core::Collections::Template::List<byte> Bytes = Elysium::Core::Text::Encoding::Default().GetBytes(Value, 0, Value.GetLength());
	std::string ByteString((char*)&Bytes[0]);
	return std::stof(ByteString);
}

Elysium::Core::Convert::Convert()
{
}
