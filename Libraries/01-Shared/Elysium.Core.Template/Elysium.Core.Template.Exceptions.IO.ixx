module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#else
#error "unsupported os"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_INTERNALBUFFEROVERFLOWEXCEPTION
#include "Exceptions/IO/InternalBufferOverflowException.hpp"
#endif

export module Elysium.Core.Template.Exceptions.IO;

export
{
	using Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException;
}
