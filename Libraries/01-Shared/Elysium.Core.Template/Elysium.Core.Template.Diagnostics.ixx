export module Elysium.Core.Template.Diagnostics;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define WIN32_LEAN_AND_MEAN
	//#include <Windows.h>;
	import <Windows.h>;
	#endif

//import <DbgHelp.h>;
//import <Psapi.h>;
//import <TlHelp32.h>;

//#pragma warning(disable:5244)
//#pragma warning(default:5244)
#else
#error "unsupported os"
#endif

#ifndef _INITIALIZER_LIST_
//#include <initializer_list>
//import <initializer_list>;
#endif

#ifndef _NEW_
//#include <new>;
//import <new>;
#endif

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS
#include "Diagnostics/Process.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSACCESS
#include "Diagnostics/ProcessAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSMODULE
#include "Diagnostics/ProcessModule.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSSTARTINFO
#include "Diagnostics/ProcessStartInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSTHREAD
#include "Diagnostics/ProcessThread.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSWINDOWSTYLE
#include "Diagnostics/ProcessWindowStyle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKFRAME
#include "Diagnostics/StackFrame.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKTRACE
#include "Diagnostics/StackTrace.hpp"
#endif
}
