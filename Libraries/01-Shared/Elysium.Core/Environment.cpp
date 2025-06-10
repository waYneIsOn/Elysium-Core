#include "Environment.hpp"

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF8ENCODING
#include "UTF8Encoding.hpp"
#endif

#ifndef _THREAD_
#include <thread>
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN	// exclude cryptography, dde, rpc, shell, winsock and other apis
#include <Windows.h>
#endif
#endif

const Elysium::Core::Utf8String Elysium::Core::Environment::CurrentDirectory()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	wchar_t CurrentDirectory[MAX_PATH];
	DWORD Length = GetCurrentDirectoryW(MAX_PATH, &CurrentDirectory[0]);

	if (Length == 0 || Length >= MAX_PATH)
	{	// @ToDo: use long path functionality (got to figure out which one exactly)
		throw SystemException();
	}

	return _InternalEncoding.GetString(reinterpret_cast<Elysium::Core::Template::System::byte*>(&CurrentDirectory), Length * sizeof(wchar_t));
#else
#error "unsupported os"
#endif
}

void Elysium::Core::Environment::CurrentDirectory(const Elysium::Core::Utf8String::ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length)
{
	if (Length >= MAX_PATH)
	{
		bool bla = false;
	}

	Elysium::Core::Container::VectorOfByte Bytes = _InternalEncoding.GetBytes(&Value[0], Length,
		sizeof(Elysium::Core::Utf16String::ConstCharacter));

	Elysium::Core::Utf8String Test = _InternalEncoding.GetString(&Bytes[0], Bytes.GetLength());

	BOOL Result = SetCurrentDirectoryW(reinterpret_cast<wchar_t*>(&Bytes[0]));
	if (Result == FALSE)
	{	// @ToDo: use long path functionality (got to figure out which one exactly)
		throw SystemException();
	}
}

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
	// https://docs.microsoft.com/en-GB/troubleshoot/windows-server/identity/naming-conventions-for-computer-domain-site-ou
	wchar_t MachineName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD BufferCount = sizeof(MachineName) / sizeof(wchar_t);

	if (!GetComputerName(MachineName, &BufferCount))
	{
		throw SystemException();
	}

	return _InternalEncoding.GetString(reinterpret_cast<Elysium::Core::byte*>(&MachineName), BufferCount * sizeof(wchar_t));
#else
#error "unsupported os"
#endif
}

const Elysium::Core::OperatingSystem Elysium::Core::Environment::OSVersion()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	// // https://learn.microsoft.com/en-us/windows/win32/api/versionhelpers/
	static DWORDLONG const dwlConditionMask = VerSetConditionMask(
		VerSetConditionMask(
			VerSetConditionMask(
				0, VER_MAJORVERSION, VER_GREATER_EQUAL),
			VER_MINORVERSION, VER_GREATER_EQUAL),
		VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

	OSVERSIONINFOEXW VersionInfo = { sizeof(VersionInfo), 0, 0, 0, 0, {0}, 0, 0, 0, VER_NT_WORKSTATION };
	BOOL VerifyInfoResult = FALSE;
	/*
	VersionInfo.dwMajorVersion = Elysium::Core::Template::Numeric::NumericTraits<WORD>::Maximum;
	VersionInfo.dwMinorVersion = Elysium::Core::Template::Numeric::NumericTraits<WORD>::Maximum;;
	if ((VerifyInfoResult = VerifyVersionInfoW(&VersionInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask)) == TRUE)
	{
		return OperatingSystem(VersionInfo.wProductType == VER_NT_WORKSTATION ? PlatformID::WindowsDesktop : PlatformID::WindowsServer,
			Version(
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMajorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMinorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwBuildNumber)));
	}
	*/
	VersionInfo.dwMajorVersion = HIBYTE(_WIN32_WINNT_WINTHRESHOLD);
	VersionInfo.dwMinorVersion = LOBYTE(_WIN32_WINNT_WINTHRESHOLD);
	if ((VerifyInfoResult = VerifyVersionInfoW(&VersionInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask)) == TRUE)
	{
		return OperatingSystem(VersionInfo.wProductType == VER_NT_WORKSTATION ? PlatformID::WindowsDesktop : PlatformID::WindowsServer,
			Version(
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMajorVersion), 
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMinorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwBuildNumber)));
	}

	VersionInfo.dwMajorVersion = HIBYTE(_WIN32_WINNT_WINBLUE);
	VersionInfo.dwMinorVersion = LOBYTE(_WIN32_WINNT_WINBLUE);
	if ((VerifyInfoResult = VerifyVersionInfoW(&VersionInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask)) == TRUE)
	{
		return OperatingSystem(VersionInfo.wProductType == VER_NT_WORKSTATION ? PlatformID::WindowsDesktop : PlatformID::WindowsServer,
			Version(
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMajorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMinorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwBuildNumber)));
	}

	VersionInfo.dwMajorVersion = HIBYTE(_WIN32_WINNT_WIN8);
	VersionInfo.dwMinorVersion = LOBYTE(_WIN32_WINNT_WIN8);
	if ((VerifyInfoResult = VerifyVersionInfoW(&VersionInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask)) == TRUE)
	{
		return OperatingSystem(VersionInfo.wProductType == VER_NT_WORKSTATION ? PlatformID::WindowsDesktop : PlatformID::WindowsServer,
			Version(
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMajorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMinorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwBuildNumber)));
	}

	VersionInfo.dwMajorVersion = HIBYTE(_WIN32_WINNT_WIN7);
	VersionInfo.dwMinorVersion = LOBYTE(_WIN32_WINNT_WIN7);
	if ((VerifyInfoResult = VerifyVersionInfoW(&VersionInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask)) == TRUE)
	{
		return OperatingSystem(VersionInfo.wProductType == VER_NT_WORKSTATION ? PlatformID::WindowsDesktop : PlatformID::WindowsServer,
			Version(
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMajorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMinorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwBuildNumber)));
	}

	VersionInfo.dwMajorVersion = HIBYTE(_WIN32_WINNT_VISTA);
	VersionInfo.dwMinorVersion = LOBYTE(_WIN32_WINNT_VISTA);
	if ((VerifyInfoResult = VerifyVersionInfoW(&VersionInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask)) == TRUE)
	{
		return OperatingSystem(VersionInfo.wProductType == VER_NT_WORKSTATION ? PlatformID::WindowsDesktop : PlatformID::WindowsServer,
			Version(
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMajorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMinorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwBuildNumber)));
	}

	VersionInfo.dwMajorVersion = HIBYTE(_WIN32_WINNT_WINXP);
	VersionInfo.dwMinorVersion = LOBYTE(_WIN32_WINNT_WINXP);
	if ((VerifyInfoResult = VerifyVersionInfoW(&VersionInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask)) == TRUE)
	{
		return OperatingSystem(VersionInfo.wProductType == VER_NT_WORKSTATION ? PlatformID::WindowsDesktop : PlatformID::WindowsServer,
			Version(
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMajorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwMinorVersion),
				static_cast<Elysium::Core::uint16_t>(VersionInfo.dwBuildNumber)));
	}
#else
#error "unsupported os"
#endif

	return OperatingSystem(PlatformID::Unknown, Version(0, 0, 0));
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
		throw SystemException();
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
	Elysium::Core::uint32_t Length = GetSystemDirectory(SystemDirectory, BufferCount);
	if (Length > 0)
	{
		return _InternalEncoding.GetString((byte*)&SystemDirectory, Length * sizeof(wchar_t));
	}
	else
	{
		throw SystemException();
	}
#else
#error "unsupported os"
#endif
}
