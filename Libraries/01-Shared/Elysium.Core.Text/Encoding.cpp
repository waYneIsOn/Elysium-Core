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

const Elysium::Core::Text::ASCIIEncoding Elysium::Core::Text::Encoding::_ASCII = ASCIIEncoding();
const Elysium::Core::Text::UTF8Encoding Elysium::Core::Text::Encoding::_UTF8 = UTF8Encoding(true, true);
const Elysium::Core::Text::UTF16Encoding Elysium::Core::Text::Encoding::_UTF16BE = UTF16Encoding(true, true, true);
const Elysium::Core::Text::UTF16Encoding Elysium::Core::Text::Encoding::_UTF16LE = UTF16Encoding(false, true, true);
const Elysium::Core::Text::UTF32Encoding Elysium::Core::Text::Encoding::_UTF32BE = UTF32Encoding(true, true, true);
const Elysium::Core::Text::UTF32Encoding Elysium::Core::Text::Encoding::_UTF32LE = UTF32Encoding(false, true, true);

Elysium::Core::Text::Encoding::~Encoding()
{ }
/*
void Elysium::Core::Text::Encoding::GetEncoding(int CodePage, Encoding * Output)
{
	throw NotImplementedException(u8"size_t Elysium::Core::Text::Encoding::GetBytes(String & Input, size_t CharIndex, size_t CharCount, byte * Output)");
}
*/
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::Default()
{
	return _UTF8;
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::ASCII()
{
	return _ASCII;
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()
{
	throw NotImplementedException(u8"const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF7()");
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF8()
{
	return _UTF8;
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF16BE()
{
	return _UTF16BE;
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF16LE()
{
	return _UTF16LE;
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32BE()
{
	return _UTF32BE;
}
const Elysium::Core::Text::Encoding & Elysium::Core::Text::Encoding::UTF32LE()
{
	return _UTF32LE;
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Text::Encoding::Convert(const Encoding & SourceEncoding, const Encoding & TargetEncoding, const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Bytes, const size_t Index, const size_t Count)
{
	// ToDo
	throw 1;
}

const Elysium::Core::uint32_t Elysium::Core::Text::Encoding::GetCodePage() const
{
	return _CodePage;
}

Elysium::Core::Text::Encoding::Encoding()
	: Elysium::Core::Text::Encoding(0)
{ }

Elysium::Core::Text::Encoding::Encoding(const Elysium::Core::uint32_t CodePage)
	: _CodePage(CodePage)
{ }
