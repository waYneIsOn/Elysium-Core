export module Elysium.Core.Template.IO;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
import <Windows.h>;
#else
#error "unsupported os regarding filesystem"
#endif

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESYSTEM
#include "IO/FileSystem.hpp"
#endif
}