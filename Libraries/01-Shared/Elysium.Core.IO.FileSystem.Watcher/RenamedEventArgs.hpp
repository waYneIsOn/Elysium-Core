/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_RENAMEDEVENTARGS
#define ELYSIUM_CORE_IO_RENAMEDEVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEMEVENTARGS
#include "FileSystemEventArgs.hpp"
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

	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER RenamedEventArgs 
		: public FileSystemEventArgs
	{
		friend class FileSystemWatcher;
	protected:
		RenamedEventArgs(const WatcherChangeTypes ChangeType, Utf8String&& FullPath, Utf8String&& Name, Utf8String&& OldName);
	public:
		RenamedEventArgs(const RenamedEventArgs& Source) = delete;

		RenamedEventArgs(RenamedEventArgs&& Right) noexcept = delete;

		virtual ~RenamedEventArgs();
	public:
		RenamedEventArgs& operator=(const RenamedEventArgs& Source) = delete;

		RenamedEventArgs& operator=(RenamedEventArgs&& Right) noexcept = delete;
	public:
		//const Utf8String& GetOldFullPath() const;

		const Utf8String& GetOldName() const;
	private:
		Utf8String _OldName;
	};
}
#endif
