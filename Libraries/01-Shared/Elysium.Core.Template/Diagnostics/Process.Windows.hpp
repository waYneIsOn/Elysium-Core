/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS	
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSACCESS
#include "ProcessAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Text/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Text/Unicode/Utf16.hpp"
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#ifndef _INC_TOOLHELP32
#include <tlhelp32.h>
#endif

#ifndef _PSAPI_H_
#include <Psapi.h>
#endif

namespace Elysium::Core::Template::Diagnostics
{
	class Process
	{
	public:
		constexpr Process() noexcept = delete;

		Process(const Process& Source) = delete;

		Process(Process&& Right) noexcept = delete;

		constexpr ~Process() = delete;
	public:
		Process& operator=(const Process& Source) = delete;

		Process& operator=(Process&& Right) noexcept = delete;
	public:
		inline static void* GetCurrentProcessHandle()
		{
			return GetCurrentProcess();
		}

		inline static Elysium::Core::Template::System::uint32_t GetCurrentId()
		{
			return GetCurrentProcessId();
		}
	public:
		inline static void* GetHandle(const Elysium::Core::Template::System::uint32_t ProcessId, const ProcessAccess DesiredAccess)
		{
			//void* Handle = OpenProcess(READ_CONTROL | PROCESS_QUERY_INFORMATION, TRUE, ProcessId);
			void* Handle = OpenProcess(static_cast<Elysium::Core::Template::System::uint32_t>(DesiredAccess), FALSE, ProcessId);
			if (Handle == INVALID_HANDLE_VALUE)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Handle;
		}

		inline static Elysium::Core::Template::System::uint32_t GetId(void* ProcessHandle)
		{
			return GetProcessId(ProcessHandle);
		}

		inline static Elysium::Core::Template::Text::String<char8_t> GetName(void* ProcessHandle)
		{
			// @ToDo: windows max module-(file-?)name length?
			char Name[MAX_PATH];
			if (!GetModuleBaseNameA(ProcessHandle, nullptr, Name, sizeof(Name)))
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Text::String<char8_t>(reinterpret_cast<char8_t*>(&Name));
		}

		inline static const bool HasExited(const Elysium::Core::Template::System::uint32_t ProcessId)
		{
			void* ProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION | SYNCHRONIZE, FALSE, ProcessId);
			if (ProcessHandle == INVALID_HANDLE_VALUE)
			{
				return true;
			}

			DWORD WaitResult = WaitForSingleObject(ProcessHandle, 0);
			if (WaitResult == WAIT_ABANDONED)
			{
				CloseHandle(ProcessHandle);
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
			else if (WaitResult != WAIT_TIMEOUT)
			{
				DWORD ExitCode;
				if (!GetExitCodeProcess(ProcessHandle, &ExitCode))
				{
					CloseHandle(ProcessHandle);
					throw Elysium::Core::Template::Exceptions::SystemException();
				}

				CloseHandle(ProcessHandle);
				return ExitCode != STILL_ACTIVE;
			}

			CloseHandle(ProcessHandle);

			return true;
		}
	public:
		inline static const bool CloseMainWindow(HWND MainWindowHandle)
		{
			if (MainWindowHandle == nullptr)
			{
				return false;
			}

			if (!PostMessage(MainWindowHandle, WM_CLOSE, 0, 0))
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return true;
		}

		inline static void Kill(void* ProcessHandle, const System::uint32_t ExitCode, const bool EntireProcessTree)
		{
			if (EntireProcessTree)
			{	// @ToDo:
			}

			if (!TerminateProcess(ProcessHandle, ExitCode))
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}

		inline static void WaitForExit(void* ProcessHandle, const Elysium::Core::Template::System::uint32_t Milliseconds)
		{
			DWORD Result = WaitForSingleObject(ProcessHandle, Milliseconds);
			if (Result != WAIT_OBJECT_0)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}
		}
	public:
		inline static Elysium::Core::Template::Container::Vector<PROCESSENTRY32> GetProcessIds()
		{
			HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (SnapshotHandle == INVALID_HANDLE_VALUE)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			PROCESSENTRY32 ProcessEntry = PROCESSENTRY32();
			ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
			if (!Process32First(SnapshotHandle, &ProcessEntry))
			{
				CloseHandle(SnapshotHandle);
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			Container::Vector<PROCESSENTRY32> Processes = Container::Vector<PROCESSENTRY32>();
			do
			{
				Processes.PushBack(ProcessEntry);
			} while (Process32Next(SnapshotHandle, &ProcessEntry));

			CloseHandle(SnapshotHandle);

			return Processes;
		}

		inline static Elysium::Core::Template::Container::Vector<PROCESSENTRY32> GetProcessIdsByName(const char8_t* ProcessName, const char8_t* MachineName)
		{
			HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (SnapshotHandle == INVALID_HANDLE_VALUE)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			PROCESSENTRY32 ProcessEntry = PROCESSENTRY32();
			ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
			if (!Process32First(SnapshotHandle, &ProcessEntry))
			{
				CloseHandle(SnapshotHandle);
				throw Elysium::Core::Template::Exceptions::SystemException();
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

		//inline static Process StartViaShellExecute();

		inline static PROCESS_INFORMATION StartViaCreateProcess(const wchar_t* ApplicationName)
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

			CloseHandle(ProcessInformation.hThread);
			CloseHandle(ProcessInformation.hProcess);

			return ProcessInformation;
		}

		inline static Elysium::Core::Template::Container::Vector<MODULEENTRY32W> GetProcessModules(const Elysium::Core::Template::System::uint32_t ProcessId)
		{
			Elysium::Core::Template::Container::Vector<MODULEENTRY32W> Result =
				Elysium::Core::Template::Container::Vector<MODULEENTRY32W>();

			void* ProcessHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);
			if (ProcessHandle == INVALID_HANDLE_VALUE)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			MODULEENTRY32W ModuleEntry;
			ZeroMemory(&ModuleEntry, sizeof(MODULEENTRY32W));
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

		inline static Elysium::Core::Template::Container::Vector<THREADENTRY32> GetProcessThreads(const Elysium::Core::Template::System::uint32_t ProcessId)
		{
			Elysium::Core::Template::Container::Vector<THREADENTRY32> Result =
				Elysium::Core::Template::Container::Vector<THREADENTRY32>();

			void* ProcessHandle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, ProcessId);
			if (ProcessHandle == INVALID_HANDLE_VALUE)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			THREADENTRY32 ThreadEntry;
			ZeroMemory(&ThreadEntry, sizeof(THREADENTRY32));
			ThreadEntry.dwSize = sizeof(THREADENTRY32);
			if (!Thread32First(ProcessHandle, &ThreadEntry))
			{
				CloseHandle(ProcessHandle);
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			do
			{
				Result.PushBack(ThreadEntry);
			} while (Thread32Next(ProcessHandle, &ThreadEntry));

			CloseHandle(ProcessHandle);

			return Result;
		}

		inline static void* GetMainWindowHandle(const Elysium::Core::Template::System::uint32_t ProcessId) noexcept
		{
			WindowHandleData HandleData = WindowHandleData();
			HandleData.ProcessId = ProcessId;
			HandleData.WindowHandle = nullptr;
			while (EnumWindows(GetMainWindowHandleCallback, reinterpret_cast<LPARAM>(&HandleData)))
			{
			}

			return HandleData.WindowHandle;
		}
	private:
		struct WindowHandleData
		{
			Elysium::Core::Template::System::uint32_t ProcessId;
			HWND WindowHandle;
		};

		inline static BOOL GetMainWindowHandleCallback(HWND WindowHandle, LPARAM Parameter) noexcept
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

		inline static const bool IsMainWindow(HWND WindowHandle) noexcept
		{
			return GetWindow(WindowHandle, GW_OWNER) == (HWND)0 && IsWindowVisible(WindowHandle);
		}
	public:
		/*
		inline static void Inject(void* ProcessHandle, Elysium::Core::Template::System::byte* Payload, Elysium::Core::Template::System::uint32_t PayloadLength);

		inline static void Inject(void* ProcessHandle, const char8_t* Assembly);
		*/
	};
}
#endif
#endif
