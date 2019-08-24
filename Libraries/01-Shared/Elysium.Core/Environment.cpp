#include "Environment.hpp"

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _THREAD_
#include <thread>
#endif

Elysium::Core::Environment::~Environment()
{
}

Elysium::Core::String Elysium::Core::Environment::MachineName()
{
	TCHAR MachineName[32767];
	DWORD BufferCount = 32767;
	if (GetComputerName(MachineName, &BufferCount))
	{
		return MachineName;
	}
	else
	{
		throw InvalidOperationException(L"The name of this computer cannot be obtained.");
	}
}
Elysium::Core::OperatingSystem Elysium::Core::Environment::OSVersion()
{
	// ToDos:
	//		- use preprocessor for different os
	//		- don't return fixed platform-id like PlatformID::WindowsDesktop (I'll just leave this in until I've decided on all values of PlatformID)
	//		- the behaviour of GetVersionEx(...) has changed with windows 8.1 -> make sure to handle everything correctly

	OSVERSIONINFOEX VersionInfo;
	VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	POSVERSIONINFO pVersionInfo = (POSVERSIONINFO)&VersionInfo;

#pragma warning (disable : 4996)	// disable deprecation warning
	bool Result = GetVersionEx(pVersionInfo);
#pragma warning (default : 4996)
	if(Result)
	{
		if (VersionInfo.wProductType == VER_NT_WORKSTATION)
		{	// desktop os

		}
		else
		{	// server os

		}

		return OperatingSystem(PlatformID::WindowsDesktop, Version(VersionInfo.dwMajorVersion, VersionInfo.dwMinorVersion, VersionInfo.dwBuildNumber));
	}
	else
	{
		throw InvalidOperationException(L"This property was unable to obtain the system version.");
	}
}
int Elysium::Core::Environment::ProcessorCount()
{
	/*
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	*/
	return std::thread::hardware_concurrency();
}
Elysium::Core::String Elysium::Core::Environment::UserName()
{
	TCHAR UserName[32767];
	DWORD BufferCount = 32767;
	if (GetUserName(UserName, &BufferCount))
	{
		return UserName;
	}
	else
	{
		throw InvalidOperationException(L"This property was unable to obtain the user name.");
	}
}
Elysium::Core::String Elysium::Core::Environment::SystemDirectory()
{
	TCHAR SystemDirectory[32767];
	DWORD BufferCount = 32767;
	if (GetSystemDirectory(SystemDirectory, BufferCount))
	{
		return SystemDirectory;
	}
	else
	{
		throw InvalidOperationException(L"This property was unable to obtain the system directory.");
	}
}

Elysium::Core::Environment::Environment()
{
}
