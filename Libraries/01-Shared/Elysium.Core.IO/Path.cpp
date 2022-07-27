#include "Path.hpp"

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _APISETFILE_
#include <fileapi.h>
#endif

Elysium::Core::Utf8String Elysium::Core::IO::Path::GetExtension(const Elysium::Core::Utf8String& Path)
{
	Validate(Path, false);

	const Elysium::Core::Template::System::size IndexOfExtensionSeparator = Path.LastIndexOf(ExtensionSeparator);
	if (IndexOfExtensionSeparator == static_cast<Elysium::Core::Template::System::size>(-1))
	{	// no extension separator found
		return Elysium::Core::Utf8String();
	}
	else
	{
		const Elysium::Core::Template::System::size IndexOfDirectorySeparator = Path.LastIndexOf(DirectorySeparator);
		if (IndexOfDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
		{
			const Elysium::Core::Template::System::size IndexOfAlternativeDirectorySeparator = Path.LastIndexOf(AlternativeDirectorySeparator);
			if (IndexOfAlternativeDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
			{	// file only
				return Elysium::Core::Utf8String(&Path[IndexOfExtensionSeparator], Path.GetLength() - IndexOfExtensionSeparator);
			}
			else if (IndexOfAlternativeDirectorySeparator < IndexOfExtensionSeparator)
			{	// relative path and file
				return Elysium::Core::Utf8String(&Path[IndexOfExtensionSeparator], Path.GetLength() - IndexOfAlternativeDirectorySeparator);
			}
			else
			{	// relative path only
				return Elysium::Core::Utf8String();
			}
		}
		else if (IndexOfDirectorySeparator < IndexOfExtensionSeparator)
		{	// path and file
			return Elysium::Core::Utf8String(&Path[IndexOfExtensionSeparator], Path.GetLength() - IndexOfDirectorySeparator);
		}
		else
		{	// path only
			return Elysium::Core::Utf8String();
		}
	}
}

Elysium::Core::Utf8StringView Elysium::Core::IO::Path::GetExtension(const Elysium::Core::Utf8StringView Path)
{
	Validate(Path, false);

	const Elysium::Core::Template::System::size IndexOfExtensionSeparator = Path.LastIndexOf(ExtensionSeparator);
	if (IndexOfExtensionSeparator == static_cast<Elysium::Core::Template::System::size>(-1))
	{	// no extension separator found
		return Elysium::Core::Utf8StringView();
	}
	else
	{
		const Elysium::Core::Template::System::size IndexOfDirectorySeparator = Path.LastIndexOf(DirectorySeparator);
		if (IndexOfDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
		{
			const Elysium::Core::Template::System::size IndexOfAlternativeDirectorySeparator = Path.LastIndexOf(AlternativeDirectorySeparator);
			if (IndexOfAlternativeDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
			{	// file only
				return Elysium::Core::Utf8StringView(&Path[IndexOfExtensionSeparator], Path.GetLength() - IndexOfExtensionSeparator);
			}
			else if (IndexOfAlternativeDirectorySeparator < IndexOfExtensionSeparator)
			{	// relative path and file
				return Elysium::Core::Utf8String(&Path[IndexOfExtensionSeparator], Path.GetLength() - IndexOfAlternativeDirectorySeparator);
			}
			else
			{	// relative path only
				return Elysium::Core::Utf8StringView();
			}
		}
		else if (IndexOfDirectorySeparator < IndexOfExtensionSeparator)
		{	// path and file
			return Elysium::Core::Utf8StringView(&Path[IndexOfExtensionSeparator], Path.GetLength() - IndexOfDirectorySeparator);
		}
		else
		{	// path only
			return Elysium::Core::Utf8StringView();
		}
	}
}

Elysium::Core::Utf8String Elysium::Core::IO::Path::GetFileName(const Elysium::Core::Utf8String& Path)
{
	Validate(Path, false);

	const Elysium::Core::Template::System::size IndexOfExtensionSeparator = Path.LastIndexOf(ExtensionSeparator);
	if (IndexOfExtensionSeparator == static_cast<Elysium::Core::Template::System::size>(-1))
	{	// no extension separator found
		return Elysium::Core::Utf8String();
	}
	else
	{
		const Elysium::Core::Template::System::size IndexOfDirectorySeparator = Path.LastIndexOf(DirectorySeparator);
		if (IndexOfDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
		{
			const Elysium::Core::Template::System::size IndexOfAlternativeDirectorySeparator = Path.LastIndexOf(AlternativeDirectorySeparator);
			if (IndexOfAlternativeDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
			{	// file only
				return Elysium::Core::Utf8String(&Path[0], Path.GetLength());
			}
			else if (IndexOfAlternativeDirectorySeparator < IndexOfExtensionSeparator)
			{	// relative path and file
				return Elysium::Core::Utf8String(&Path[IndexOfAlternativeDirectorySeparator] + 1, Path.GetLength() - IndexOfAlternativeDirectorySeparator - 1);
			}
			else
			{	// relative path only
				return Elysium::Core::Utf8String();
			}
		}
		else if (IndexOfDirectorySeparator < IndexOfExtensionSeparator)
		{	// path and file
			const Elysium::Core::Template::System::size IndexOfAlternativeDirectorySeparator = Path.LastIndexOf(AlternativeDirectorySeparator);
			if (IndexOfAlternativeDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
			{	// no alternative directory seperator
				return Elysium::Core::Utf8String(&Path[IndexOfDirectorySeparator] + 1, Path.GetLength() - IndexOfDirectorySeparator - 1);
			}
			else
			{	// mixed
				const Elysium::Core::Template::System::size IndexOfSeparator = IndexOfAlternativeDirectorySeparator > IndexOfDirectorySeparator ?
					IndexOfAlternativeDirectorySeparator : IndexOfDirectorySeparator;
				return Elysium::Core::Utf8String(&Path[IndexOfSeparator] + 1, Path.GetLength() - IndexOfSeparator - 1);
			}
		}
		else
		{	// path only
			return Elysium::Core::Utf8String();
		}
	}
}

Elysium::Core::Utf8String Elysium::Core::IO::Path::GetFileName(const Elysium::Core::Utf8StringView Path)
{
	Validate(Path, false);

	const Elysium::Core::Template::System::size IndexOfExtensionSeparator = Path.LastIndexOf(ExtensionSeparator);
	if (IndexOfExtensionSeparator == static_cast<Elysium::Core::Template::System::size>(-1))
	{	// no extension separator found
		return Elysium::Core::Utf8String();
	}
	else
	{
		const Elysium::Core::Template::System::size IndexOfDirectorySeparator = Path.LastIndexOf(DirectorySeparator);
		if (IndexOfDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
		{
			const Elysium::Core::Template::System::size IndexOfAlternativeDirectorySeparator = Path.LastIndexOf(AlternativeDirectorySeparator);
			if (IndexOfAlternativeDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
			{	// file only
				return Elysium::Core::Utf8String(&Path[0], Path.GetLength());
			}
			else if (IndexOfAlternativeDirectorySeparator < IndexOfExtensionSeparator)
			{	// relative path and file
				return Elysium::Core::Utf8String(&Path[IndexOfAlternativeDirectorySeparator] + 1, Path.GetLength() - IndexOfAlternativeDirectorySeparator - 1);
			}
			else
			{	// relative path only
				return Elysium::Core::Utf8String();
			}
		}
		else if (IndexOfDirectorySeparator < IndexOfExtensionSeparator)
		{	// path and file
			const Elysium::Core::Template::System::size IndexOfAlternativeDirectorySeparator = Path.LastIndexOf(AlternativeDirectorySeparator);
			if (IndexOfAlternativeDirectorySeparator == static_cast<Elysium::Core::Template::System::size>(-1))
			{	// no alternative directory seperator
				return Elysium::Core::Utf8String(&Path[IndexOfDirectorySeparator] + 1, Path.GetLength() - IndexOfDirectorySeparator - 1);
			}
			else
			{	// mixed
				const Elysium::Core::Template::System::size IndexOfSeparator = IndexOfAlternativeDirectorySeparator > IndexOfDirectorySeparator ?
					IndexOfAlternativeDirectorySeparator : IndexOfDirectorySeparator;
				return Elysium::Core::Utf8String(&Path[IndexOfSeparator] + 1, Path.GetLength() - IndexOfSeparator - 1);
			}
		}
		else
		{	// path only
			return Elysium::Core::Utf8String();
		}
	}
}

const bool Elysium::Core::IO::Path::EndsInDirectorySeperator(const Elysium::Core::Utf8String& Path)
{
	Validate(Path, false);

	return Path[Path.GetLength() - 1] == DirectorySeparator;	// ToDo: AlternativeDirectorySeparator?
}

const bool Elysium::Core::IO::Path::EndsInDirectorySeperator(const Elysium::Core::Utf8StringView Path)
{
	Validate(Path, false);

	return Path[Path.GetLength() - 1] == DirectorySeparator;	// ToDo: AlternativeDirectorySeparator?
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
