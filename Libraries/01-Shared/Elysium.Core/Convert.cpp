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
{	// ToDo
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
Elysium::Core::String Elysium::Core::Convert::ToString(const int64_t Value, const int32_t FromBase)
{	// ToDo
	char Buffer[33];
	errno_t ErrorNumber = _itoa_s(Value, Buffer, FromBase);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)Buffer, strlen(Buffer));
}
Elysium::Core::String Elysium::Core::Convert::ToString(const size_t Value, const int32_t FromBase)
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

Elysium::Core::String Elysium::Core::Convert::ToBase64String(Elysium::Core::Collections::Template::List<Elysium::Core::byte> Bytes)
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
	static const byte base64_chars[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	int in_len = Bytes.GetCount() - 1;
	int c = 0;
	int i = 0;
	int j = 0;
	byte Array3[3];
	byte Array4[4];

	Elysium::Core::Collections::Template::List<Elysium::Core::byte> Result = Elysium::Core::Collections::Template::List<Elysium::Core::byte>();

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
				Result.Add(base64_chars[Array4[i]]);
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; i < 3; j++)
		{
			Array3[j] = '\0';
		}

		Array4[0] = (Array3[0] & 0xFC) >> 2;
		Array4[1] = ((Array3[0] & 0x03) << 4) + ((Array3[1] & 0xF0) >> 4);
		Array4[2] = ((Array3[1] & 0x0F) << 2) + ((Array3[2] & 0xC0) >> 6);
		Array4[3] = Array3[2] & 0x3F;

		for (j = 0; j < i  +1; j++)
		{
			Result.Add(base64_chars[Array4[j]]);
		}

		while (i++ < 3)
		{
			Result.Add('=');
		}
	}

	return Elysium::Core::Text::Encoding::Default().GetString(&Result[0], Result.GetCount());
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
