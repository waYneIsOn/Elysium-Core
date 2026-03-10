export module Elysium.Core.Template.Exceptions.IO;
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>;
import <Windows.h>;
#endif
#else
#error "unsupported os"
#endif

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_INTERNALBUFFEROVERFLOWEXCEPTION
#include "Exceptions/IO/InternalBufferOverflowException.hpp"
#endif
}
