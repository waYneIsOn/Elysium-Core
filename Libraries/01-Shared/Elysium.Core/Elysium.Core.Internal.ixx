module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#else
#error "unsupported os"
#endif

export module Elysium.Core.Internal;

module :private;
/*
export
{
#ifndef ELYSIUM_CORE_INTERNAL_ASYNCRESULT
#include "AsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_INTERNAL_WINDOWSERRORCODE
#include "WindowsErrorCode.hpp"
#endif

#ifndef ELYSIUM_CORE_INTERNAL_WRAPPEDOVERLAP
#include "WrappedOverlap.hpp"
#endif
}
*/