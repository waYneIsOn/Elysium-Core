#include "Calendar.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _WINNLS_
#include <WinNls.h>
#endif
#else
#error "undefined os"
#endif

Elysium::Core::Globalization::Calendar::~Calendar()
{ }

void Elysium::Core::Globalization::Calendar::Test()
{
	Elysium::Core::int32_t Result =
		GetCalendarInfoEx(LOCALE_NAME_INVARIANT, CAL_GREGORIAN, nullptr, CAL_NOUSEROVERRIDE, nullptr, 0, nullptr);
	/*
	GetCalendarInfoEx((const wchar_t*)&Elysium::Core::Text::Encoding::UTF16LE().GetBytes(&_Name[0], _Name.GetLength(), sizeof(char16_t))[0],
		CALID, nullptr, CALTYPE, nullptr, 0, nullptr);
	*/
}

Elysium::Core::Globalization::Calendar::Calendar()
	: _Name()
{ }
