/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSACCESS
#include "ProcessAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
	
	#ifndef _INC_TOOLHELP32
	#include <tlhelp32.h>
	#endif

	#ifndef _PSAPI_H_
	#include <Psapi.h>
	#endif
#endif

namespace Elysium::Core::Template::Diagnostics
{
	class Process
	{
	public:
		Process() noexcept = delete;

		Process(const Process& Source) = delete;

		Process(Process&& Right) noexcept = delete;

		~Process() = delete;
	public:
		Process& operator=(const Process& Source) = delete;

		Process& operator=(Process&& Right) noexcept = delete;
	public:
		static void* GetCurrentProcessHandle();

		static Elysium::Core::Template::System::uint32_t GetCurrentId();
	public:
		static void* GetHandle(const Elysium::Core::Template::System::uint32_t ProcessId, const ProcessAccess DesiredAccess);

		static Elysium::Core::Template::System::uint32_t GetId(void* ProcessHandle);

		static Elysium::Core::Template::Text::String<char8_t> GetName(void* ProcessHandle);

		static const bool HasExited(const Elysium::Core::Template::System::uint32_t ProcessId);
	public:
		static const bool CloseMainWindow(HWND MainWindowHandle);

		static void Kill(void* ProcessHandle, const System::uint32_t ExitCode, const bool EntireProcessTree);

		static void WaitForExit(void* ProcessHandle, const Elysium::Core::Template::System::uint32_t Milliseconds);
	public:
		static Elysium::Core::Template::Container::Vector<PROCESSENTRY32> GetProcessIds();

		static Elysium::Core::Template::Container::Vector<PROCESSENTRY32> GetProcessIdsByName(const char8_t* ProcessName, const char8_t* MachineName);

		//static Process StartViaShellExecute();

		static PROCESS_INFORMATION StartViaCreateProcess(const wchar_t* ApplicationName);

		static Elysium::Core::Template::Container::Vector<MODULEENTRY32W> GetProcessModules(const Elysium::Core::Template::System::uint32_t ProcessId);

		static void* GetMainWindowHandle(const Elysium::Core::Template::System::uint32_t ProcessId) noexcept;
	private:
		struct WindowHandleData
		{
			Elysium::Core::Template::System::uint32_t ProcessId;
			HANDLE WindowHandle;
		};

		static BOOL GetMainWindowHandleCallback(HWND WindowHandle, LPARAM Parameter) noexcept;

		static const bool IsMainWindow(HWND WindowHandle) noexcept;
	public:
		/*
		static void Inject(void* ProcessHandle, Elysium::Core::Template::System::byte* Payload, Elysium::Core::Template::System::uint32_t PayloadLength);

		static void Inject(void* ProcessHandle, const char8_t* Assembly);
		*/
	};

	inline void* Elysium::Core::Template::Diagnostics::Process::GetCurrentProcessHandle()
	{
		return GetCurrentProcess();
	}

	inline Elysium::Core::Template::System::uint32_t Elysium::Core::Template::Diagnostics::Process::GetCurrentId()
	{
		return GetCurrentProcessId();
	}

	inline void* Process::GetHandle(const Elysium::Core::Template::System::uint32_t ProcessId, const ProcessAccess DesiredAccess)
	{
		//void* Handle = OpenProcess(READ_CONTROL | PROCESS_QUERY_INFORMATION, TRUE, ProcessId);
		void* Handle = OpenProcess(static_cast<Elysium::Core::Template::System::uint32_t>(DesiredAccess), FALSE, ProcessId);
		if (Handle == INVALID_HANDLE_VALUE)
		{
			throw Exceptions::SystemException();
		}

		return Handle;
	}

	inline Elysium::Core::Template::System::uint32_t Elysium::Core::Template::Diagnostics::Process::GetId(void* ProcessHandle)
	{
		return GetProcessId(ProcessHandle);
	}

	inline Elysium::Core::Template::Text::String<char8_t> Process::GetName(void* ProcessHandle)
	{
		// @ToDo: windows max module-(file-?)name length?
		char Name[MAX_PATH];
		if (!GetModuleBaseNameA(ProcessHandle, nullptr, Name, sizeof(Name)))
		{
			throw Exceptions::SystemException();
		}

		return Text::String<char8_t>(reinterpret_cast<char8_t*>(&Name));
	}

	inline const bool Elysium::Core::Template::Diagnostics::Process::HasExited(const Elysium::Core::Template::System::uint32_t ProcessId)
	{
		void* ProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION | SYNCHRONIZE, FALSE, ProcessId);
		if (ProcessHandle == INVALID_HANDLE_VALUE)
		{
			return true;
		}

		DWORD ExitCode;
		if (!GetExitCodeProcess(ProcessHandle, &ExitCode))
		{
			CloseHandle(ProcessHandle);
			throw Exceptions::SystemException();
		}

		CloseHandle(ProcessHandle);
		return ExitCode != STILL_ACTIVE;
	}

	inline const bool Process::CloseMainWindow(HWND MainWindowHandle)
	{
		if (MainWindowHandle == nullptr)
		{
			return false;
		}

		if (!PostMessage(MainWindowHandle, WM_CLOSE, 0, 0))
		{
			throw Exceptions::SystemException();
		}

		return true;
	}
	
	inline void Elysium::Core::Template::Diagnostics::Process::Kill(void* ProcessHandle, const System::uint32_t ExitCode, const bool EntireProcessTree)
	{
		if (EntireProcessTree)
		{	// @ToDo:
		}

		if (!TerminateProcess(ProcessHandle, ExitCode))
		{
			throw Exceptions::SystemException();
		}
	}

	inline void Elysium::Core::Template::Diagnostics::Process::WaitForExit(void* ProcessHandle, const Elysium::Core::Template::System::uint32_t Milliseconds)
	{
		DWORD Result = WaitForSingleObject(ProcessHandle, Milliseconds);
	}
	
	inline Elysium::Core::Template::Container::Vector<PROCESSENTRY32> Process::GetProcessIds()
	{
		HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD, 0);
		if (SnapshotHandle == INVALID_HANDLE_VALUE)
		{
			throw Exceptions::SystemException();
		}

		PROCESSENTRY32 ProcessEntry = PROCESSENTRY32();
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(SnapshotHandle, &ProcessEntry))
		{
			CloseHandle(SnapshotHandle);
			throw Exceptions::SystemException();
		}

		Container::Vector<PROCESSENTRY32> Processes = Container::Vector<PROCESSENTRY32>();
		do
		{
			Processes.PushBack(ProcessEntry);
		} while (Process32Next(SnapshotHandle, &ProcessEntry));

		CloseHandle(SnapshotHandle);

		return Processes;
	}

	inline Elysium::Core::Template::Container::Vector<PROCESSENTRY32> Process::GetProcessIdsByName(const char8_t* ProcessName, const char8_t* MachineName)
	{
		HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD, 0);
		if (SnapshotHandle == INVALID_HANDLE_VALUE)
		{
			throw Exceptions::SystemException();
		}

		PROCESSENTRY32 ProcessEntry = PROCESSENTRY32();
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(SnapshotHandle, &ProcessEntry))
		{
			CloseHandle(SnapshotHandle);
			throw Exceptions::SystemException();
		}

		Container::Vector<PROCESSENTRY32> Processes = Container::Vector<PROCESSENTRY32>();
		do
		{
			Text::String<char8_t> CurrentProcessName =
				Text::Unicode::Utf16::FromSafeWideString<char8_t>(&ProcessEntry.szExeFile[0], Text::CharacterTraits<wchar_t>::GetLength(&ProcessEntry.szExeFile[0]));
			if (CurrentProcessName == ProcessName)
			{
				Processes.PushBack(ProcessEntry);
			}
		} while (Process32Next(SnapshotHandle, &ProcessEntry));
		
		CloseHandle(SnapshotHandle);

		return Processes;
	}

	inline PROCESS_INFORMATION Process::StartViaCreateProcess(const wchar_t* ApplicationName)
	{
		STARTUPINFO StartupInfo = STARTUPINFO();
		ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
		StartupInfo.cb = sizeof(STARTUPINFO);
		StartupInfo.dwFlags = 0;

		PROCESS_INFORMATION ProcessInformation = PROCESS_INFORMATION();
		//ZeroMemory(&ProcessInformation, sizeof(PROCESS_INFORMATION));
		/*
		if (!CreateProcessWithLogonW(nullptr, nullptr, nullptr, 0, ApplicationName, nullptr, 0,
			nullptr, nullptr, &StartupInfo, &ProcessInformation))
		{
			throw Template::Exceptions::SystemException();
		}
		*/

		if (!CreateProcessW(ApplicationName,
			nullptr,        // Command line arguments
			nullptr,        // Process handle not inheritable
			nullptr,		// Thread handle not inheritable
			TRUE,			// Set handle inheritance to TRUE
			0,              // No creation flags
			nullptr,		// Use parent's environment block
			nullptr,		// Use parent's starting directory 
			&StartupInfo, &ProcessInformation))
		{
			throw Template::Exceptions::SystemException();
		}

		//WaitForSingleObject(ProcessInformation.hProcess, INFINITE);
		CloseHandle(ProcessInformation.hThread);
		CloseHandle(ProcessInformation.hProcess);

		return ProcessInformation;

		//return Process(u8"", _LocalMachineName, false, ProcessInformation.dwProcessId);
	}

	inline Elysium::Core::Template::Container::Vector<MODULEENTRY32W> Process::GetProcessModules(const Elysium::Core::Template::System::uint32_t ProcessId)
	{
		Elysium::Core::Template::Container::Vector<MODULEENTRY32W> Result =
			Elysium::Core::Template::Container::Vector<MODULEENTRY32W>();

		void* ProcessHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);
		if (ProcessHandle == INVALID_HANDLE_VALUE)
		{
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		MODULEENTRY32W ModuleEntry;
		ZeroMemory(&ModuleEntry, sizeof(ModuleEntry));
		ModuleEntry.dwSize = sizeof(MODULEENTRY32W);
		if (!Module32FirstW(ProcessHandle, &ModuleEntry))
		{
			CloseHandle(ProcessHandle);
			throw Elysium::Core::Template::Exceptions::SystemException();
		}

		do
		{
			Result.PushBack(ModuleEntry);
		} while (Module32NextW(ProcessHandle, &ModuleEntry));

		CloseHandle(ProcessHandle);

		return Result;
	}
	
	inline void* Elysium::Core::Template::Diagnostics::Process::GetMainWindowHandle(const System::uint32_t ProcessId) noexcept
	{
		WindowHandleData HandleData = WindowHandleData();
		HandleData.ProcessId = ProcessId;
		HandleData.WindowHandle = nullptr;
		while (EnumWindows(GetMainWindowHandleCallback, reinterpret_cast<LPARAM>(&HandleData)))
		{ }

		return HandleData.WindowHandle;
	}

	inline BOOL Elysium::Core::Template::Diagnostics::Process::GetMainWindowHandleCallback(HWND WindowHandle, LPARAM Parameter) noexcept
	{
		WindowHandleData* HandleData = reinterpret_cast<WindowHandleData*>(Parameter);

		DWORD ProcessId;
		GetWindowThreadProcessId(WindowHandle, &ProcessId);
		if (HandleData->ProcessId != ProcessId || !IsMainWindow(WindowHandle))
		{
			return TRUE;
		}

		HandleData->WindowHandle = WindowHandle;
		return FALSE;
	}

	inline const bool Elysium::Core::Template::Diagnostics::Process::IsMainWindow(HWND WindowHandle) noexcept
	{
		return GetWindow(WindowHandle, GW_OWNER) == (HWND)0 && IsWindowVisible(WindowHandle);
	}
}
#endif
