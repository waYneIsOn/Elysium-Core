#include "WinSymbols.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _DBGHELP_
#include <DbgHelp.h>
#endif
#endif

void Elysium::Core::Diagnostics::Internal::WinSymbols::Initialize()
{
	if (SymInitialize(GetCurrentProcess(), nullptr, true) != TRUE)
	{	// ToDo: throw SystemException() or more specific one?
		throw 1;
	}
}

void Elysium::Core::Diagnostics::Internal::WinSymbols::Shutdown()
{
	if (SymCleanup(GetCurrentProcess()) != TRUE)
	{
		// ToDo: throw SystemException() or more specific one?
		// does it even make sense to throw an exception here?
	}
}
