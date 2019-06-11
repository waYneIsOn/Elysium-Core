#include "Guid.hpp"

#ifndef __midl
#include <cstring>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::Guid Elysium::Core::Guid::_EmptyGuid = Elysium::Core::Guid();

Elysium::Core::Guid::Guid(const byte B[16])
{
	memcpy(&_Data[0], &B[0], sizeof(byte) * 16);
}
Elysium::Core::Guid::Guid(const uint32_t A, const uint16_t B, const uint16_t C, const byte* D[8])
{
	memcpy(&_Data[0], &A, sizeof(uint32_t));
	memcpy(&_Data[4], &B, sizeof(uint16_t));
	memcpy(&_Data[6], &C, sizeof(uint16_t));
	memcpy(&_Data[8], D[0], sizeof(byte) * 8);
}
Elysium::Core::Guid::~Guid()
{
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
Elysium::Core::Guid Elysium::Core::Guid::Parse(const char * Input)
{
	if (Input == nullptr)
	{	// ToDo: throw specific exception
#ifdef UNICODE
		throw Exception(L"ArgumentNullException: Input");
#else
		throw Exception("ArgumentNullException: Input");
#endif
	}

	byte Data[16];
	size_t Length = strlen(Input);
	switch (Length)
	{
	case 32:
		ParseN(Input, &Data[0]);
		break;
	case 36:
		ParseD(Input, &Data[0]);
		break;
	case 38:
		if (Input[0] == '(')
		{
			ParseB(Input, &Data[0]);
			break;
		}
		else if (Input[0] == '{')
		{
			ParseP(Input, &Data[0]);
			break;
		}
	case 68:
		ParseX(Input, &Data[0]);
		break;
	default:
		// ToDo: throw specific exception
#ifdef UNICODE
		throw Exception(L"FormatException: Input");
#else
		throw Exception("FormatException: Input");
#endif
	}

	return Guid(Data);
}

const Elysium::Core::byte * Elysium::Core::Guid::ToByteArray() const
{
	return &_Data[0];
}
void Elysium::Core::Guid::ToString(String * Output) const
{
#ifdef UNICODE
	throw NotImplementedException(L"void Elysium::Core::Guid::ToString(String * Output) const");
#else
	throw NotImplementedException("void Elysium::Core::Guid::ToString(String * Output) const");
#endif
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

bool Elysium::Core::Guid::operator==(const Guid & Other)
{
	return _Data == Other._Data;
}
bool Elysium::Core::Guid::operator!=(const Guid & Other)
{
	return _Data != Other._Data;
}
bool Elysium::Core::Guid::operator<(const Guid & Other)
{
	return _Data < Other._Data;
}
bool Elysium::Core::Guid::operator>(const Guid & Other)
{
	return _Data > Other._Data;
}
bool Elysium::Core::Guid::operator<=(const Guid & Other)
{
	return _Data <= Other._Data;
}
bool Elysium::Core::Guid::operator>=(const Guid & Other)
{
	return _Data >= Other._Data;
}

Elysium::Core::Guid::Guid()
{
	memset(&_Data[0], 0x00, sizeof(byte) * 16);
}

void Elysium::Core::Guid::ParseN(const char * Input, byte * Data)
{	// 00000000000000000000000000000000
#ifdef UNICODE
	throw NotImplementedException(L"ParseN");
#else
	throw NotImplementedException("ParseN");
#endif
}
void Elysium::Core::Guid::ParseD(const char * Input, byte * Data)
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
void Elysium::Core::Guid::ParseB(const char * Input, byte * Data)
{	// {00000000-0000-0000-0000-000000000000}
#ifdef UNICODE
	throw NotImplementedException(L"ParseB");
#else
	throw NotImplementedException("ParseB");
#endif
}
void Elysium::Core::Guid::ParseP(const char * Input, byte * Data)
{	// (00000000-0000-0000-0000-000000000000)
#ifdef UNICODE
	throw NotImplementedException(L"ParseP");
#else
	throw NotImplementedException("ParseP");
#endif
}
void Elysium::Core::Guid::ParseX(const char * Input, byte * Data)
{	// {0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}
#ifdef UNICODE
	throw NotImplementedException(L"ParseX");
#else
	throw NotImplementedException("ParseX");
#endif
}

char Elysium::Core::Guid::HexDigitToChar(char Input)
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

void Elysium::Core::Guid::ByteToHexDigit(byte Input, char* Chars)
{
	int16_t Result = Input;
	int16_t Remainder;
	int16_t Quotient;

	int i = 0;
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
