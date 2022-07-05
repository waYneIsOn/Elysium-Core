#include "Path.hpp"

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _APISETFILE_
#include <fileapi.h>
#endif

const bool Elysium::Core::IO::Path::EndsInDirectorySeperator(const Elysium::Core::Utf8String& Path)
{
	Validate(Path, false);

	return Path[Path.GetLength() - 1] == DirectorySeparator;
}

const bool Elysium::Core::IO::Path::EndsInDirectorySeperator(const Elysium::Core::Utf8StringView Path)
{
	Validate(Path, false);

	return Path[Path.GetLength() - 1] == DirectorySeparator;
}

Elysium::Core::Utf8String Elysium::Core::IO::Path::GetFullPath(const Elysium::Core::Utf8String& Path)
{
	Validate(Path, false);

	return GetFullPath((char*)&Path[0]);
}

Elysium::Core::Utf8String Elysium::Core::IO::Path::GetFullPath(const Elysium::Core::Utf8StringView Path)
{
	Validate(Path, false);

	return GetFullPath((char*)&Path[0]);
}

Elysium::Core::Utf8String Elysium::Core::IO::Path::GetFullPath(const Elysium::Core::Utf8String& Path, const Elysium::Core::Utf8String& BasePath)
{
	Validate(Path, false);
	Validate(BasePath, false);

	throw 1;
}

Elysium::Core::Utf8String Elysium::Core::IO::Path::GetFullPath(const Elysium::Core::Utf8StringView Path, const Elysium::Core::Utf8StringView BasePath)
{
	Validate(Path, false);
	Validate(BasePath, false);

	throw 1;
}

void Elysium::Core::IO::Path::Validate(const Elysium::Core::Utf8String& Path, const bool ValidateWildcards)
{
	if (Path.GetLength() == 0)
	{
		throw ArgumentException(u8"Path");
	}

	if (Path.IndexOfAny(&InvalidPathCharacters[0], 35) != static_cast<Elysium::Core::Template::System::size>(-1) ||
		(ValidateWildcards && Path.IndexOfAny(&WildcardCharacters[0], 2) != static_cast<Elysium::Core::Template::System::size>(-1)))
	{
		throw ArgumentException(u8"Path contains illegal characters.");
	}
}

void Elysium::Core::IO::Path::Validate(const Elysium::Core::Utf8StringView Path, const bool ValidateWildcards)
{
	if (Path.GetLength() == 0)
	{
		throw ArgumentException(u8"Path");
	}

	if (Path.IndexOfAny(&InvalidPathCharacters[0], 35) != static_cast<Elysium::Core::Template::System::size>(-1) ||
		(ValidateWildcards && Path.IndexOfAny(&WildcardCharacters[0], 2) != static_cast<Elysium::Core::Template::System::size>(-1)))
	{
		throw ArgumentException(u8"Path contains illegal characters.");
	}
}

Elysium::Core::Utf8String Elysium::Core::IO::Path::GetFullPath(const char* ASCIIPath)
{
	char Buffer[MAX_PATH];	// ToDo: long names (MAX_PATH)
	unsigned long Length = GetFullPathNameA(ASCIIPath, MAX_PATH, &Buffer[0], nullptr);

	return Elysium::Core::Utf8String((Elysium::Core::Utf8String::ConstCharacterPointer)Buffer, Length);
}
