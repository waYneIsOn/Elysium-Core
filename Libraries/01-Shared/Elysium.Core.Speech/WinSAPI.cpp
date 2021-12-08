#include "WinSAPI.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS

#ifndef __ATLBASE_H__
#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
#endif

#ifndef __ATLCOM_H__
#include <atlcom.h>
#endif

void Elysium::Core::Speech::Internal::WinSAPI::Initialize()
{
	if (FAILED(CoInitialize(NULL)))
	{
		return;
	}
}

void Elysium::Core::Speech::Internal::WinSAPI::Shutdown()
{
	CoUninitialize();
}
#endif
