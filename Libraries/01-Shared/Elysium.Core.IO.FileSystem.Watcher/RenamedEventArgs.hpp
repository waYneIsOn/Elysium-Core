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

	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER RenamedEventArgs : public EventArgs
	{
		friend class FileSystemWatcher;
	protected:
		RenamedEventArgs(const WatcherChangeTypes ChangeType, const char8_t* Directory, const char8_t* Name, const char8_t* OldName);
	public:
		RenamedEventArgs(const RenamedEventArgs& Source) = delete;

		RenamedEventArgs(RenamedEventArgs&& Right) noexcept = delete;

		virtual ~RenamedEventArgs();
	public:
		RenamedEventArgs& operator=(const RenamedEventArgs& Source) = delete;

		RenamedEventArgs& operator=(RenamedEventArgs&& Right) noexcept = delete;
	public:
		//const Exception& GetException() const;
	private:
		//Utf8String _OldFullPath;
		//Utf8String _OldName;
	};
}
#endif
