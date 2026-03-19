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
#error "unsupported os regarding filesystem"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM
#include "IO/FileSystem.hpp"
#endif

export module Elysium.Core.Template.IO;

export
{
	using Elysium::Core::Template::IO::FileSystem;
}