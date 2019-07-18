#include "Encoding.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF8ENCODING
#include "UTF8Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ASCIIENCODING
#include "ASCIIEncoding.hpp"
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#elif defined(__ANDROID__)
#define EXPORT
#else
#error "undefined os"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "../Elysium.Core/ArgumentNullException.hpp"
#endif

const Elysium::Core::Text::Encoding Elysium::Core::Text::Encoding::_Default = Encoding();
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
const Elysium::Core::Text::UTF8Encoding Elysium::Core::Text::Encoding::_UTF8 = UTF8Encoding();
const Elysium::Core::Text::ASCIIEncoding Elysium::Core::Text::Encoding::_ASCII = ASCIIEncoding();
#elif defined(__ANDROID__)
// ToDo: E0298
#else
#endif

Elysium::Core::Text::Encoding::Encoding(const Encoding & Encoding)
	: _CodePage(Encoding._CodePage)
{
}
Elysium::Core::Text::Encoding::~Encoding()
{
}

void Elysium::Core::Text::Encoding::GetEncoding(int CodePage, Encoding * Output)
{
#ifdef UNICODE
	throw NotImplementedException(L"size_t Elysium::Core::Text::Encoding::GetBytes(String & Input, size_t CharIndex, size_t CharCount, byte * Output)");
#else
	throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetBytes(String & Input, size_t CharIndex, size_t CharCount, byte * Output)");
#endif
}

const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::ASCII()
{
#ifdef UNICODE
	return &_ASCII;
#else
	throw NotImplementedException("const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::ASCII()");
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::BigEndianUnicode()
{
#ifdef UNICODE
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::BigEndianUnicode()");
#else
	throw NotImplementedException("const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::BigEndianUnicode()");
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::Default()
{
	return &_Default;
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::Unicode()
{
#ifdef UNICODE
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Unicode()");
#else
	throw NotImplementedException("const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Unicode()");
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::UTF32()
{
#ifdef UNICODE
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32()");
#else
	throw NotImplementedException("const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32()");
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::UTF7()
{
#ifdef UNICODE
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()");
#else
	throw NotImplementedException("const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()");
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::UTF8()
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	return &_UTF8;
#elif defined(__ANDROID__)
	throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetBytes(String & Input, size_t CharIndex, size_t CharCount, byte * Output)");
#else
#error "undefined os"
#endif
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

Elysium::Core::Collections::Generic::List<byte> Elysium::Core::Text::Encoding::GetBytes(const String & Input, const size_t CharIndex, const size_t CharCount) const
{
	Elysium::Core::Collections::Generic::List<byte> Result;

#ifdef UNICODE
	int Length = WideCharToMultiByte(_CodePage, 0, &Input.GetCharArray()[0], (int)CharCount, 0, 0, 0, 0);

	char* ConvertedBytes = new char[Length];
	WideCharToMultiByte(_CodePage, 0, &Input.GetCharArray()[0], -1, &ConvertedBytes[0], Length, 0, 0);
	for (int i = 0; i < Length; i++)
	{
		Result.Add((byte(ConvertedBytes[i])));
	}
	delete[] ConvertedBytes;
#else
	throw NotImplementedException("Elysium::Core::Collections::Generic::List<byte> Elysium::Core::Text::Encoding::GetBytes(...)");
#endif 

	return Result;
}
Elysium::Core::String Elysium::Core::Text::Encoding::GetString(const byte * Bytes, const size_t ByteCount) const
{
	String Result;

#ifdef UNICODE
	// determine the length of the string
	const int Length = MultiByteToWideChar(_CodePage, 0, (char*)Bytes, (int)ByteCount, nullptr, 0);

	// prepare the string
	Result._Length = (size_t)Length;
	if (ByteCount != -1)
	{
		Result._Length++;
	}
	if (Result._Data != nullptr)
	{
		delete[] Result._Data;
	}
	Result._Data = new wchar_t[Result._Length];

	// now actually convert the bytes to string
	MultiByteToWideChar(_CodePage, 0, (char*)Bytes, (int)ByteCount, Result._Data, Length);

	// null terminate the string, if necessary
	if (ByteCount != -1)
	{
		Result._Data[Length] = L'\0';
	}
#else
	throw NotImplementedException("String Elysium::Core::Text::Encoding::GetString(const byte * Bytes, const size_t ByteCount, String * Output) const");
#endif

	return Result;
}

Elysium::Core::Text::Encoding::Encoding()
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	: Elysium::Core::Text::Encoding((int)GetACP())
#elif defined(__ANDROID__)
	// ToDo: how to get default encoding codepage on android?
	: Elysium::Core::Text::Encoding(0)
#else
#error "undefined os"
#endif
{
}
Elysium::Core::Text::Encoding::Encoding(int CodePage)
	: _CodePage(CodePage)
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	CPINFOEX Info;
	if (GetCPInfoEx(_CodePage, 0, &Info))
	{
		_EncodingName = Info.CodePageName;
		_IsSingleByte = Info.MaxCharSize == 1;
	}
#elif defined(__ANDROID__)
	// ToDo: get encoding info
#else
#error "undefined os"
#endif
}
