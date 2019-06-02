#include "UTF8Encoding.hpp"

#ifndef _WINDOWS_
#include <Windows.h>
#endif

Elysium::Core::Text::UTF8Encoding::UTF8Encoding()
	: Elysium::Core::Text::UTF8Encoding(false)
{
}
Elysium::Core::Text::UTF8Encoding::UTF8Encoding(bool EncoderShouldEmitUTF8Identifier)
	: Elysium::Core::Text::Encoding(CP_UTF8),
	_EncoderShouldEmitUTF8Identifier(EncoderShouldEmitUTF8Identifier)
{
}
Elysium::Core::Text::UTF8Encoding::~UTF8Encoding()
{
}
