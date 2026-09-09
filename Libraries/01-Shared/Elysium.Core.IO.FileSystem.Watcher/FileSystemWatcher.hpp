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

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMWATCHER
#include "../Elysium.Core.Template/IO/FileSystem/FileSystemWatcher.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_ATOMIC
#include "../Elysium.Core.Threading/Atomic.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#include "../Elysium.Core.Threading/ManualResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_MUTEX
#include "../Elysium.Core.Threading/Mutex.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API Elysium::Core::Template::IO::FileSystem::FileSystemWatcher;

	using FileSystemWatcher = Elysium::Core::Template::IO::FileSystem::FileSystemWatcher;
}
#endif
