#include "Environment.hpp"

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
#endif

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _THREAD_
#include <thread>
#endif

#if defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
const Elysium::Core::String Elysium::Core::Environment::_NewLineCharacters = Elysium::Core::String(u"\r\n");
#elif defined(UNIX)	// ToDo
const Elysium::Core::String Elysium::Core::Environment::_NewLineCharacters = Elysium::Core::String(u"\n");
#elif defined(PREOSX_MAC)	// ToDo
const Elysium::Core::String Elysium::Core::Environment::_NewLineCharacters = Elysium::Core::String(u"\r");
#elif defined(__ANDROID__)	// ToDo
const Elysium::Core::String Elysium::Core::Environment::_NewLineCharacters = Elysium::Core::String(u"\n");
#else
#error "unsupported os"
#endif

Elysium::Core::Environment::~Environment()
{
}

constexpr const bool Elysium::Core::Environment::Is64BitProcess()
{
#ifdef _WIN64 || __x86_64__ || __ppc64__
	return true;
#else
	return false;
#endif
}

const Elysium::Core::String Elysium::Core::Environment::MachineName()
{
	wchar_t MachineName[4096];	// TCHAR
	unsigned long BufferCount = 4096;	// DWORD
	if (GetComputerName(MachineName, &BufferCount))
	{
		//return MachineName;
		return String(u"not implemented");
	}
	else
	{
		throw InvalidOperationException(String(u"The name of this computer cannot be obtained."));
	}
}
const Elysium::Core::String & Elysium::Core::Environment::NewLine()
{
	return _NewLineCharacters;
}
const Elysium::Core::OperatingSystem Elysium::Core::Environment::OSVersion()
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
		throw InvalidOperationException(u"This property was unable to obtain the system version.");
	}
}
const uint32_t Elysium::Core::Environment::ProcessorCount()
{
	/*
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	*/
	return std::thread::hardware_concurrency();
}
const Elysium::Core::String Elysium::Core::Environment::UserName()
{
	wchar_t UserName[4096];	// TCHAR
	unsigned long BufferCount = 4096;	// DWORD
	if (GetUserName(UserName, &BufferCount))
	{
		//return UserName;
		return u"not implemented";
	}
	else
	{
		throw InvalidOperationException(u"This property was unable to obtain the user name.");
	}
}
const Elysium::Core::String Elysium::Core::Environment::SystemDirectory()
{
	wchar_t SystemDirectory[4096];	// TCHAR
	unsigned long BufferCount = 4096;	// DWORD
	if (GetSystemDirectory(SystemDirectory, BufferCount))
	{
		//return SystemDirectory;
		return u"not implemented";
	}
	else
	{
		throw InvalidOperationException(u"This property was unable to obtain the system directory.");
	}
}

Elysium::Core::Environment::Environment()
{
}
