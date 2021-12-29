#include "Environment.hpp"

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
#endif

#ifndef _THREAD_
#include <thread>
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif
#endif

const bool Elysium::Core::Environment::Is64BitProcess()
{
#if ELYSIUM_CORE_BITNESS == 32
	// as 32-bit processes can run on 64-bit, we need to check at runtime
	BOOL f64 = FALSE;
	return IsWow64Process(GetCurrentProcess(), &f64) && f64;
#elif ELYSIUM_CORE_BITNESS == 64
	return true;
#else
	return false;
#endif
}

const Elysium::Core::Utf8String Elysium::Core::Environment::MachineName()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	// computer-name maximum length under windows appears to be 15
	wchar_t MachineName[15];
	unsigned long BufferCount = 15;
	if (GetComputerName(MachineName, &BufferCount))
	{
		return _InternalEncoding.GetString((Elysium::Core::byte*)&MachineName, BufferCount * sizeof(wchar_t));
	}
	else
	{
		throw InvalidOperationException(u8"The name of this computer cannot be obtained.");
	}
#else
#error "unsupported os"
#endif
}

const Elysium::Core::Utf8String& Elysium::Core::Environment::NewLine()
{
	return _NewLine;
}

const Elysium::Core::OperatingSystem Elysium::Core::Environment::OSVersion()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	// ToDos:
	//		- use preprocessor for different os
	//		- don't return fixed platform-id like PlatformID::WindowsDesktop (I'll just leave this in until I've decided on all values of PlatformID)
	//		- the behaviour of GetVersionEx(...) has changed with windows 8.1 -> make sure to handle everything correctly
	//		- windows phone and WindowsCE?
	// https://www.codeproject.com/Articles/678606/Part1-Overcoming-Windows-8-1s-deprecation-of-GetVe
	// https://blog.yaakov.online/finding-operating-system-version/

	OSVERSIONINFOEX VersionInfo;
	VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	POSVERSIONINFO pVersionInfo = (POSVERSIONINFO)&VersionInfo;

#pragma warning (disable : 4996)	// disable deprecation warning
	bool Result = GetVersionEx(pVersionInfo);
#pragma warning (default : 4996)
	if (Result)
	{
		if (VersionInfo.wProductType == VER_NT_WORKSTATION)
		{	// desktop os
			return OperatingSystem(PlatformID::WindowsDesktop, Version(VersionInfo.dwMajorVersion, VersionInfo.dwMinorVersion, VersionInfo.dwBuildNumber));
		}
		else
		{	// server os
			return OperatingSystem(PlatformID::WindowsServer, Version(VersionInfo.dwMajorVersion, VersionInfo.dwMinorVersion, VersionInfo.dwBuildNumber));
		}
	}
	else
	{
		throw InvalidOperationException(u8"This property was unable to obtain the system version.");
	}
#else
#error "unsupported os"
#endif
}

const Elysium::Core::uint32_t Elysium::Core::Environment::ProcessorCount()
{
	/*
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	*/
	return std::thread::hardware_concurrency();
}

const Elysium::Core::Utf8String Elysium::Core::Environment::UserName()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	// user-name maximum length under windows appears to be 1024
	wchar_t UserName[1024];
	unsigned long BufferCount = 1024;
	if (GetUserName(UserName, &BufferCount))
	{
		return _InternalEncoding.GetString((byte*)&UserName, BufferCount * sizeof(wchar_t));
	}
	else
	{
		throw InvalidOperationException(u8"This property was unable to obtain the user name.");
	}
#else
#error "unsupported os"
#endif
}

const Elysium::Core::Utf8String Elysium::Core::Environment::SystemDirectory()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	// user-name maximum length under windows appears to be ...
	wchar_t SystemDirectory[4096];
	unsigned long BufferCount = 4096;
	if (GetSystemDirectory(SystemDirectory, BufferCount))
	{
		return _InternalEncoding.GetString((byte*)&SystemDirectory, BufferCount * sizeof(wchar_t));
	}
	else
	{
		throw InvalidOperationException(u8"This property was unable to obtain the system directory.");
	}
#else
#error "unsupported os"
#endif
}
