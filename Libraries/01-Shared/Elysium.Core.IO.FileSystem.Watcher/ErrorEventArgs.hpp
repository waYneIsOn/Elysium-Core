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

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESYSTEM_WATCHER_API
#include "API.hpp"
#endif

namespace Elysium::Core::IO
{
	class FileSystemWatcher;

	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER ErrorEventArgs : public EventArgs
	{
		friend class FileSystemWatcher;
	protected:
		//ErrorEventArgs(Exception&& Exception);
	public:
		ErrorEventArgs(const ErrorEventArgs& Source) = delete;

		ErrorEventArgs(ErrorEventArgs&& Right) noexcept = delete;

		virtual ~ErrorEventArgs();
	public:
		ErrorEventArgs& operator=(const ErrorEventArgs& Source) = delete;

		ErrorEventArgs& operator=(ErrorEventArgs&& Right) noexcept = delete;
	public:
		//const Exception& GetException() const;
	private:
		//Exception _Exception;
	};
}
#endif

