#include "Path.hpp"

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _APISETFILE_
#include <fileapi.h>
#endif

Elysium::Core::Utf8String Elysium::Core::IO::Path::GetFullPath(const char* ASCIIPath)
{
	char Buffer[MAX_PATH];	// ToDo: long names (MAX_PATH)
	unsigned long Length = GetFullPathNameA(ASCIIPath, MAX_PATH, &Buffer[0], nullptr);

	return Elysium::Core::Utf8String((Elysium::Core::Utf8String::ConstCharacterPointer)Buffer, Length);
}
