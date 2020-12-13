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

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif
#elif defined(__ANDROID__)
#define EXPORT
#else
#error "undefined os"
#endif

const Elysium::Core::String Elysium::Core::Convert::_Base64Chars = u8"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const Elysium::Core::String Elysium::Core::Convert::ToString(const int16_t Value, const int32_t FromBase)
{	// ToDo
	char Buffer[7];
	if (errno_t ErrorNumber = _itoa_s(Value, Buffer, 7, FromBase) != 0)
	{
		throw 1;
	}

	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)Buffer, strlen(Buffer));
}
const Elysium::Core::String Elysium::Core::Convert::ToString(const int32_t Value, const int32_t FromBase)
{	// ToDo: Encoding::Unicode()
	char Buffer[33];
	if (errno_t ErrorNumber = _itoa_s(Value, Buffer, 33, FromBase) != 0)
	{
		throw 1;
	}
	
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)Buffer, strlen(Buffer));
}
const Elysium::Core::String Elysium::Core::Convert::ToString(const int64_t Value, const int32_t FromBase)
{	// ToDo
	char Buffer[33];
	if (errno_t ErrorNumber = _i64toa_s(Value, Buffer, 33, FromBase) != 0)
	{
		throw 1;
	}

	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)Buffer, strlen(Buffer));
}
const Elysium::Core::String Elysium::Core::Convert::ToString(const uint16_t Value, const int32_t FromBase)
{	// ToDo
	char Buffer[7];
	if (errno_t ErrorNumber = _ultoa_s(Value, Buffer, 7, FromBase) != 0)
	{
		throw 1;
	}

	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)Buffer, strlen(Buffer));
}
const Elysium::Core::String Elysium::Core::Convert::ToString(const uint32_t Value, const int32_t FromBase)
{	// ToDo
	char Buffer[33];
	if (errno_t ErrorNumber = _ultoa_s(Value, Buffer, 33, FromBase) != 0)
	{
		throw 1;
	}

	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)Buffer, strlen(Buffer));
}
const Elysium::Core::String Elysium::Core::Convert::ToString(const uint64_t Value, const int32_t FromBase)
{	// ToDo: Encoding::Unicode()
	char Buffer[33];
	if(errno_t ErrorNumber = _ui64toa_s(Value, Buffer, 33, FromBase) != 0)
	{
		throw 1;
	}

	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)Buffer, strlen(Buffer));
}
const Elysium::Core::String Elysium::Core::Convert::ToString(const float Value, const int32_t FromBase)
{	// ToDo: Encoding::Unicode()
	std::string StringValue = std::to_string(Value);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)StringValue.c_str(), StringValue.length());
}
const Elysium::Core::String Elysium::Core::Convert::ToString(const double Value, const int32_t FromBase)
{	// ToDo: Encoding::Unicode()
	std::string StringValue = std::to_string(Value);
	return Elysium::Core::Text::Encoding::Default().GetString((const byte*)StringValue.c_str(), StringValue.length());
}
/*
const Elysium::Core::WideString Elysium::Core::Convert::ToWideString(const String & Value)
{
	int Length = MultiByteToWideChar(CP_UTF8, 0, &Value[0], -1, NULL, 0);
	wchar_t* WideChars = new wchar_t[Length];
	MultiByteToWideChar(CP_UTF8, 0, &Value[0], -1, WideChars, Length);

	WideString Result = WideString(WideChars);
	delete[] WideChars;
	
	return Result;
}
*/
Elysium::Core::Collections::Template::List<Elysium::Core::byte> Elysium::Core::Convert::FromBase64String(const String & Base64String)
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
	Elysium::Core::Collections::Template::List<Elysium::Core::byte> Result;
	size_t InputLength = Base64String.GetLength();
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
				Array4[i] = _Base64Chars.IndexOf(Array4[i]);
			}

			Array3[0] = (Array4[0] << 2) + ((Array4[1] & 0x30) >> 4);
			Array3[1] = ((Array4[1] & 0xF) << 4) + ((Array4[2] & 0x3C) >> 2);
			Array3[2] = ((Array4[2] & 0x3) << 6) + Array4[3];

			Result.AddRange(&Array3[0], 3);
			i = 0;
		}
	}

	if (i)
	{
		for (j = 0; j < i; j++)
		{
			Array4[j] = _Base64Chars.IndexOf(Array4[j]);
		}

		Array3[0] = (Array4[0] << 2) + ((Array4[1] & 0x30) >> 4);
		Array3[1] = ((Array4[1] << 0xF) << 4) + ((Array4[2] & 0x3C) >> 2);

		for (j = 0; j < i - 1; j++)
		{
			Result.Add(Array3[j]);
		}
	}

	return Result;
}
Elysium::Core::String Elysium::Core::Convert::ToBase64String(const Elysium::Core::byte * Bytes, const Elysium::Core::uint32_t Length)
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
	size_t in_len = Length;
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
				Result.Add(_Base64Chars[Array4[i]]);
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
			Result.Add(_Base64Chars[Array4[j]]);
		}

		while (i++ < 3)
		{
			Result.Add(u8'=');
		}
	}

	return Elysium::Core::Text::Encoding::Default().GetString(&Result[0], Result.GetCount());
}

Elysium::Core::int32_t Elysium::Core::Convert::ToInt32(const char8_t * Value, const int32_t FromBase)
{	// https://www.geeksforgeeks.org/write-your-own-atoi/ - this function only works for base10 atm
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
	while (Value[i] >= u8'0' && Value[i] <= u8'9')
	{
		// handle overflow cases
		if (Base > INT_MAX / 10 || (Base == INT_MAX / 10 && Value[i] - u8'0' > 7))
		{
			return Sign == 1 ? INT_MAX : INT_MIN;
		}
		Base = 10 * Base + (Value[i++] - u8'0');
	}
	return Base * Sign;
}
Elysium::Core::int32_t Elysium::Core::Convert::ToInt32(const Elysium::Core::String & Value, const int32_t FromBase)
{	// https://www.geeksforgeeks.org/write-your-own-atoi/ - this function only works for base10 atm
	int16_t Sign = 1;
	int32_t i = 0;
	int32_t Base = 0;

	// eat leading whitespaces
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
		if (Base > INT_MAX / 10 || (Base == INT_MAX / 10 && Value[i] - u8'0' > 7))
		{
			return Sign == 1 ? INT_MAX : INT_MIN;
		}
		Base = 10 * Base + (Value[i++] - u8'0');
	}
	return Base * Sign;
}

Elysium::Core::int32_t Elysium::Core::Convert::ToInt32(const Elysium::Core::StringView & Value, const int32_t FromBase)
{	// https://www.geeksforgeeks.org/write-your-own-atoi/ - this function only works for base10 atm
	int16_t Sign = 1;
	int32_t i = 0;
	int32_t Base = 0;

	// eat leading whitespaces
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
		if (Base > INT_MAX / 10 || (Base == INT_MAX / 10 && Value[i] - u8'0' > 7))
		{
			return Sign == 1 ? INT_MAX : INT_MIN;
		}
		Base = 10 * Base + (Value[i++] - u8'0');
	}
	return Base * Sign;
}

Elysium::Core::uint16_t Elysium::Core::Convert::ToUInt16(const char8_t * Value, const int32_t FromBase)
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
		if (Base > INT_MAX / 10 || (Base == INT_MAX / 10 && Value[i] - u8'0' > 7))
		{
			return Sign == 1 ? INT_MAX : INT_MIN;
		}
		Base = 10 * Base + (Value[i++] - u8'0');
	}
	return Base * Sign;
}

uint8_t Elysium::Core::Convert::ToUInt8(const char8_t * Value, const int32_t FromBase)
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
		if (Base > INT_MAX / 10 || (Base == INT_MAX / 10 && Value[i] - u8'0' > 7))
		{
			return Sign == 1 ? INT_MAX : INT_MIN;
		}
		Base = 10 * Base + (Value[i++] - u8'0');
	}
	return Base * Sign;
}

float Elysium::Core::Convert::ToSingle(const char8_t * Value)
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
	Elysium::Core::Collections::Template::Array<byte> Bytes = Elysium::Core::Text::Encoding::Default().GetBytes(&Value[0], Value.GetLength());
	std::string ByteString((char*)&Bytes[0]);
	return std::stof(ByteString);
}

bool Elysium::Core::Convert::IsBase64(const char8_t Char)
{
	return (isalnum(Char) || (Char == u8'+') || (Char == u8'/'));
}
