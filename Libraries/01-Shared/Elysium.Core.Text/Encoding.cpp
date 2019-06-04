#include "Encoding.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF8ENCODING
#include "UTF8Encoding.hpp"
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
const Elysium::Core::Text::UTF8Encoding Elysium::Core::Text::UTF8Encoding::_UTF8 = UTF8Encoding();
#elif defined(__ANDROID__)
// ToDo: E0298
#else
#endif

Elysium::Core::Text::Encoding::~Encoding()
{
}

void Elysium::Core::Text::Encoding::GetEncoding(int CodePage, Encoding * Output)
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException(L"size_t Elysium::Core::Text::Encoding::GetBytes(String & Input, size_t CharIndex, size_t CharCount, byte * Output)");
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetBytes(String & Input, size_t CharIndex, size_t CharCount, byte * Output)");
#else
#error "undefined os"
#endif
}

const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::ASCII()
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::ASCII()");
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException("const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::ASCII()");
#else
#error "undefined os"
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::BigEndianUnicode()
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::BigEndianUnicode()");
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::BigEndianUnicode()");
#else
#error "undefined os"
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::Default()
{
	return &_Default;
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::Unicode()
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Unicode()");
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Unicode()");
#else
#error "undefined os"
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::UTF32()
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32()");
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32()");
#else
#error "undefined os"
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::UTF7()
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()");
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException(L"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()");
#else
#error "undefined os"
#endif
}
const Elysium::Core::Text::Encoding * Elysium::Core::Text::Encoding::UTF8()
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	return &_UTF8;
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetBytes(String & Input, size_t CharIndex, size_t CharCount, byte * Output)");
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

size_t Elysium::Core::Text::Encoding::GetBytes(const String * Input, const size_t CharIndex, const size_t CharCount, Elysium::Core::Collections::Generic::List<byte>* Output) const
{
#ifdef UNICODE
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
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetBytes(...)");
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetBytes(...)");
#else
#error "undefined os"
#endif
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
	const int Length = MultiByteToWideChar(_CodePage, 0, (char*)Bytes, -1, 0, 0);
	Output->_Length = (size_t)Length;
	if (Output->_Data != nullptr)
	{
		delete[] Output->_Data;
	}
	Output->_Data = new wchar_t[Length];
	MultiByteToWideChar(_CodePage, 0, (char*)Bytes, -1, Output->_Data, Length);

	return Length;
#else
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetString(const byte * Bytes, const size_t ByteCount, String * Output) const");
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException("size_t Elysium::Core::Text::Encoding::GetString(const byte * Bytes, const size_t ByteCount, String * Output) const");
#else
#error "undefined os"
#endif
#endif 
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