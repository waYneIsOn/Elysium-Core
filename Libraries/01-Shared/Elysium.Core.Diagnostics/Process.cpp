#include "Process.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS
#include "../Elysium.Core.Template/Process.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
#endif

Elysium::Core::Diagnostics::Process::Process(const char8_t* Name, const char8_t* MachineName, const bool IsRemoteMachine, const Elysium::Core::Template::System::uint32_t ProcessId)
	: _Name(Name), _MachineName(MachineName), _IsRemoteMachine(IsRemoteMachine), _ProcessId(ProcessId), _HasProcessId(true), _ThreadId(GetCurrentThreadId()),
	_HasThreadId(true), _ProcessHandle(Elysium::Core::Template::Diagnostics::Process::GetHandle(ProcessId)), _ThreadHandle(GetCurrentThread())
{
	// @ToDo: _ThreadId and _ThreadHandle
}

Elysium::Core::Diagnostics::Process::Process() noexcept
	: _Name(), _MachineName(_LocalMachineName), _IsRemoteMachine(false), _ProcessId(0), _HasProcessId(false), _ThreadId(0), _HasThreadId(false),
	_ProcessHandle(nullptr), _ThreadHandle(nullptr)
{ }

Elysium::Core::Diagnostics::Process::Process(const Process& Source)
	: _Name(Source._Name), _MachineName(Source._MachineName), _IsRemoteMachine(Source._IsRemoteMachine), _ProcessId(Source._ProcessId), _HasProcessId(Source._HasProcessId),
	_ThreadId(Source._ThreadId), _HasThreadId(Source._HasThreadId), _ProcessHandle(Source._ProcessHandle), _ThreadHandle(Source._ThreadHandle)
{ }

Elysium::Core::Diagnostics::Process::Process(Process&& Right) noexcept
	: _Name(), _MachineName(), _IsRemoteMachine(), _ProcessId(), _HasProcessId(), _ThreadId(), _HasThreadId(), _ProcessHandle(), _ThreadHandle()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Diagnostics::Process::~Process()
{
	Close();
}

Elysium::Core::Diagnostics::Process& Elysium::Core::Diagnostics::Process::operator=(const Process& Source)
{
	if (this != &Source)
	{
		_Name = Source._Name;
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

Elysium::Core::Diagnostics::Process& Elysium::Core::Diagnostics::Process::operator=(Process&& Right) noexcept
{
	if (this != &Right)
	{
		_Name = Elysium::Core::Template::Functional::Move(Right._Name);
		_MachineName = Elysium::Core::Template::Functional::Move(Right._MachineName);
		_IsRemoteMachine = Elysium::Core::Template::Functional::Move(Right._IsRemoteMachine);
		_ProcessId = Elysium::Core::Template::Functional::Move(Right._ProcessId);
		_HasProcessId = Elysium::Core::Template::Functional::Move(Right._HasProcessId);
		_ThreadId = Elysium::Core::Template::Functional::Move(Right._ThreadId);
		_HasThreadId = Elysium::Core::Template::Functional::Move(Right._HasThreadId);
		_ProcessHandle = Elysium::Core::Template::Functional::Move(Right._ProcessHandle);
		_ThreadHandle = Elysium::Core::Template::Functional::Move(Right._ThreadHandle);

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

const bool Elysium::Core::Diagnostics::Process::GetHasExited() const
{
	return Elysium::Core::Template::Diagnostics::Process::HasExited(_ProcessHandle);
}

const Elysium::Core::Template::System::uint32_t Elysium::Core::Diagnostics::Process::GetId() const
{
	if (!_HasProcessId)
	{
		throw InvalidOperationException();
	}
	
	return _ProcessId;
}

const Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::ProcessModule> Elysium::Core::Diagnostics::Process::GetModules() const
{
	DWORD RequiredBytes;
	if (!EnumProcessModules(_ProcessHandle, nullptr, 0, &RequiredBytes))
	{
		//throw SystemException();
	}

	Template::Container::Vector<HMODULE> ModuleHandles = Template::Container::Vector<HMODULE>(RequiredBytes / sizeof(HMODULE));
	if (!EnumProcessModules(_ProcessHandle, &ModuleHandles[0], RequiredBytes, &RequiredBytes))
	{
		//throw SystemException();
	}

	Template::Container::Vector<ProcessModule> Result = Template::Container::Vector<ProcessModule>(ModuleHandles.GetLength());
	Result.Clear();
	for (Template::Container::Vector<HMODULE>::FIterator Iterator = ModuleHandles.GetBegin(); Iterator != ModuleHandles.GetEnd(); ++Iterator)
	{
		HMODULE CurrentModuleHandle = *Iterator;
		//Result.PushBack(ProcessModule(_ProcessHandle, CurrentModuleHandle));
	}

	return Result;
}

const Elysium::Core::Utf8String& Elysium::Core::Diagnostics::Process::GetProcessName() const
{
	return _Name;
}

Elysium::Core::Diagnostics::Process Elysium::Core::Diagnostics::Process::Start(const ProcessStartInfo& StartInfo)
{
	const Template::Text::String<char8_t>& FileName = StartInfo.GetFileName();
	const Template::Text::String<wchar_t>& WideFileName = Template::Text::Unicode::Utf16::SafeToWideString<char8_t>(&FileName[0], FileName.GetLength());

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
		throw Template::Exceptions::SystemException();
	}

	return Process(u8"", _LocalMachineName, false, ProcessInformation.dwProcessId);
	/*
	_ProcessId = ProcessInformation.dwProcessId;
	_HasProcessId = true;
	_ThreadId = ProcessInformation.dwThreadId;
	_HasThreadId = true;
	_ProcessHandle = ProcessInformation.hProcess;
	_ThreadHandle = ProcessInformation.hThread;
	*/
	//return true;
}

void Elysium::Core::Diagnostics::Process::Close()
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

	_ProcessId = 0;
	_HasProcessId = false;
	_ThreadId = 0;
	_HasThreadId = false;
	_MachineName = _MachineName.Empty;
	_IsRemoteMachine = false;
}

const bool Elysium::Core::Diagnostics::Process::CloseMainWindow()
{
	void* MainWindowHandle = Elysium::Core::Template::Diagnostics::Process::GetMainWindowHandle(_ProcessId);

	return Elysium::Core::Template::Diagnostics::Process::CloseMainWindow(reinterpret_cast<HWND>(MainWindowHandle));
}

void Elysium::Core::Diagnostics::Process::Kill(const bool EntireProcessTree)
{
	Elysium::Core::Template::Diagnostics::Process::Kill(_ProcessHandle, 0, EntireProcessTree);
}

void Elysium::Core::Diagnostics::Process::WaitForExit(const Elysium::Core::Template::System::uint32_t Milliseconds)
{
	Elysium::Core::Template::Diagnostics::Process::WaitForExit(_ProcessHandle, Milliseconds);
}

const Elysium::Core::Diagnostics::Process Elysium::Core::Diagnostics::Process::CurrentProcess()
{
	void* ProcessHandle = Elysium::Core::Template::Diagnostics::Process::GetCurrentProcessHandle();
	Elysium::Core::Utf8String CurrentProcessName = Elysium::Core::Template::Diagnostics::Process::GetName(ProcessHandle);

	return Process(&CurrentProcessName[0], _LocalMachineName, false, Elysium::Core::Template::Diagnostics::Process::GetCurrentProcessId());
}

const Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcesses(const char8_t* MachineName)
{
	const Elysium::Core::Template::Container::Vector<PROCESSENTRY32> ProcessIds =
		Elysium::Core::Template::Diagnostics::Process::GetProcessIds();

	Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::Process> Result =
		Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::Process>(ProcessIds.GetLength());
	Result.Clear();

	for (Elysium::Core::Template::Container::Vector<PROCESSENTRY32>::ConstIterator Iterator = ProcessIds.GetBegin();
		Iterator != ProcessIds.GetEnd(); ++Iterator)
	{
		PROCESSENTRY32 CurrentEnty = *Iterator;

		Elysium::Core::Utf8String CurrentProcessName = Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(
			&CurrentEnty.szExeFile[0],
			Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&CurrentEnty.szExeFile[0]));

		Result.PushBack(Elysium::Core::Template::Functional::Move(Process(&CurrentProcessName[0], MachineName, MachineName == _LocalMachineName, CurrentEnty.th32ProcessID)));
	}

	return Result;
}

const Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcessesByName(const char8_t* ProcessName, const char8_t* MachineName)
{
	const Elysium::Core::Template::Container::Vector<PROCESSENTRY32> ProcessIds =
		Elysium::Core::Template::Diagnostics::Process::GetProcessIdsByName(ProcessName, MachineName);

	Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::Process> Result =
		Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::Process>(ProcessIds.GetLength());
	Result.Clear();

	for (Elysium::Core::Template::Container::Vector<PROCESSENTRY32>::ConstIterator Iterator = ProcessIds.GetBegin();
		Iterator != ProcessIds.GetEnd(); ++Iterator)
	{
		PROCESSENTRY32 CurrentEnty = *Iterator;

		Elysium::Core::Utf8String CurrentProcessName = Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(
			&CurrentEnty.szExeFile[0],
			Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(&CurrentEnty.szExeFile[0]));

		Result.PushBack(Elysium::Core::Template::Functional::Move(Process(&CurrentProcessName[0], MachineName, MachineName == _LocalMachineName, CurrentEnty.th32ProcessID)));
	}

	return Result;
}



/*
inline const Container::Vector<ProcessModule> Process::GetModules() const
{
	DWORD RequiredBytes;
	if (!EnumProcessModules(_ProcessHandle, nullptr, 0, &RequiredBytes))
	{
		throw Exceptions::SystemException();
	}

	Container::Vector<HMODULE> ModuleHandles = Container::Vector<HMODULE>(RequiredBytes / sizeof(HMODULE));
	if (!EnumProcessModules(_ProcessHandle, &ModuleHandles[0], RequiredBytes, &RequiredBytes))
	{
		throw Exceptions::SystemException();
	}

	Container::Vector<ProcessModule> Result = Container::Vector<ProcessModule>(ModuleHandles.GetLength());
	Result.Clear();
	for (Container::Vector<HMODULE>::FIterator Iterator = ModuleHandles.GetBegin(); Iterator != ModuleHandles.GetEnd(); ++Iterator)
	{
		HMODULE CurrentModuleHandle = *Iterator;
		Result.PushBack(ProcessModule(_ProcessHandle, CurrentModuleHandle));
	}

	return Result;
}

inline const bool Elysium::Core::Template::Diagnostics::Process::Start(const ProcessStartInfo& StartInfo)
{
}

*/

