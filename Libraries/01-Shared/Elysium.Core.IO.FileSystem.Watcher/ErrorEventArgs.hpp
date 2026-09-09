/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_ERROREVENTARGS
#define ELYSIUM_CORE_IO_ERROREVENTARGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM_ERROREVENTEVENTARGS
#include "../Elysium.Core.Template/IO/FileSystem/ErrorEventArgs.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API Elysium::Core::Template::IO::FileSystem::ErrorEventArgs;

	using ErrorEventArgs = Elysium::Core::Template::IO::FileSystem::ErrorEventArgs;
}
#endif

