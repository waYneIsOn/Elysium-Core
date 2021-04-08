#include "Process.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

Elysium::Core::Diagnostics::Process::Process()
	: _MachineName(u8"."), _IsRemoteMachine(false), _ProcessId(0), _HasProcessId(false), _ThreadId(0), _HasThreadId(false), _ProcessHandle(nullptr), 
	_ThreadHandle(nullptr), _StartInfo()
{ }
Elysium::Core::Diagnostics::Process::~Process()
{
	if (_ProcessHandle != nullptr)
	{
		CloseHandle(_ProcessHandle);
		_ProcessHandle = nullptr;
	}
	if (_ThreadHandle != nullptr)
	{
		CloseHandle(_ThreadHandle);
		_ProcessHandle = nullptr;
	}
}

Elysium::Core::Diagnostics::Process Elysium::Core::Diagnostics::Process::GetCurrentProcess()
{
	ELYSIUM_CORE_DIAGNOSTICS_PROCESSHANDLE ProcessHandle = ELYSIUM_CORE_DIAGNOSTICS_GETCURRENTPROCESS;
	if (ProcessHandle == nullptr)
	{
		// ToDo:
		throw 1;
	}

	// ToDo:
	throw 1;
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcesses()
{
	return GetProcesses(u8".");
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcesses(const Elysium::Core::String& MachineName)
{
	// ToDo:
	throw 1;
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

const Elysium::Core::Collections::Template::Array<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcessesByName(const Elysium::Core::String& ProcessName)
{
	return GetProcessesByName(ProcessName, u8".");
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcessesByName(const Elysium::Core::String& ProcessName, const Elysium::Core::String& MachineName)
{
	// ToDo:
	throw 1;
}

const bool Elysium::Core::Diagnostics::Process::GetHasExited() const
{
	unsigned long ExitCode = -1;
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

Elysium::Core::Diagnostics::ProcessStartInfo& Elysium::Core::Diagnostics::Process::GetStartInfo()
{
	return _StartInfo;
}

const Elysium::Core::Diagnostics::ProcessStartInfo& Elysium::Core::Diagnostics::Process::GetStartInfo() const
{
	return _StartInfo;
}

const bool Elysium::Core::Diagnostics::Process::Start()
{
	const Elysium::Core::String& FileName = _StartInfo.GetFileName();

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
	ExitProcess(0);
}

const bool Elysium::Core::Diagnostics::Process::CloseMainWindow()
{
	//return CloseWindow(nullptr);
	throw 1;
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

Elysium::Core::Diagnostics::Process::Process(const Elysium::Core::String MachineName, const bool IsRemoteMachine, const Elysium::Core::uint32_t ProcessId)
	: _MachineName(MachineName), _IsRemoteMachine(IsRemoteMachine), _ProcessId(ProcessId), _HasProcessId(true), _ThreadId(0), _HasThreadId(false),
	_ProcessHandle(nullptr),_ThreadHandle(nullptr), _StartInfo()
{ }
