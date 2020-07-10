#include "ASCIIEncoding.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _MINWINDEF_
#include <minwindef.h>
#endif

#ifndef _WINNLS_
#include <WinNls.h>
#endif

#elif defined(__ANDROID__)

#else
#error "undefined os"
#endif
/*
const Elysium::Core::Collections::Template::Array<char16_t> Elysium::Core::Text::ASCIIEncoding::_Chart = {
	// control characters
	u'\0', u' ', u' ', u' ', u' ', u' ', u' ', u'\a', u'\b', u'\t', u'\n', u'\v', u'\f', u'\r', u' ', u' ',
	u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ',

	// printable characters
	u' ', u'!', u'"', u'#', u'$', u'%', u'&', u'\'', u'(', ')', u'*', u'+', u',', u'-', u'.', u'/',
	u'0', u'1', u'2', u'3', u'4', u'5', u'6', u'7', u'8', u'9', u':', u';', u'<', u'=', u'>', u'?',
	u'@', u'A', u'B', u'C', u'D', u'E', u'F', u'G', u'H', u'I', u'J', u'K', u'L', u'M', u'N', u'O',
	u'P', u'Q', u'R', u'S', u'T', u'U', u'V', u'W', u'X', u'Y', u'Z', u'[', u'\\', u']', u'^', u'_',
	u'`', u'a', u'b', u'c', u'd', u'e', u'f', u'g', u'h', u'i', u'j', u'k', u'l', u'm', u'n', u'o',
	u'p', u'q', u'r', u's', u't', u'u', u'v', u'w', u'x', u'y', u'z', u'{', u'|', u'}', u'~',
	
	u'\d'
};
*/
Elysium::Core::Text::ASCIIEncoding::ASCIIEncoding()
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	: Elysium::Core::Text::Encoding(20127)
#elif defined(__ANDROID__)
	: Elysium::Core::Text::Encoding(20127)
#else
#error "undefined os"
#endif
{ }
Elysium::Core::Text::ASCIIEncoding::~ASCIIEncoding()
{ }

Elysium::Core::String Elysium::Core::Text::ASCIIEncoding::GetString(const byte * Bytes, const size_t ByteCount) const
{
	String Result = String(ByteCount);
	for (size_t i = 0; i < ByteCount; i++)
	{
		Result[i] = static_cast<char16_t>(Bytes[i]);
	}

	return Result;
}
