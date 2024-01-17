#include "Process.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS
#include "../Elysium.Core.Template/Process.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSACCESS
#include "../Elysium.Core.Template/ProcessAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
#endif

Elysium::Core::Diagnostics::Process::Process(const char8_t* Name, const char8_t* MachineName, const bool IsRemoteMachine, const Elysium::Core::Template::System::uint32_t ProcessId)
	: _Name(Name), _MachineName(MachineName), _IsRemoteMachine(IsRemoteMachine), _ProcessId(ProcessId), _HasProcessId(true), _ThreadId(0),
	_HasThreadId(false),
	_ProcessHandle(Elysium::Core::Template::Diagnostics::Process::GetHandle(ProcessId, Elysium::Core::Template::Diagnostics::ProcessAccess::ReadControl)),
	_ThreadHandle(0), _Modules()
{
	// @ToDo: _ThreadId and _ThreadHandle
}

Elysium::Core::Diagnostics::Process::Process() noexcept
	: _Name(), _MachineName(_LocalMachineName), _IsRemoteMachine(false), _ProcessId(0), _HasProcessId(false), _ThreadId(0), _HasThreadId(false), 
	_ProcessHandle(nullptr), _ThreadHandle(nullptr), _Modules()
{ }

Elysium::Core::Diagnostics::Process::Process(const Process& Source)
	: _Name(), _MachineName(), _IsRemoteMachine(), _ProcessId(), _HasProcessId(), _ThreadId(), _HasThreadId(), _ProcessHandle(), _ThreadHandle(), _Modules()
{ 
	Close();
	*this = Source;
}

Elysium::Core::Diagnostics::Process::Process(Process&& Right) noexcept
	: _Name(), _MachineName(), _IsRemoteMachine(), _ProcessId(), _HasProcessId(), _ThreadId(), _HasThreadId(), _ProcessHandle(), _ThreadHandle(), _Modules()
{
	Close();
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
		_Modules = Source._Modules;
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
		_Modules = Elysium::Core::Template::Functional::Move(Right._Modules);

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
	return Elysium::Core::Template::Diagnostics::Process::HasExited(_ProcessId);
}

const Elysium::Core::Template::System::uint32_t Elysium::Core::Diagnostics::Process::GetId() const
{
	if (!_HasProcessId)
	{
		throw InvalidOperationException();
	}
	
	return _ProcessId;
}

const Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::ProcessModule>& Elysium::Core::Diagnostics::Process::GetModules() const
{
	if (_Modules.GetLength() == 0)
	{
		Elysium::Core::Template::Container::Vector<MODULEENTRY32W> NativeModules =
			Elysium::Core::Template::Diagnostics::Process::GetProcessModules(_ProcessId);

		for (Template::Container::Vector<MODULEENTRY32W>::FIterator Iterator = NativeModules.GetBegin(); Iterator != NativeModules.GetEnd(); ++Iterator)
		{
			MODULEENTRY32W& Entry = *Iterator;

			Elysium::Core::Template::Text::String<char8_t> Name =
				Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(Entry.szModule,
					Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Entry.szModule));
			Elysium::Core::Template::Text::String<char8_t> FileName =
				Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(Entry.szExePath,
					Elysium::Core::Template::Text::CharacterTraits<wchar_t>::GetLength(Entry.szExePath));

			Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::ProcessModule>& Modules =
				const_cast<Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::ProcessModule>&>(_Modules);
			Modules.PushBack(Elysium::Core::Template::Functional::Move(ProcessModule(Elysium::Core::Template::Functional::Move(Name),
				Elysium::Core::Template::Functional::Move(FileName), reinterpret_cast<void*>(Entry.modBaseAddr), nullptr, Entry.modBaseSize, Entry.th32ModuleID)));
		}
	}

	return _Modules;
}

const Elysium::Core::Utf8String& Elysium::Core::Diagnostics::Process::GetProcessName() const
{
	return _Name;
}

Elysium::Core::Diagnostics::Process Elysium::Core::Diagnostics::Process::Start(const ProcessStartInfo& StartInfo)
{
	







	const Template::Text::String<char8_t>& FileName = StartInfo.GetFileName();
	const Template::Text::String<wchar_t>& WideFileName = Template::Text::Unicode::Utf16::SafeToWideString<char8_t>(&FileName[0], FileName.GetLength());

	PROCESS_INFORMATION ProcessInformation = Elysium::Core::Template::Diagnostics::Process::StartViaCreateProcess(&WideFileName[0]);

	return Process(u8"", _LocalMachineName, false, ProcessInformation.dwProcessId);
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
	if (MainWindowHandle == nullptr)
	{
		return false;
	}

	const bool Result = Elysium::Core::Template::Diagnostics::Process::CloseMainWindow(reinterpret_cast<HWND>(MainWindowHandle));

	return Result;
}

void Elysium::Core::Diagnostics::Process::Kill(const bool EntireProcessTree)
{
	void* ProcessHandle = Elysium::Core::Template::Diagnostics::Process::GetHandle(_ProcessId, 
		Elysium::Core::Template::Diagnostics::ProcessAccess::Terminate);

	try
	{
		Elysium::Core::Template::Diagnostics::Process::Kill(ProcessHandle, -1, EntireProcessTree);
		CloseHandle(ProcessHandle);
	}
	catch (const Elysium::Core::Template::Exceptions::SystemException& ex)
	{
		CloseHandle(ProcessHandle);
		throw;
	}
}

void Elysium::Core::Diagnostics::Process::Refresh()
{
	//_Threads.Clear();
	_Modules.Clear();
}

void Elysium::Core::Diagnostics::Process::WaitForExit(const Elysium::Core::Template::System::uint32_t Milliseconds)
{
	Elysium::Core::Template::Diagnostics::Process::WaitForExit(_ProcessHandle, Milliseconds);
}

const Elysium::Core::Diagnostics::Process Elysium::Core::Diagnostics::Process::CurrentProcess()
{
	void* ProcessHandle = Elysium::Core::Template::Diagnostics::Process::GetCurrentProcessHandle();
	Elysium::Core::Utf8String CurrentProcessName = Elysium::Core::Template::Diagnostics::Process::GetName(ProcessHandle);

	return Process(&CurrentProcessName[0], _LocalMachineName, false, Elysium::Core::Template::Diagnostics::Process::GetCurrentId());
}

const Elysium::Core::Template::Container::Vector<Elysium::Core::Diagnostics::Process> Elysium::Core::Diagnostics::Process::GetProcesses(const char8_t* ProcessName, const char8_t* MachineName)
{
	const Elysium::Core::Template::Container::Vector<PROCESSENTRY32> ProcessIds =
		ProcessName == nullptr ? 
		Elysium::Core::Template::Diagnostics::Process::GetProcessIds() :
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

