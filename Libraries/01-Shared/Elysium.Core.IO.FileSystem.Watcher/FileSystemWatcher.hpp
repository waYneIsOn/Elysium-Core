/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESYSTEMWATCHER
#define ELYSIUM_CORE_IO_FILESYSTEMWATCHER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_NOTIFYFILTERS
#include "NotifyFilters.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _APISETFILE_
#include <fileapi.h>
#endif
#else
#error "undefined os"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER FileSystemWatcher
	{
	public:
		FileSystemWatcher(const Utf8String& Path);

		FileSystemWatcher(const Utf8String& Path, const Utf8String& Filter);

		FileSystemWatcher(const FileSystemWatcher& Source) = delete;

		FileSystemWatcher(FileSystemWatcher&& Right) noexcept = delete;

		~FileSystemWatcher();
	public:
		FileSystemWatcher& operator=(const FileSystemWatcher& Source) = delete;

		FileSystemWatcher& operator=(FileSystemWatcher&& Right) noexcept = delete;
	public:
		const Utf8String& GetPath() const;

		const Utf8String& GetFilter() const;
	public:
		void BeginInit();
	private:
		inline static const NotifyFilters DefaultNotifyFilters = NotifyFilters::LastWrite | NotifyFilters::FileName | NotifyFilters::DirectoryName;
	private:
		NotifyFilters _NotifyFilters;
		bool _IncludeSubdirectories;
		Utf8String _Path;
		Utf8String _Filter;
#if defined ELYSIUM_CORE_OS_WINDOWS
		HANDLE _DirectoryHandle = nullptr;
#else
#error "undefined os"
#endif
	};
}
#endif
