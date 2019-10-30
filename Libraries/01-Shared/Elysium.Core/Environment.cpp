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

bool Elysium::Core::Environment::Is64BitProcess()
{
//#if sizeof(void*) == 8
#ifdef _WIN64 || __x86_64__ || __ppc64__
	return true;
#else
	return false;
#endif
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
Elysium::Core::String Elysium::Core::Environment::NewLine()
{
#if defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#ifdef UNICODE
	return L"\r\n";
#else
	return "\r\n";
#endif
#elif defined(UNIX)	// ToDo
#ifdef UNICODE
	return L"\n";
#else
	return "\n";
#endif
#elif defined(PREOSX_MAC)	// ToDo
#ifdef UNICODE
	return L"\r";
#else
	return "\r";
#endif
#elif defined(__ANDROID__)	// ToDo
#ifdef UNICODE
	return L"\n";
#else
	return "\n";
#endif
#else
#error "unsupported os"
#endif
}
Elysium::Core::OperatingSystem Elysium::Core::Environment::OSVersion()
{
	// ToDos:
	//		- use preprocessor for different os
	//		- don't return fixed platform-id like PlatformID::WindowsDesktop (I'll just leave this in until I've decided on all values of PlatformID)
	//		- the behaviour of GetVersionEx(...) has changed with windows 8.1 -> make sure to handle everything correctly
	// https://www.codeproject.com/Articles/678606/Part1-Overcoming-Windows-8-1s-deprecation-of-GetVe
	// https://blog.yaakov.online/finding-operating-system-version/

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
