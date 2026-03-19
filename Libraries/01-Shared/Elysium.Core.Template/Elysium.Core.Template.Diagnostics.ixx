module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#ifndef _DBGHELP_
#include <DbgHelp.h>
#endif

#ifndef _INC_TOOLHELP32
#include <tlhelp32.h>
#endif

#ifndef _PSAPI_H_
#include <Psapi.h>
#endif
#else
#error "unsupported os"
#endif

#ifndef _NEW_
#include <new>
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

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

export module Elysium.Core.Template.Diagnostics;

export
{
	using Elysium::Core::Template::Diagnostics::Process;
	using Elysium::Core::Template::Diagnostics::ProcessAccess;
	//using Elysium::Core::Template::Diagnostics::ProcessModule;
	using Elysium::Core::Template::Diagnostics::ProcessStartInfo;
	//using Elysium::Core::Template::Diagnostics::ProcessThread;
	using Elysium::Core::Template::Diagnostics::ProcessWindowStyle;
	using Elysium::Core::Template::Diagnostics::StackFrame;
	using Elysium::Core::Template::Diagnostics::StackTrace;
}
