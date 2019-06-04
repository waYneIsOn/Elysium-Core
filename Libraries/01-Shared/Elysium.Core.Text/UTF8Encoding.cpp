#include "UTF8Encoding.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#elif defined(__ANDROID__)

#else
#error "undefined os"
#endif

Elysium::Core::Text::UTF8Encoding::UTF8Encoding()
	: Elysium::Core::Text::UTF8Encoding(false)
{
}
Elysium::Core::Text::UTF8Encoding::UTF8Encoding(bool EncoderShouldEmitUTF8Identifier)
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	: Elysium::Core::Text::Encoding(CP_UTF8),
#elif defined(__ANDROID__)
	: Elysium::Core::Text::Encoding(65001),
#else
#error "undefined os"
#endif
	_EncoderShouldEmitUTF8Identifier(EncoderShouldEmitUTF8Identifier)
{
}
Elysium::Core::Text::UTF8Encoding::~UTF8Encoding()
{
}
