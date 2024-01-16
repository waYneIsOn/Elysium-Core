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

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSMODULE
#include "ProcessModule.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSSTARTINFO
#include "ProcessStartInfo.hpp"
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

		static Elysium::Core::Template::System::uint32_t GetCurrentProcessId();
	public:
		static void* GetHandle(const Elysium::Core::Template::System::uint32_t ProcessId);

		static Elysium::Core::Template::System::uint32_t GetId(void* ProcessHandle);

		static Elysium::Core::Template::Text::String<char8_t> GetName(void* ProcessHandle);

		static const bool HasExited(void* ProcessHandle);
	public:
		static const bool CloseMainWindow(const System::uint32_t ProcessId);

		static void Kill(void* ProcessHandle, const System::uint32_t ExitCode, const bool EntireProcessTree);

		static void WaitForExit(void* ProcessHandle, const Elysium::Core::Template::System::uint32_t Milliseconds);
	public:
		static Elysium::Core::Template::Container::Vector<PROCESSENTRY32> GetProcessIds();

		static Elysium::Core::Template::Container::Vector<PROCESSENTRY32> GetProcessIdsByName(const char8_t* ProcessName, const char8_t* MachineName);
	private:

	};

	inline void* Elysium::Core::Template::Diagnostics::Process::GetCurrentProcessHandle()
	{
		return GetCurrentProcess();
	}

	inline Elysium::Core::Template::System::uint32_t Elysium::Core::Template::Diagnostics::Process::GetCurrentProcessId()
	{
		//return GetCurrentProcessId();	// @ToDo: can I somehow use this directly here? (Psapi.h)
		return GetId(GetCurrentProcessHandle());
	}

	inline void* Process::GetHandle(const Elysium::Core::Template::System::uint32_t ProcessId)
	{
		void* Handle = OpenProcess(READ_CONTROL | PROCESS_QUERY_INFORMATION, TRUE, ProcessId);
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

	inline const bool Elysium::Core::Template::Diagnostics::Process::HasExited(void* ProcessHandle)
	{
		DWORD ExitCode;
		if (!GetExitCodeProcess(ProcessHandle, &ExitCode))
		{
			throw Exceptions::SystemException();
		}

		return ExitCode != STILL_ACTIVE;
	}

	inline const bool Process::CloseMainWindow(const System::uint32_t ProcessId)
	{
		//@ ToDo:
		/*
		const HANDLE MainWindowHandle = GetMainWindowHandle(ProcessId);
		if (MainWindowHandle == nullptr)
		{	// no main window found, ergo there is nothing to do, so simply return true
			return true;
		}
		else
		{
			return CloseWindow(reinterpret_cast<HWND>(MainWindowHandle)) != FALSE;
			//return DestroyWindow(reinterpret_cast<HWND>(MainWindowHandle)) != FALSE;
		}
		*/
		return false;
	}
	
	inline void Elysium::Core::Template::Diagnostics::Process::Kill(void* ProcessHandle, const System::uint32_t ExitCode, const bool EntireProcessTree)
	{
		if (EntireProcessTree)
		{	// @ToDo:
		}
		TerminateProcess(ProcessHandle, ExitCode);
	}

	inline void Elysium::Core::Template::Diagnostics::Process::WaitForExit(void* ProcessHandle, const Elysium::Core::Template::System::uint32_t Milliseconds)
	{
		WaitForSingleObject(ProcessHandle, Milliseconds);
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
			throw Exceptions::SystemException();
		}

		Container::Vector<PROCESSENTRY32> Processes = Container::Vector<PROCESSENTRY32>();
		while (Process32Next(SnapshotHandle, &ProcessEntry))
		{
			Processes.PushBack(ProcessEntry);
		}
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
			throw Exceptions::SystemException();
		}

		Container::Vector<PROCESSENTRY32> Processes = Container::Vector<PROCESSENTRY32>();
		while (Process32Next(SnapshotHandle, &ProcessEntry))
		{
			Text::String<char8_t> CurrentProcessName =
				Text::Unicode::Utf16::FromSafeWideString<char8_t>(&ProcessEntry.szExeFile[0], Text::CharacterTraits<wchar_t>::GetLength(&ProcessEntry.szExeFile[0]));
			if (CurrentProcessName == ProcessName)
			{
				Processes.PushBack(ProcessEntry);
			}
		}
		CloseHandle(SnapshotHandle);

		return Processes;
	}

}
#endif
