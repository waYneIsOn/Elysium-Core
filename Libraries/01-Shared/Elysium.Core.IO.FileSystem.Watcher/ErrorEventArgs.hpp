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

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../Elysium.Core.Template/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_INTERNALBUFFEROVERFLOWEXCEPTION
#include "../Elysium.Core.Template/Exceptions/IO/InternalBufferOverflowException.hpp"
#endif

namespace Elysium::Core::IO
{
	class FileSystemWatcher;

	class ELYSIUM_CORE_IO_FILESYSTEM_WATCHER ErrorEventArgs 
		: public EventArgs
	{
		friend class FileSystemWatcher;
	protected:
		ErrorEventArgs(Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException&& Exception);
	public:
		ErrorEventArgs() = delete;

		ErrorEventArgs(const ErrorEventArgs& Source) = delete;

		ErrorEventArgs(ErrorEventArgs&& Right) noexcept = delete;

		virtual ~ErrorEventArgs() noexcept = default;
	public:
		ErrorEventArgs& operator=(const ErrorEventArgs& Source) = delete;

		ErrorEventArgs& operator=(ErrorEventArgs&& Right) noexcept = delete;
	public:
		const Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException& GetException() const;
	private:
		const Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException _Exception;
	};
}
#endif

