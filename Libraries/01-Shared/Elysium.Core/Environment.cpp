#include "Environment.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef _THREAD_
#include <thread>
#endif

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
const Elysium::Core::String Elysium::Core::Environment::_NewLineCharacters = Elysium::Core::String(u8"\r\n");
#elif defined(ELYSIUM_CORE_OS_ANDROID)
const Elysium::Core::String Elysium::Core::Environment::_NewLineCharacters = Elysium::Core::String(u8"\n");
#elif defined(ELYSIUM_CORE_OS_LINUX)
const Elysium::Core::String Elysium::Core::Environment::_NewLineCharacters = Elysium::Core::String(u8"\n");
#elif defined(ELYSIUM_CORE_OS_MAC)
const Elysium::Core::String Elysium::Core::Environment::_NewLineCharacters = Elysium::Core::String(u8"\r");
#else
#error "unsupported os"
#endif

constexpr const bool Elysium::Core::Environment::Is64BitProcess()
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

const Elysium::Core::String Elysium::Core::Environment::MachineName()
{
	wchar_t MachineName[4096];	// TCHAR
	unsigned long BufferCount = 4096;	// DWORD
	if (GetComputerName(MachineName, &BufferCount))
	{
		const Elysium::Core::Text::Encoding& UTF16BE = Elysium::Core::Text::Encoding::UTF16BE();
		return UTF16BE.GetString((byte*)&MachineName, BufferCount);
	}
	else
	{
		throw InvalidOperationException(u8"The name of this computer cannot be obtained.");
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
		throw InvalidOperationException(u8"This property was unable to obtain the system version.");
	}
}
const Elysium::Core::uint32_t Elysium::Core::Environment::ProcessorCount()
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
		const Elysium::Core::Text::Encoding& UTF16BE = Elysium::Core::Text::Encoding::UTF16BE();
		return UTF16BE.GetString((byte*)&UserName, BufferCount);
	}
	else
	{
		throw InvalidOperationException(u8"This property was unable to obtain the user name.");
	}
}
const Elysium::Core::String Elysium::Core::Environment::SystemDirectory()
{
	wchar_t SystemDirectory[4096];	// TCHAR
	unsigned long BufferCount = 4096;	// DWORD
	if (GetSystemDirectory(SystemDirectory, BufferCount))
	{
		const Elysium::Core::Text::Encoding& UTF16BE = Elysium::Core::Text::Encoding::UTF16BE();
		return UTF16BE.GetString((byte*)&SystemDirectory, BufferCount);
	}
	else
	{
		throw InvalidOperationException(u8"This property was unable to obtain the system directory.");
	}
}

