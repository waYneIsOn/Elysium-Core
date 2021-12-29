#include "Process.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_INTERNAL_WINDOWFINDER
#include "WindowFinder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Elysium.Core.Template/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _INC_TOOLHELP32
#include <tlhelp32.h>
#endif
#else
#error "undefined os"
#endif

Elysium::Core::Diagnostics::Process::Process()
	: _MachineName(_LocalMachineName), _IsRemoteMachine(false), _ProcessId(0), _HasProcessId(false), _ThreadId(0), _HasThreadId(false), 
	_ProcessHandle(nullptr), _ThreadHandle(nullptr)
{ }
Elysium::Core::Diagnostics::Process::~Process()
{
	Close();
}

const bool Elysium::Core::Diagnostics::Process::GetHasExited() const
{
	unsigned long ExitCode;
	if (!GetExitCodeProcess(_ProcessHandle, &ExitCode))
	{
		throw Elysium::Core::SystemException();
	}

	return ExitCode != STILL_ACTIVE;
}

const Elysium::Core::uint32_t Elysium::Core::Diagnostics::Process::GetId() const
{
	if (!_HasProcessId)
	{
		throw Elysium::Core::InvalidOperationException();
	}

	return _ProcessId;
}

const bool Elysium::Core::Diagnostics::Process::Start(const ProcessStartInfo& StartInfo)
{
	const Elysium::Core::Utf8String& FileName = StartInfo.GetFileName();

	STARTUPINFO StartupInfo = STARTUPINFO();
	//ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
	StartupInfo.cb = sizeof(STARTUPINFO);

	PROCESS_INFORMATION ProcessInformation = PROCESS_INFORMATION();
	//ZeroMemory(&ProcessInformation, sizeof(PROCESS_INFORMATION));

	if (!CreateProcess((wchar_t*)&Elysium::Core::Text::Encoding::UTF16LE().GetBytes(&FileName[0], FileName.GetLength(), sizeof(wchar_t))[0],
		nullptr,        // Command line arguments
		nullptr,        // Process handle not inheritable
		nullptr,		// Thread handle not inheritable
		false,          // Set handle inheritance to FALSE
		0,              // No creation flags
		nullptr,		// Use parent's environment block
		nullptr,		// Use parent's starting directory 
		&StartupInfo, &ProcessInformation))
	{
		throw Elysium::Core::SystemException();
	}

	_ProcessId = ProcessInformation.dwProcessId;
	_HasProcessId = true;
	_ThreadId = ProcessInformation.dwThreadId;
	_HasThreadId = true;
	_ProcessHandle = ProcessInformation.hProcess;
	_ThreadHandle = ProcessInformation.hThread;

	return true;
}

void Elysium::Core::Diagnostics::Process::Close()
{
	if (_ThreadHandle != nullptr)
	{
		CloseHandle(_ThreadHandle);
		_ProcessHandle = nullptr;
	}
	if (_ProcessHandle != nullptr)
	{
		CloseHandle(_ProcessHandle);
		_ProcessHandle = nullptr;
	}
}

const bool Elysium::Core::Diagnostics::Process::CloseMainWindow()
{
	const void* MainWindowHandle = Internal::WindowFinder::GetMainWindowHandle(_ProcessId);
	if (MainWindowHandle == nullptr)
	{	// no main window found, ergo there is nothing to do, so simply return true
		return true;
	}
	else
	{
		return CloseWindow((HWND)MainWindowHandle) == 1;
	}
}

void Elysium::Core::Diagnostics::Process::Kill(const bool EntireProcessTree)
{
	if (EntireProcessTree)
	{	// ToDo:
		throw 1;
	}
	TerminateProcess(_ProcessHandle, 0);
}

void Elysium::Core::Diagnostics::Process::Refresh()
{	// ToDo:
	throw 1;
}

void Elysium::Core::Diagnostics::Process::WaitForExit()
{
	WaitForExit(INFINITE);
}

void Elysium::Core::Diagnostics::Process::WaitForExit(const Elysium::Core::int32_t Milliseconds)
{
	WaitForSingleObject(_ProcessHandle, Milliseconds);
}

void Elysium::Core::Diagnostics::Process::EnterDebugMode()
{
	//EnableDebugPriv();
	throw 1;
}

void Elysium::Core::Diagnostics::Process::LeaveDebugMode()
{
	//LeaveDebugPriv();
	throw 1;
}

Elysium::Core::Diagnostics::Process Elysium::Core::Diagnostics::Process::GetCurrentProcess()
{
	return Process(_LocalMachineName, false, GetCurrentProcessId());
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcesses()
{
	return GetProcesses(_LocalMachineName);
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcesses(const Elysium::Core::Utf8String& MachineName)
{
	HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (SnapshotHandle == INVALID_HANDLE_VALUE)
	{
		throw Elysium::Core::SystemException();
	}

	// ...
	PROCESSENTRY32 ProcessEntry = PROCESSENTRY32();
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(SnapshotHandle, &ProcessEntry))
	{
		CloseHandle(SnapshotHandle);
		throw Elysium::Core::SystemException();
	}

	Elysium::Core::size i = 0;
	do
	{
		i++;
	} while (Process32Next(SnapshotHandle, &ProcessEntry));

	// ...
	Elysium::Core::Collections::Template::Array<Process> Processes = Elysium::Core::Collections::Template::Array<Process>(i);
	if (!Process32First(SnapshotHandle, &ProcessEntry))
	{
		CloseHandle(SnapshotHandle);
		throw Elysium::Core::SystemException();
	}

	i = 0;
	do
	{
		Processes[i]._ProcessId = ProcessEntry.th32ProcessID;
		i++;
	} while (Process32Next(SnapshotHandle, &ProcessEntry));
	CloseHandle(SnapshotHandle);

	return Processes;
}

Elysium::Core::Diagnostics::Process Elysium::Core::Diagnostics::Process::GetProcessById(const Elysium::Core::uint32_t ProcessId)
{
	ELYSIUM_CORE_DIAGNOSTICS_PROCESSHANDLE ProcessHandle = ELYSIUM_CORE_DIAGNOSTICS_GETPROCESSBYID(READ_CONTROL | PROCESS_QUERY_INFORMATION, true, ProcessId);
	if (ProcessHandle == nullptr)
	{
		throw ArgumentException(u8"The process specified by the ProcessId parameter is not running. The identifier might be expired.");
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

const Elysium::Core::Collections::Template::Array<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcessesByName(const Elysium::Core::Utf8String& ProcessName)
{
	return GetProcessesByName(ProcessName, _LocalMachineName);
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcessesByName(const Elysium::Core::Utf8String& ProcessName, const Elysium::Core::Utf8String& MachineName)
{
	if (Elysium::Core::Utf8String::IsNullOrEmtpy(ProcessName))
	{
		throw Elysium::Core::ArgumentException(u8"ProcessName");
	}

	HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (SnapshotHandle == INVALID_HANDLE_VALUE)
	{
		throw Elysium::Core::SystemException();
	}

	// ...
	PROCESSENTRY32 ProcessEntry = PROCESSENTRY32();
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(SnapshotHandle, &ProcessEntry))
	{
		CloseHandle(SnapshotHandle);
		throw Elysium::Core::SystemException();
	}

	Elysium::Core::size i = 0;
	do
	{
		Elysium::Core::Utf8String CurrentProcessName = Elysium::Core::Text::Encoding::UTF16LE().GetString((byte*)&ProcessEntry.szExeFile[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetSize(&ProcessEntry.szExeFile[0]));
		if (CurrentProcessName == ProcessName)
		{
			i++;
		}
	} while (Process32Next(SnapshotHandle, &ProcessEntry));

	// ...
	Elysium::Core::Collections::Template::Array<Process> Processes = Elysium::Core::Collections::Template::Array<Process>(i);
	if (!Process32First(SnapshotHandle, &ProcessEntry))
	{
		CloseHandle(SnapshotHandle);
		throw Elysium::Core::SystemException();
	}

	i = 0;
	do
	{
		Elysium::Core::Utf8String CurrentProcessName = Elysium::Core::Text::Encoding::UTF16LE().GetString((byte*)&ProcessEntry.szExeFile[0], Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetSize(&ProcessEntry.szExeFile[0]));
		if (CurrentProcessName == ProcessName)
		{
			Processes[i]._ProcessId = ProcessEntry.th32ProcessID;
			i++;
		}
	} while (Process32Next(SnapshotHandle, &ProcessEntry));
	CloseHandle(SnapshotHandle);

	return Processes;
}

Elysium::Core::Diagnostics::Process::Process(const Elysium::Core::Utf8String MachineName, const bool IsRemoteMachine, const Elysium::Core::uint32_t ProcessId)
	: _MachineName(MachineName), _IsRemoteMachine(IsRemoteMachine), _ProcessId(ProcessId), _HasProcessId(true), _ThreadId(0), _HasThreadId(false),
	_ProcessHandle(nullptr),_ThreadHandle(nullptr)
{ }
