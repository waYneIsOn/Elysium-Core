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

Elysium::Core::Text::ASCIIEncoding::ASCIIEncoding()
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	: Elysium::Core::Text::Encoding(20127)
#elif defined(__ANDROID__)
	: Elysium::Core::Text::Encoding(20127)
#else
#error "undefined os"
#endif
{
}
Elysium::Core::Text::ASCIIEncoding::~ASCIIEncoding()
{
}
