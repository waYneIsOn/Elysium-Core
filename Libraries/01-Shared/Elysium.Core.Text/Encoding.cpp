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

#ifndef _UCHAR
#include <uchar.h>
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
	throw NotImplementedException(u"size_t Elysium::Core::Text::Encoding::GetBytes(String & Input, size_t CharIndex, size_t CharCount, byte * Output)");
}

const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::ASCII()
{
	return _ASCII;
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::BigEndianUnicode()
{
	throw NotImplementedException(u"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::BigEndianUnicode()");
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Default()
{
	return _Default;
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Unicode()
{
	throw NotImplementedException(u"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Unicode()");
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32()
{
	throw NotImplementedException(u"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32()");
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()
{
	throw NotImplementedException(u"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()");
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF8()
{
	return _UTF8;
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

Elysium::Core::Collections::Template::List<byte> Elysium::Core::Text::Encoding::GetBytes(const char16_t Input) const
{
	// ToDo: can we not use nullptr as the first parameter in c16rtomb?
	mbstate_t State{};

	// get the size required
	char Buffer[4];
	size_t RequiredSize = c16rtomb(Buffer, Input, &State);

	// write bytes to list
	Elysium::Core::Collections::Template::List<byte> Result = Elysium::Core::Collections::Template::List<byte>(RequiredSize + 1);
	c16rtomb((char*)&Result[0], Input, &State);
	Result[RequiredSize] = u'\0';

	return Result;
}
Elysium::Core::Collections::Template::List<Elysium::Core::byte> Elysium::Core::Text::Encoding::GetBytes(const String & Input, const size_t CharIndex, const size_t CharCount) const
{
	// ToDo: can we not use nullptr as the first parameter in c16rtomb?
	mbstate_t State{};

	// iterate Input to get the size required
	size_t InputLength = Input.GetLength() + 1;
	size_t RequiredSize = 0;
	char Buffer[4];
	for (size_t i = 0; i < InputLength; i++)
	{
		RequiredSize += c16rtomb(Buffer, Input[i], &State);

#ifdef _DEBUG
		// ToDo: remove this block once I'm sure about buffer size
		if (c16rtomb(Buffer, Input[i], &State) > 4)
		{
			throw Exception();
		}
#endif
	}

	// write bytes to list
	Elysium::Core::Collections::Template::List<byte> Result = Elysium::Core::Collections::Template::List<byte>(RequiredSize);
	RequiredSize = 0;
	for (size_t i = 0; i < InputLength; i++)
	{
		RequiredSize += c16rtomb((char*)&Result[RequiredSize], Input[i], &State);
	}
	//Result[RequiredSize] = u'\0';

	return Result;
}

Elysium::Core::String Elysium::Core::Text::Encoding::GetString(const byte * Bytes, const size_t ByteCount) const
{
	// ToDo: can we not use nullptr as the first parameter in mbrtoc16?
	mbstate_t State{};

	// iterate Bytes to get the size required
	size_t RequiredSize = 0;
	char16_t Buffer;
	const char* ptr = (const char*)&Bytes[0];
	const char* end = (const char*)&Bytes[ByteCount - 1];
	while (size_t rc = mbrtoc16(&Buffer, ptr, end - ptr + 1, &State))
	{
		if (rc == -2 || rc == -1)
		{
			break;
		}

		ptr += rc;
		RequiredSize++;
	}

	// ...
	String Result = String(RequiredSize);
	RequiredSize = 0;
	ptr = (const char*)&Bytes[0];
	while (size_t rc = mbrtoc16(&Result[RequiredSize], ptr, end - ptr + 1, &State))
	{
		if (rc == -2 || rc == -1)
		{
			break;
		}

		ptr += rc;
		RequiredSize++;
	}
	Result[RequiredSize] = u'\0';
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
		//_EncodingName = Info.CodePageName;
		_EncodingName = u"not implemented";
		_IsSingleByte = Info.MaxCharSize == 1;
	}
#elif defined(__ANDROID__)
	// ToDo: get encoding info
#else
#error "undefined os"
#endif
}
