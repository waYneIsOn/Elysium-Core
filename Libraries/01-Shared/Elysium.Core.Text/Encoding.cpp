#include "Encoding.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ASCIIENCODING
#include "ASCIIEncoding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF8ENCODING
#include "UTF8Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF16ENCODING
#include "UTF16Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF32ENCODING
#include "UTF32Encoding.hpp"
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

#ifndef _UCHAR
#include <uchar.h>
#endif

Elysium::Core::Text::Encoding::Encoding()
	: Elysium::Core::Text::Encoding(0)
{ }

Elysium::Core::Text::Encoding::Encoding(const Elysium::Core::uint32_t CodePage)
	: _CodePage(CodePage)
{ }

Elysium::Core::Text::Encoding::~Encoding()
{ }

/*
void Elysium::Core::Text::Encoding::GetEncoding(int CodePage, Encoding * Output)
{
	throw NotImplementedException(u8"Elysium::Core::size Elysium::Core::Text::Encoding::GetBytes(String & Input, Elysium::Core::size CharIndex, Elysium::Core::size CharCount, byte * Output)");
}
*/
Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Default()
{
	static Elysium::Core::Text::UTF8Encoding Encoding = UTF8Encoding(true, true);
	return Encoding;
}

Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::ASCII()
{
	static Elysium::Core::Text::ASCIIEncoding Encoding = ASCIIEncoding();
	return Encoding;
}

Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()
{
	throw NotImplementedException(u8"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()");
}

Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF8()
{
	static Elysium::Core::Text::UTF8Encoding Encoding = UTF8Encoding(true, true);
	return Encoding;
}

Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF16BE()
{
	static Elysium::Core::Text::UTF16Encoding Encoding = UTF16Encoding(true, true, true);
	return Encoding;
}

Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF16LE()
{
	static Elysium::Core::Text::UTF16Encoding Encoding = UTF16Encoding(false, true, true);
	return Encoding;
}

Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32BE()
{
	static Elysium::Core::Text::UTF32Encoding Encoding = UTF32Encoding(true, true, true);
	return Encoding;
}

Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32LE()
{
	static Elysium::Core::Text::UTF32Encoding Encoding = UTF32Encoding(false, true, true);
	return Encoding;
}

const Elysium::Core::Container::VectorOfByte Elysium::Core::Text::Encoding::Convert(const Encoding & SourceEncoding, const Encoding & TargetEncoding, const Elysium::Core::Container::VectorOfByte& Bytes, const Elysium::Core::size Index, const Elysium::Core::size Count)
{
	// ToDo
	throw 1;
}

const Elysium::Core::uint32_t Elysium::Core::Text::Encoding::GetCodePage() const
{
	return _CodePage;
}
