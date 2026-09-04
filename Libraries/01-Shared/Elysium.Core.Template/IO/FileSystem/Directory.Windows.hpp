/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_DIRECTORY_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_DIRECTORY_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF8
#include "../../Text/Unicode/Utf8.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../../Text/Unicode/Utf16.hpp"
#endif

#ifndef _APISETFILE_
#include <fileapi.h>
#endif

#ifndef _ERRHANDLING_H_
#include <errhandlingapi.h>
#endif

#ifndef _WINBASE_
#include <WinBase.h>
#endif

namespace Elysium::Core::Template::IO::FileSystem
{
	class Directory
	{
	public:
		constexpr Directory() = delete;

		constexpr Directory(const Directory& Source) = delete;

		constexpr Directory(Directory&& Right) noexcept = delete;

		constexpr ~Directory() = delete;
	public:
		constexpr Directory& operator=(const Directory& Source) = delete;

		constexpr Directory& operator=(Directory&& Right) noexcept = delete;
	public:
		inline static bool Create(const char8_t* Path)
		{
			if (Path == nullptr)
			{
				return false;
			}

			const Elysium::Core::Template::System::size PathLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Path);
			if (!Elysium::Core::Template::Text::Unicode::Utf8::IsValid(Path, PathLength))
			{
				return false;
			}

			Elysium::Core::Template::Text::String<wchar_t> WindowsPath =
				Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString<char8_t>(Path, PathLength);

			BOOL Result = CreateDirectoryW(&WindowsPath[0], nullptr);
			if (Result == FALSE)
			{
				DWORD ErrorCode = GetLastError();
				// @ToDo
				bool bla = false;
			}

			return true;
		}

		inline static bool Rename(const char8_t* OldPath, const char8_t* NewPath)
		{
			if (OldPath == nullptr || NewPath == nullptr)
			{
				return false;
			}

			const Elysium::Core::Template::System::size OldPathLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(OldPath);
			if (!Elysium::Core::Template::Text::Unicode::Utf8::IsValid(OldPath, OldPathLength))
			{
				return false;
			}

			const Elysium::Core::Template::System::size NewPathLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(NewPath);
			if (!Elysium::Core::Template::Text::Unicode::Utf8::IsValid(NewPath, NewPathLength))
			{
				return false;
			}

			Elysium::Core::Template::Text::String<wchar_t> OldWindowsPath =
				Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString<char8_t>(OldPath, OldPathLength);
			Elysium::Core::Template::Text::String<wchar_t> NewWindowsPath =
				Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString<char8_t>(NewPath, NewPathLength);

			BOOL Result = MoveFileExW(&OldWindowsPath[0], &NewWindowsPath[0], MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH);
			if (Result == FALSE)
			{
				DWORD ErrorCode = GetLastError();
				// @ToDo
				bool bla = false;
			}

			return true;
		}

		inline static bool Remove(const char8_t* Path)
		{
			if (Path == nullptr)
			{
				return false;
			}

			const Elysium::Core::Template::System::size PathLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Path);
			if (!Elysium::Core::Template::Text::Unicode::Utf8::IsValid(Path, PathLength))
			{
				return false;
			}

			Elysium::Core::Template::Text::String<wchar_t> WindowsPath =
				Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString<char8_t>(Path, PathLength);

			// will only delete if empty
			BOOL Result = RemoveDirectoryW(&WindowsPath[0]);
			if (Result == FALSE)
			{
				DWORD ErrorCode = GetLastError();
				// @ToDo
				bool bla = false;
			}
			/*
			SHFILEOPSTRUCTW fileOp = { 0 };
			fileOp.wFunc = FO_DELETE;
			fileOp.pFrom = &WindowsPath[0];
			fileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
			int Result = SHFileOperationW(&fileOp);
			if (Result != 0)
			{
				// <winerror.h>
				// 2 = ERROR_FILE_NOT_FOUND
				bool bla = false;
			}
			*/
			return true;
		}
	};
}
#endif
#endif
