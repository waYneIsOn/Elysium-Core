/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_BYTE
#define ELYSIUM_CORE_BYTE

namespace Elysium::Core
{
	typedef unsigned char byte;
	typedef unsigned char BYTE;
	typedef unsigned char Byte;
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
