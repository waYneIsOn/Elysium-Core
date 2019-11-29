#include "Convert.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
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

Elysium::Core::Convert::Convert()
{
}
