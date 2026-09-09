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

#ifndef ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_RENAMEDEVENTARGS
#include "../Elysium.Core.Template/IO/FileSystem/RenamedEventArgs.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API Elysium::Core::Template::IO::FileSystem::RenamedEventArgs;

	using RenamedEventArgs = Elysium::Core::Template::IO::FileSystem::RenamedEventArgs;
}
#endif
