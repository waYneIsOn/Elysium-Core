#include "Guid.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::Guid Elysium::Core::Guid::_EmptyGuid = Elysium::Core::Guid::Guid();

Elysium::Core::Guid::Guid(const byte B[16])
{
	memcpy(&_Data[0], &B[0], sizeof(byte) * 16);
}
Elysium::Core::Guid::Guid(const unsigned __int32 A, const unsigned __int16 B, const unsigned __int16 C, const byte* D[8])
{
	memcpy(&_Data[0], &A, sizeof(unsigned __int32));
	memcpy(&_Data[4], &B, sizeof(unsigned __int16));
	memcpy(&_Data[6], &C, sizeof(unsigned __int16));
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
	throw NotImplementedException();
}
Elysium::Core::Guid Elysium::Core::Guid::Parse(const char * Input)
{
	if (Input == nullptr)
	{	// ToDo: throw specific exception
		throw Exception(L"ArgumentNullException: Input");
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
		throw Exception(L"FormatException: Input");
	}

	return Guid(Data);
}

const Elysium::Core::byte * Elysium::Core::Guid::ToByteArray() const
{
	return &_Data[0];
}
std::string Elysium::Core::Guid::ToString() const
{
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

	return std::string(&Data[0]);
}

Elysium::Core::Guid::Guid()
{
	memset(&_Data[0], 0x00, sizeof(byte) * 16);
}

void Elysium::Core::Guid::ParseN(const char * Input, byte * Data)
{	// 00000000000000000000000000000000
	throw NotImplementedException(L"ParseN");
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
	throw NotImplementedException(L"ParseB");
}
void Elysium::Core::Guid::ParseP(const char * Input, byte * Data)
{	// (00000000-0000-0000-0000-000000000000)
	throw NotImplementedException(L"ParseP");
}
void Elysium::Core::Guid::ParseX(const char * Input, byte * Data)
{	// {0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}
	throw NotImplementedException(L"ParseX");
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
	__int16 Result = Input;
	__int16 Remainder;
	__int16 Quotient;

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
