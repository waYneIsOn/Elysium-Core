/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#define ELYSIUM_CORE_THREADING_THREADPOOL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL
#include "../Elysium.Core.Template/Threading/ThreadPool.hpp"
#endif

namespace Elysium::Core::IO
{
	class FileStream;
	class FileSystemWatcher;
}

namespace Elysium::Core::Net::Sockets
{
	class Socket;
}

namespace Elysium::Core::Threading::Tasks
{
	class Task;
}

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API  Elysium::Core::Template::Threading::ThreadPool;

	using ThreadPool = Elysium::Core::Template::Threading::ThreadPool;
}
#endif
