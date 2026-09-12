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

#ifndef ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_FILESYSTEMEVENTARGS
#include "../Elysium.Core.Template/IO/FileSystem/FileSystemEventArgs.hpp"
#endif

namespace Elysium::Core::IO
{
	template class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API Elysium::Core::Template::IO::FileSystem::FileSystemEventArgs<>;

	using FileSystemEventArgs = Elysium::Core::Template::IO::FileSystem::FileSystemEventArgs<>;
}
#endif

