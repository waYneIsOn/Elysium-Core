#include "Guid.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template/CharacterTraits.hpp"
#endif

#ifndef __midl
#include <cstring>
#endif

Elysium::Core::Guid Elysium::Core::Guid::_EmptyGuid = Elysium::Core::Guid();

Elysium::Core::Guid::Guid(const Elysium::Core::byte B[16])
	: _Data(0)
{ }
Elysium::Core::Guid::Guid(const Elysium::Core::uint32_t A, const Elysium::Core::uint16_t B, const Elysium::Core::uint16_t C, const Elysium::Core::byte* D[8])
	: _Data(0)
{
	Elysium::Core::byte* Data = (Elysium::Core::byte*)&_Data;

	memcpy(&Data[0], &A, sizeof(Elysium::Core::uint32_t));
	memcpy(&Data[4], &B, sizeof(Elysium::Core::uint16_t));
	memcpy(&Data[6], &C, sizeof(Elysium::Core::uint16_t));
	memcpy(&Data[8], D[0], sizeof(Elysium::Core::byte) * 8);
}
Elysium::Core::Guid::Guid(const Guid & Source)
	: _Data(Source._Data)
{ }
Elysium::Core::Guid::Guid(Guid && Right) noexcept
	: _Data(0)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}
Elysium::Core::Guid::~Guid()
{ }

Elysium::Core::Guid & Elysium::Core::Guid::operator=(const Guid & Source)
{
	if (this != &Source)
	{
		_Data = Source._Data;
	}

	return *this;
}
Elysium::Core::Guid & Elysium::Core::Guid::operator=(Guid && Right) noexcept
{
	if (this != &Right)
	{
		_Data = Elysium::Core::Template::Functional::Move(Right._Data);

		Right._Data = 0;
	}

	return *this;
}

const bool Elysium::Core::Guid::operator==(const Guid & Other)
{
	return _Data == Other._Data;
}
const bool Elysium::Core::Guid::operator!=(const Guid & Other)
{
	return _Data != Other._Data;
}
const bool Elysium::Core::Guid::operator<(const Guid & Other)
{
	return _Data < Other._Data;
}
const bool Elysium::Core::Guid::operator>(const Guid & Other)
{
	return _Data > Other._Data;
}
const bool Elysium::Core::Guid::operator<=(const Guid & Other)
{
	return _Data <= Other._Data;
}
const bool Elysium::Core::Guid::operator>=(const Guid & Other)
{
	return _Data >= Other._Data;
}

const Elysium::Core::Guid & Elysium::Core::Guid::Empty()
{
	return _EmptyGuid;
}
Elysium::Core::Guid Elysium::Core::Guid::NewGuid()
{
	// ToDo:
	throw NotImplementedException();
}
Elysium::Core::Guid Elysium::Core::Guid::Parse(const char8_t* Input)
{
	if (Input == nullptr)
	{
		throw ArgumentNullException();
	}

	byte Data[16];
	size_t Length = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Input);
	switch (Length)
	{
	case 32:
		ParseN(Input, &Data[0]);
		break;
	case 36:
		ParseD(Input, &Data[0]);
		break;
	case 38:
		if (Input[0] == u8'(')
		{
			ParseB(Input, &Data[0]);
			break;
		}
		else if (Input[0] == u8'{')
		{
			ParseP(Input, &Data[0]);
			break;
		}
		[[fallthrough]];
	case 68:
		ParseX(Input, &Data[0]);
		break;
	default:
		// ToDo: throw specific exception
		throw Exception(u8"FormatException: Input");
	}

	return Guid(Data);
}

const Elysium::Core::byte * Elysium::Core::Guid::ToByteArray() const
{
	return (Elysium::Core::byte*)&_Data;
}
Elysium::Core::String Elysium::Core::Guid::ToString() const
{
	throw NotImplementedException(u8"void Elysium::Core::Guid::ToString(String * Output) const");
	/*
	char Data[38] = "00000000-0000-0000-0000-000000000000";
	ByteToHexDigit(_Data[3], &Data[0]);
	ByteToHexDigit(_Data[2], &Data[2]);
	ByteToHexDigit(_Data[1], &Data[4]);
	ByteToHexDigit(_Data[0], &Data[6]);
	ByteToHexDigit(_Data[5], &Data[9]);
	ByteToHexDigit(_Data[4], &Data[11]);
	ByteToHexDigit(_Data[7], &Data[14]);
	ByteToHexDigit(_Data[6], &Data[16]);
	ByteToHexDigit(_Data[8], &Data[19]);
	ByteToHexDigit(_Data[9], &Data[21]);
	ByteToHexDigit(_Data[10], &Data[24]);
	ByteToHexDigit(_Data[11], &Data[26]);
	ByteToHexDigit(_Data[12], &Data[28]);
	ByteToHexDigit(_Data[13], &Data[30]);
	ByteToHexDigit(_Data[14], &Data[32]);
	ByteToHexDigit(_Data[15], &Data[34]);
	*/
}

Elysium::Core::Guid::Guid()
	: _Data(0)
{ }

void Elysium::Core::Guid::ParseN(const char8_t* Input, Elysium::Core::byte * Data)
{	// 00000000000000000000000000000000
	throw NotImplementedException(u8"ParseN");
}
void Elysium::Core::Guid::ParseD(const char8_t* Input, Elysium::Core::byte * Data)
{	// 00000000-0000-0000-0000-000000000000
	Data[0] = HexDigitToChar(Input[6]) * 16 + HexDigitToChar(Input[7]);
	Data[1] = HexDigitToChar(Input[4]) * 16 + HexDigitToChar(Input[5]);
	Data[2] = HexDigitToChar(Input[2]) * 16 + HexDigitToChar(Input[3]);
	Data[3] = HexDigitToChar(Input[0]) * 16 + HexDigitToChar(Input[1]);
	Data[4] = HexDigitToChar(Input[11]) * 16 + HexDigitToChar(Input[12]);
	Data[5] = HexDigitToChar(Input[9]) * 16 + HexDigitToChar(Input[10]);
	Data[6] = HexDigitToChar(Input[16]) * 16 + HexDigitToChar(Input[17]);
	Data[7] = HexDigitToChar(Input[14]) * 16 + HexDigitToChar(Input[15]);
	Data[8] = HexDigitToChar(Input[19]) * 16 + HexDigitToChar(Input[20]);
	Data[9] = HexDigitToChar(Input[21]) * 16 + HexDigitToChar(Input[22]);
	Data[10] = HexDigitToChar(Input[24]) * 16 + HexDigitToChar(Input[25]);
	Data[11] = HexDigitToChar(Input[26]) * 16 + HexDigitToChar(Input[27]);
	Data[12] = HexDigitToChar(Input[28]) * 16 + HexDigitToChar(Input[29]);
	Data[13] = HexDigitToChar(Input[30]) * 16 + HexDigitToChar(Input[31]);
	Data[14] = HexDigitToChar(Input[32]) * 16 + HexDigitToChar(Input[33]);
	Data[15] = HexDigitToChar(Input[34]) * 16 + HexDigitToChar(Input[35]);
}
void Elysium::Core::Guid::ParseB(const char8_t* Input, Elysium::Core::byte * Data)
{	// {00000000-0000-0000-0000-000000000000}
	throw NotImplementedException(u8"ParseB");
}
void Elysium::Core::Guid::ParseP(const char8_t* Input, Elysium::Core::byte * Data)
{	// (00000000-0000-0000-0000-000000000000)
	throw NotImplementedException(u8"ParseP");
}
void Elysium::Core::Guid::ParseX(const char8_t* Input, Elysium::Core::byte * Data)
{	// {0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}
	throw NotImplementedException(u8"ParseX");
}

Elysium::Core::uint8_t Elysium::Core::Guid::HexDigitToChar(char8_t Input)
{
	if (Input > 47 && Input < 58)
	{	// 0-9
		return Input - 48;
	}
	if (Input > 64 && Input < 71)
	{	// A-F
		return Input - 55;
	}
	if (Input > 96 && Input < 103)
	{	// a-f
		return Input - 87;
	}
	return 0;
}

void Elysium::Core::Guid::ByteToHexDigit(Elysium::Core::byte Input, char8_t* Chars)
{
	Elysium::Core::int16_t Result = Input;
	Elysium::Core::int16_t Remainder;
	Elysium::Core::int16_t Quotient;

	Elysium::Core::int16_t i = 0;
	do
	{
		Quotient = Result / 16;
		Remainder = Result - (Quotient * 16);
		if (Remainder >= 0 && Remainder < 10)
		{	// 0-9
			Chars[1 - i] = Remainder + 48;
		}
		if (Remainder > 9 && Remainder < 16)
		{	// a-f
			Chars[1 - i] = Remainder + 87;
		}
		Result = Quotient;
		i++;
	} while (Result != 0);
}
