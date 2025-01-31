/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESYSTEMEVENTARGS
#define ELYSIUM_CORE_IO_FILESYSTEMEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_WATCHERCHANGETYPES
#include "WatcherChangeTypes.hpp"
#endif

namespace Elysium::Core::IO
{
	class FileSystemWatcher;

	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER FileSystemEventArgs 
		: public EventArgs
	{
		friend class FileSystemWatcher;
	protected:
		FileSystemEventArgs(const WatcherChangeTypes ChangeType, Elysium::Core::Utf8String&& FullPath, Elysium::Core::Utf8String&& Name);
	public:
		FileSystemEventArgs(const FileSystemEventArgs& Source) = delete;

		FileSystemEventArgs(FileSystemEventArgs&& Right) noexcept = delete;

		virtual ~FileSystemEventArgs();
	public:
		FileSystemEventArgs& operator=(const FileSystemEventArgs& Source) = delete;

		FileSystemEventArgs& operator=(FileSystemEventArgs&& Right) noexcept = delete;
	public:
		const WatcherChangeTypes GetChangeType() const;

		const Utf8String& GetFullPath() const;

		const Utf8String& GetName() const;
	private:
		WatcherChangeTypes _ChangeType;
		Utf8String _FullPath;
		Utf8String _Name;
	};
}
#endif

