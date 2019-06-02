#include "Encoding.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF8ENCODING
#include "UTF8Encoding.hpp"
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "../Elysium.Core/ArgumentNullException.hpp"
#endif

const Elysium::Core::Text::Encoding Elysium::Core::Text::Encoding::_Default = Encoding();
const Elysium::Core::Text::UTF8Encoding Elysium::Core::Text::UTF8Encoding::_UTF8 = UTF8Encoding();

Elysium::Core::Text::Encoding::~Encoding()
{
}

void Elysium::Core::Text::Encoding::GetEncoding(int CodePage, Encoding * Output)
{
	throw NotImplementedException(L"size_t Elysium::Core::Text::Encoding::GetBytes(String & Input, size_t CharIndex, size_t CharCount, byte * Output)");
}

const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::ASCII()
{
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::ASCII()");
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::BigEndianUnicode()
{
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::BigEndianUnicode()");
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::Default()
{
	return &_Default;
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::Unicode()
{
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Unicode()");
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::UTF32()
{
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32()");
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::UTF7()
{
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()");
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::UTF8()
{
	return &_UTF8;
}

bool Elysium::Core::Text::Encoding::GetIsSingleByte() const
{
	return _IsSingleByte;
}
int Elysium::Core::Text::Encoding::GetCodePage() const
{
	return _CodePage;
}
const Elysium::Core::String & Elysium::Core::Text::Encoding::GetEncodingName() const
{
	return (const String&)_EncodingName;
}

#include <xstring>
size_t Elysium::Core::Text::Encoding::GetBytes(const String * Input, const size_t CharIndex, const size_t CharCount, Elysium::Core::Collections::Generic::List<byte>* Output) const
{
#ifdef UNICODE
	// ToDo: use _CodePage instead of CP_UTF8?
	int Length = WideCharToMultiByte(_CodePage, 0, &Input->GetCharArray()[0], -1, 0, 0, 0, 0);
	char* ConvertedBytes = new char[Length];
	WideCharToMultiByte(_CodePage, 0, &Input->GetCharArray()[0], -1, &ConvertedBytes[0], Length, 0, 0);
	for (int i = 0; i < Length; i++)
	{
		Output->Add((byte(ConvertedBytes[i])));
	}
	delete[] ConvertedBytes;

	return Length;
#else
	throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetBytes(...)");
#endif 
}
size_t Elysium::Core::Text::Encoding::GetString(const byte * Bytes, const size_t ByteCount, String * Output) const
{
#ifdef UNICODE
	if (Output == nullptr)
	{
		throw ArgumentNullException(L"Output");
	}

	// ToDo: this only works if the last byte is 0x00 ie. \0 atm
	// ToDo: use _CodePage instead of CP_UTF8?
	const int Length = MultiByteToWideChar(_CodePage, 0, (char*)Bytes, -1, 0, 0);
	ElysiumChar* ConvertedString = new ElysiumChar[Length];
	MultiByteToWideChar(_CodePage, 0, (char*)Bytes, -1, &ConvertedString[0], Length);
	*Output = ConvertedString;
	delete[] ConvertedString;

	return Length;
#else
	throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetString(const byte * Bytes, const size_t ByteCount, String * Output) const");
#endif 
}

Elysium::Core::Text::Encoding::Encoding()
	: Elysium::Core::Text::Encoding((int)GetACP())
{
}
Elysium::Core::Text::Encoding::Encoding(int CodePage)
	: _CodePage(CodePage)
{
	CPINFOEX Info;
	if (GetCPInfoEx(_CodePage, 0, &Info))
	{
		_EncodingName = Info.CodePageName;
		_IsSingleByte = Info.MaxCharSize == 1;
	}
}
