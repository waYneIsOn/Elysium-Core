#include "File.hpp"

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Elysium.Core.Template/Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
#endif

void Elysium::Core::IO::File::Delete(const char8_t* Path)
{
	if (Path == nullptr)
	{
		return;
	}

	// ToDo: don't assume correct input (encoding and path might be directory)
	WideString OSPath = Template::Text::Unicode::Utf16::SafeToWideString(Path, Template::Text::CharacterTraits<char8_t>::GetLength(Path));

	BOOL Result = DeleteFileW(&OSPath[0]);
}

void Elysium::Core::IO::File::Move(const char8_t* SourceFileName, const char8_t* DestinationFileName, const bool Overwrite)
{
	if (SourceFileName == nullptr)
	{
		return;
	}

	if (DestinationFileName == nullptr)
	{
		return;
	}

	// ToDo: don't assume correct input (encoding and path might be directory)
	WideString OSSourceFileName = Template::Text::Unicode::Utf16::SafeToWideString(SourceFileName, Template::Text::CharacterTraits<char8_t>::GetLength(SourceFileName));
	WideString OSDestinationFileName = Template::Text::Unicode::Utf16::SafeToWideString(DestinationFileName, Template::Text::CharacterTraits<char8_t>::GetLength(DestinationFileName));

	BOOL Result = MoveFileExW(&OSSourceFileName[0], &OSDestinationFileName[0], Overwrite ? MOVEFILE_REPLACE_EXISTING : 0x00000000);
}
