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
	private:
		Utf8String _Path;
		Utf8String _Filter;
	};
}
#endif
