#include "SystemSpecific.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else
#error "unsupported os"
#endif

const Elysium::Core::int32_t Elysium::Core::SystemSpecific::GetLastErrorCode()
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	return GetLastError();
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#else
#error "unsupported os"
#endif
}

Elysium::Core::Utf8String Elysium::Core::SystemSpecific::GetErrorMessage(const Elysium::Core::int32_t ErrorCode)
{
	char* ErrorMessageBuffer = nullptr;
	Elysium::Core::size size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&ErrorMessageBuffer, 0, NULL);
	LocalFree(ErrorMessageBuffer);

	return Elysium::Core::Utf8String();
}
