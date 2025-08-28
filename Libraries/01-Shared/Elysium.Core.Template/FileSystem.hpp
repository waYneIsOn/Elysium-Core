/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM
#define ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF8
#include "Utf8.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINBASE_
	#include <WinBase.h>
	#endif
#else
#error "unsupported os regarding filesystem"
#endif

namespace Elysium::Core::Template::IO
{
	class FileSystem
	{
	public:
		FileSystem() = delete;

		FileSystem(const FileSystem& Source) = delete;

		FileSystem(FileSystem&& Right) noexcept = delete;

		~FileSystem() = delete;
	public:
		FileSystem& operator=(const FileSystem& Source) = delete;

		FileSystem& operator=(FileSystem&& Right) noexcept = delete;
	public:
		static bool CreateFolder(const char8_t* Path);

		static bool RenameFolder(const char8_t* OldPath, const char8_t* NewPath);

		static bool RemoveFolder(const char8_t* Path);
	};
	
	inline bool Elysium::Core::Template::IO::FileSystem::CreateFolder(const char8_t* Path)
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
			bool bla = false;
		}

		return true;
	}

	inline bool Elysium::Core::Template::IO::FileSystem::RenameFolder(const char8_t* OldPath, const char8_t* NewPath)
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
			bool bla = false;
		}

		return true;
	}

	inline bool Elysium::Core::Template::IO::FileSystem::RemoveFolder(const char8_t* Path)
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

		BOOL Result = RemoveDirectoryW(&WindowsPath[0]);
		if (Result == FALSE)
		{
			DWORD ErrorCode = GetLastError();
			bool bla = false;
		}

		return true;
	}
}
#endif
