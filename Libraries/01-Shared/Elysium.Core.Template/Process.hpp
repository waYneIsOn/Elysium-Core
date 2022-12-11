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

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSSTARTINFO
#include "ProcessStartInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTEXCEPTION
#include "ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTNULLEXCEPTION
#include "ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
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
#endif

namespace Elysium::Core::Template::Diagnostics
{
	class Process final
	{
	public:
		Process(const char8_t* MachineName, const bool IsRemoteMachine, const System::uint32_t ProcessId) noexcept;
	public:
		Process() noexcept;

		Process(const Process& Source);

		Process(Process&& Right) noexcept;

		~Process();
	public:
		Process& operator=(const Process& Source);

		Process& operator=(Process&& Right) noexcept;
	public:
		const bool GetHasExited() const;

		const System::uint32_t GetId() const;
	public:
		const bool Start(const ProcessStartInfo& StartInfo);

		void Close();

		const bool CloseMainWindow();

		void Kill(const bool EntireProcessTree);

		void Refresh();

		void WaitForExit(const System::uint32_t Milliseconds = 0xFFFFFFFF);
	public:
		static void EnterDebugMode();

		static void LeaveDebugMode();

		static const Process& CurrentProcess();

		static const Container::Vector<Process> GetProcesses(const char8_t* MachineName = _LocalMachineName);

		static Process GetProcessById(const System::uint32_t ProcessId);

		static const Container::Vector<Process> GetProcessesByName(const char8_t* ProcessName, const char8_t* MachineName = _LocalMachineName);
	private:
		inline static const char8_t* _LocalMachineName = u8".";

		static const Process _CurrentProcess;
	private:
		Text::String<char8_t> _MachineName;
		bool _IsRemoteMachine;
		System::uint32_t _ProcessId;
		bool _HasProcessId;
		System::uint32_t _ThreadId;
		bool _HasThreadId;
		void* _ProcessHandle;
		void* _ThreadHandle;
	private:
		struct WindowHandleData
		{
			System::uint32_t ProcessId;
			HANDLE WindowHandle;
		};

		static const HANDLE GetMainWindowHandle(const System::uint32_t ProcessId);

		static BOOL GetMainWindowHandleCallback(HWND WindowHandle, LPARAM Parameter);

		static const bool IsMainWindow(HWND WindowHandle);
	};

	inline const Elysium::Core::Template::Diagnostics::Process Process::_CurrentProcess = Process(_LocalMachineName, false, GetCurrentProcessId());

	inline Elysium::Core::Template::Diagnostics::Process::Process(const char8_t* MachineName, const bool IsRemoteMachine, const System::uint32_t ProcessId) noexcept
		: _MachineName(MachineName), _IsRemoteMachine(IsRemoteMachine), _ProcessId(ProcessId), _HasProcessId(true), _ThreadId(GetCurrentThreadId()),
		_HasThreadId(true), _ProcessHandle(GetCurrentProcess()), _ThreadHandle(GetCurrentThread())
	{ }

	inline Elysium::Core::Template::Diagnostics::Process::Process() noexcept
		: _MachineName(_LocalMachineName), _IsRemoteMachine(false), _ProcessId(0), _HasProcessId(false), _ThreadId(0), _HasThreadId(false),
		_ProcessHandle(nullptr), _ThreadHandle(nullptr)
	{ }

	inline Elysium::Core::Template::Diagnostics::Process::Process(const Process & Source)
		: _MachineName(Source._MachineName), _IsRemoteMachine(Source._IsRemoteMachine), _ProcessId(Source._ProcessId), _HasProcessId(Source._HasProcessId),
		_ThreadId(Source._ThreadId), _HasThreadId(Source._HasThreadId), _ProcessHandle(Source._ProcessHandle), _ThreadHandle(Source._ThreadHandle)
	{ }

	inline Diagnostics::Process::Process(Process&& Right) noexcept
		: _MachineName(), _IsRemoteMachine(), _ProcessId(), _HasProcessId(), _ThreadId(), _HasThreadId(), _ProcessHandle(), _ThreadHandle()
	{
		*this = Functional::Move(Right);
	}

	inline Elysium::Core::Template::Diagnostics::Process::~Process()
	{ 
		Close();
	}

	inline Elysium::Core::Template::Diagnostics::Process& Diagnostics::Process::operator=(const Process& Source)
	{
		if (this != &Source)
		{
			_MachineName = Source._MachineName;
			_IsRemoteMachine = Source._IsRemoteMachine;
			_ProcessId = Source._ProcessId;
			_HasProcessId = Source._HasProcessId;
			_ThreadId = Source._ThreadId;
			_HasThreadId = Source._HasThreadId;
			_ProcessHandle = Source._ProcessHandle;
			_ThreadHandle = Source._ThreadHandle;
		}

		return *this;
	}

	inline Elysium::Core::Template::Diagnostics::Process& Diagnostics::Process::operator=(Process&& Right) noexcept
	{
		if (this != &Right)
		{
			_MachineName = Functional::Move(Right._MachineName);
			_IsRemoteMachine = Functional::Move(Right._IsRemoteMachine);
			_ProcessId = Functional::Move(Right._ProcessId);
			_HasProcessId = Functional::Move(Right._HasProcessId);
			_ThreadId = Functional::Move(Right._ThreadId);
			_HasThreadId = Functional::Move(Right._HasThreadId);
			_ProcessHandle = Functional::Move(Right._ProcessHandle);
			_ThreadHandle = Functional::Move(Right._ThreadHandle);
			
			Right._IsRemoteMachine = false;
			Right._ProcessId = 0;
			Right._HasProcessId = false;
			Right._ThreadId = 0;
			Right._HasThreadId = false;
			Right._ProcessHandle = nullptr;
			Right._ThreadHandle = nullptr;
		}

		return *this;
	}

	inline const bool Elysium::Core::Template::Diagnostics::Process::GetHasExited() const
	{
		DWORD ExitCode;
		if (!GetExitCodeProcess(_ProcessHandle, &ExitCode))
		{
			throw Exceptions::SystemException();
		}

		return ExitCode != STILL_ACTIVE;
	}

	inline const System::uint32_t Elysium::Core::Template::Diagnostics::Process::GetId() const
	{
		if (!_HasProcessId)
		{
			throw Exceptions::InvalidOperationException();
		}

		return _ProcessId;
	}

	inline const bool Elysium::Core::Template::Diagnostics::Process::Start(const ProcessStartInfo& StartInfo)
	{
		const Text::String<char8_t>& FileName = StartInfo.GetFileName();
		const Text::String<wchar_t>& WideFileName = Text::Unicode::Utf16::SafeToWideString<char8_t>(&FileName[0], FileName.GetLength());

		STARTUPINFO StartupInfo = STARTUPINFO();
		//ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
		StartupInfo.cb = sizeof(STARTUPINFO);

		PROCESS_INFORMATION ProcessInformation = PROCESS_INFORMATION();
		//ZeroMemory(&ProcessInformation, sizeof(PROCESS_INFORMATION));

		if (!CreateProcess(&WideFileName[0],
			nullptr,        // Command line arguments
			nullptr,        // Process handle not inheritable
			nullptr,		// Thread handle not inheritable
			false,          // Set handle inheritance to FALSE
			0,              // No creation flags
			nullptr,		// Use parent's environment block
			nullptr,		// Use parent's starting directory 
			&StartupInfo, &ProcessInformation))
		{
			throw Exceptions::SystemException();
		}

		_ProcessId = ProcessInformation.dwProcessId;
		_HasProcessId = true;
		_ThreadId = ProcessInformation.dwThreadId;
		_HasThreadId = true;
		_ProcessHandle = ProcessInformation.hProcess;
		_ThreadHandle = ProcessInformation.hThread;

		return true;
	}

	inline void Elysium::Core::Template::Diagnostics::Process::Close()
	{
		if (_ThreadHandle != nullptr)
		{
			CloseHandle(_ThreadHandle);
			_ThreadHandle = nullptr;
		}
		if (_ProcessHandle != nullptr)
		{
			CloseHandle(_ProcessHandle);
			_ProcessHandle = nullptr;
		}
	}
	
	inline const bool Elysium::Core::Template::Diagnostics::Process::CloseMainWindow()
	{
		const HANDLE MainWindowHandle = GetMainWindowHandle(_ProcessId);
		if (MainWindowHandle == nullptr)
		{	// no main window found, ergo there is nothing to do, so simply return true
			return true;
		}
		else
		{
			return CloseWindow((HWND)MainWindowHandle) == 1;
		}
	}
	
	inline void Elysium::Core::Template::Diagnostics::Process::Kill(const bool EntireProcessTree)
	{
		if (EntireProcessTree)
		{	// ToDo:
			throw 1;
		}
		TerminateProcess(_ProcessHandle, 0);
	}

	inline void Diagnostics::Process::Refresh()
	{	// ToDo:
		throw 1;
	}

	inline void Diagnostics::Process::WaitForExit(const System::uint32_t Milliseconds)
	{
		WaitForSingleObject(_ProcessHandle, Milliseconds);
	}

	inline void Diagnostics::Process::EnterDebugMode()
	{
		//EnableDebugPriv();
		throw 1;
	}

	inline void Elysium::Core::Template::Diagnostics::Process::LeaveDebugMode()
	{
		//LeaveDebugPriv();
		throw 1;
	}

	inline const Process& Elysium::Core::Template::Diagnostics::Process::CurrentProcess()
	{
		return _CurrentProcess;
	}
	
	inline const Container::Vector<Process> Elysium::Core::Template::Diagnostics::Process::GetProcesses(const char8_t* MachineName)
	{
		HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (SnapshotHandle == INVALID_HANDLE_VALUE)
		{
			throw Exceptions::SystemException();
		}

		// ...
		PROCESSENTRY32 ProcessEntry = PROCESSENTRY32();
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

		Container::Vector<Process> Processes = Container::Vector<Process>();
		while (Process32Next(SnapshotHandle, &ProcessEntry))
		{
			Processes.PushBack(Process(MachineName, MachineName == _LocalMachineName, ProcessEntry.th32ProcessID));
		}
		CloseHandle(SnapshotHandle);

		return Processes;
	}
	
	inline Elysium::Core::Template::Diagnostics::Process Elysium::Core::Template::Diagnostics::Process::GetProcessById(const System::uint32_t ProcessId)
	{
		HANDLE ProcessHandle = OpenProcess(READ_CONTROL | PROCESS_QUERY_INFORMATION, true, ProcessId);
		if (ProcessHandle == nullptr)
		{
			throw Exceptions::ArgumentException(u8"The process specified by the ProcessId parameter is not running. The identifier might be expired.");
		}
		/*
		if ()
		{
			throw InvalidOperationException(u8"The process was not started by this object.");
		}
		*/
		/*
		MEMORY_PRIORITY_INFORMATION MemoryPriorityInformation = MEMORY_PRIORITY_INFORMATION();
		if (!GetProcessInformation(ProcessHandle, PROCESS_INFORMATION_CLASS::ProcessMemoryPriority, &MemoryPriorityInformation, sizeof(MEMORY_PRIORITY_INFORMATION)))
		{
			throw 1;
		}
		*/
		// ToDo:
		throw 1;
	}
	
	inline const Container::Vector<Process> Elysium::Core::Template::Diagnostics::Process::GetProcessesByName(const char8_t* ProcessName, const char8_t* MachineName)
	{
		if (Text::CharacterTraits<char8_t>::IsEmpty(ProcessName))
		{
			throw Exceptions::ArgumentNullException(u8"ProcessName");
		}

		HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (SnapshotHandle == INVALID_HANDLE_VALUE)
		{
			throw Exceptions::SystemException();
		}

		// ...
		PROCESSENTRY32 ProcessEntry = PROCESSENTRY32();
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

		Container::Vector<Process> Processes = Container::Vector<Process>();
		while (Process32Next(SnapshotHandle, &ProcessEntry))
		{
			Text::String<char8_t> CurrentProcessName =
				Text::Unicode::Utf16::FromSafeWideString<char8_t>(&ProcessEntry.szExeFile[0], Text::CharacterTraits<wchar_t>::GetLength(&ProcessEntry.szExeFile[0]));
			if (CurrentProcessName == ProcessName)
			{
				Processes.PushBack(Process(MachineName, MachineName == _LocalMachineName, ProcessEntry.th32ProcessID));
			}
		}
		CloseHandle(SnapshotHandle);

		return Processes;
	}
	
	inline const HANDLE Elysium::Core::Template::Diagnostics::Process::GetMainWindowHandle(const System::uint32_t ProcessId)
	{
		WindowHandleData HandleData = WindowHandleData();
		HandleData.ProcessId = ProcessId;
		HandleData.WindowHandle = nullptr;
		while (EnumWindows(GetMainWindowHandleCallback, (LPARAM)&HandleData))
		{ }

		return HandleData.WindowHandle;
	}

	inline BOOL Elysium::Core::Template::Diagnostics::Process::GetMainWindowHandleCallback(HWND WindowHandle, LPARAM Parameter)
	{
		WindowHandleData* HandleData = (WindowHandleData*)Parameter;

		DWORD ProcessId;
		GetWindowThreadProcessId(WindowHandle, &ProcessId);
		if (HandleData->ProcessId != ProcessId || !IsMainWindow(WindowHandle))
		{
			return TRUE;
		}

		HandleData->WindowHandle = WindowHandle;
		return FALSE;
	}

	inline const bool Elysium::Core::Template::Diagnostics::Process::IsMainWindow(HWND WindowHandle)
	{
		return GetWindow(WindowHandle, GW_OWNER) == (HWND)0 && IsWindowVisible(WindowHandle);
	}
}
#endif
