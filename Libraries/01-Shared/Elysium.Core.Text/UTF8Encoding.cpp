#include "UTF8Encoding.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif
#elif defined(__ANDROID__)

#else
#error "undefined os"
#endif

Elysium::Core::Text::UTF8Encoding::UTF8Encoding()
	: Elysium::Core::Text::UTF8Encoding(false)
{ }
Elysium::Core::Text::UTF8Encoding::UTF8Encoding(bool EncoderShouldEmitUTF8Identifier)
	: Elysium::Core::Text::Encoding(CP_UTF8),
	_EncoderShouldEmitUTF8Identifier(EncoderShouldEmitUTF8Identifier)
{ }
Elysium::Core::Text::UTF8Encoding::~UTF8Encoding()
{ }

const bool Elysium::Core::Text::UTF8Encoding::GetIsSingleByte() const
{
	return false;
}

const Elysium::Core::String Elysium::Core::Text::UTF8Encoding::GetEncodingName() const
{
	return Elysium::Core::String(u"Unicode (UTF-8)");
}

Elysium::Core::Collections::Template::List<byte> Elysium::Core::Text::UTF8Encoding::GetBytes(const char16_t Input) const
{
	return Elysium::Core::Collections::Template::List<byte>();
}
Elysium::Core::Collections::Template::List<byte> Elysium::Core::Text::UTF8Encoding::GetBytes(const String & Input, const size_t CharIndex, const size_t CharCount) const
{
	return Elysium::Core::Collections::Template::List<byte>();
}

Elysium::Core::String Elysium::Core::Text::UTF8Encoding::GetString(const byte * Bytes, const size_t ByteCount) const
{
	return String();
}
