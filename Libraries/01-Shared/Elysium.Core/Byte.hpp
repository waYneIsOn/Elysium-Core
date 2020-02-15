/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_BYTE
#define ELYSIUM_CORE_BYTE

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

namespace Elysium::Core
{
	typedef uint8_t byte;
	typedef uint8_t BYTE;
	typedef uint8_t Byte;
	/*
	void printbytes_char(const char* ANSI_or_UTF8)
	{
		const char *bytes = ANSI_or_UTF8;
		int len = strlen(bytes);
		for (size_t i = 0; i < len; i++)
			printf("%02X ", 0xFF & bytes[i]);
		printf("\n");
	}

	void printbytes_wchar_t(const wchar_t* UTF16)
	{
		//Note, in Windows wchar_t length is 2 bytes
		const char *bytes = (const char*)UTF16;
		int len = wcslen(UTF16) * 2;
		for (size_t i = 0; i < len; i++)
			printf("%02X ", 0xFF & bytes[i]);
		printf("\n");
	}
	*/
}
#endif
