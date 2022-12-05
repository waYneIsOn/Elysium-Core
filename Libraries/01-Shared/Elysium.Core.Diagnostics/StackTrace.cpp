#include "StackTrace.hpp"

#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESS
#include "Process.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _DBGHELP_
#include <DbgHelp.h>
#endif
#endif

Elysium::Core::Diagnostics::StackTrace::StackTrace()
	: _StackFrames(CaptureStackFrames())
{ }

Elysium::Core::Diagnostics::StackTrace::~StackTrace() noexcept
{ }

const Elysium::Core::Diagnostics::Container::VectorOfStackFrame& Elysium::Core::Diagnostics::StackTrace::GetFrames() const noexcept
{
	return _StackFrames;
}

Elysium::Core::Diagnostics::Container::VectorOfStackFrame Elysium::Core::Diagnostics::StackTrace::CaptureStackFrames()
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	// https://learn.microsoft.com/en-us/windows/win32/debug/capturestackbacktrace
	// https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-symfromaddr?source=recommendations
	//		-> All DbgHelp functions, such as this one, are single threaded. Therefore, calls from more than one thread to this function will 
	//		likely result in unexpected behavior or memory corruption. To avoid this, you must synchronize all concurrent calls from more than one 
	//		thread to this function.
	// should use this due to multithreading:
	// https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-stackwalk

	CONTEXT NativeContextFrame;
	RtlCaptureContext(&NativeContextFrame);

	STACKFRAME64 NativeStackFrame;
	memset(&NativeStackFrame, 0, sizeof(STACKFRAME64));
	NativeStackFrame.AddrPC.Mode = AddrModeFlat;
	NativeStackFrame.AddrStack.Mode = AddrModeFlat;
	NativeStackFrame.AddrFrame.Mode = AddrModeFlat;
	NativeStackFrame.AddrPC.Offset = NativeContextFrame.Rip;
	NativeStackFrame.AddrStack.Offset = NativeContextFrame.Rsp;
	NativeStackFrame.AddrFrame.Offset = NativeContextFrame.Rsp;

	DWORD MachineType = IMAGE_FILE_MACHINE_AMD64;

	static constexpr const Template::System::size SymbolBufferSize = sizeof(IMAGEHLP_SYMBOL64) + MaxFunctionNameLength * sizeof(wchar_t);
	Template::System::byte SymbolBuffer[SymbolBufferSize];

	IMAGEHLP_SYMBOL64* pSymbol = (IMAGEHLP_SYMBOL64*)&SymbolBuffer;
	memset(pSymbol, 0, sizeof(SymbolBufferSize));
	pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
	pSymbol->MaxNameLength = MaxFunctionNameLength;

	DWORD64 Displacement = 0;
	DWORD OffsetFromLine = 0;

	char MethodNameBuffer[MaxFunctionNameLength];

	IMAGEHLP_LINE64 Line;
	Line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

	HANDLE CurrentProcessHandle = Process::CurrentProcess()._ProcessHandle;

	Container::VectorOfStackFrame StackFrames = Container::VectorOfStackFrame(1);

	while(true)
	{
		BOOL StackWalk64Result = StackWalk64(MachineType, CurrentProcessHandle, GetCurrentThread(), &NativeStackFrame, &NativeContextFrame, nullptr,
			SymFunctionTableAccess64, SymGetModuleBase64, nullptr);
		if (StackWalk64Result != TRUE)
		{
			break; 
		}

		BOOL SymGetSymFromAddr64Result = SymGetSymFromAddr64(CurrentProcessHandle, (ULONG64)NativeStackFrame.AddrPC.Offset, &Displacement, pSymbol);
		BOOL UnDecorateSymbolNameResult = UnDecorateSymbolName(pSymbol->Name, (PSTR)MethodNameBuffer, MaxFunctionNameLength, UNDNAME_NAME_ONLY);
		BOOL SymGetLineFromAddr64Result = SymGetLineFromAddr64(CurrentProcessHandle, NativeStackFrame.AddrPC.Offset, &OffsetFromLine, &Line);

		StackFrames.PushBack(Elysium::Core::Template::Functional::Move(StackFrame((void*)Line.Address, (const char8_t*)MethodNameBuffer, Line.LineNumber, 0)));
	}
	/*
	SymInitialize(CurrentProcess, NULL, TRUE);

	void* STACK[MaxFrames];

	SYMBOL_INFO symbol = SYMBOL_INFO();
	symbol.MaxNameLen = TRACE_MAX_FUNCTION_NAME_LENGTH;
	symbol.SizeOfStruct = sizeof(SYMBOL_INFO);

	DWORD displacement;
	IMAGEHLP_LINE64 line;
	line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

	unsigned short NumberOfCapturedFrames = CaptureStackBackTrace(FramesToSkip, MaxFrames, STACK, nullptr);
	for (unsigned short i = 0; i < NumberOfCapturedFrames; i++)
	{
		BOOL SymFromAddrResult = SymFromAddr(CurrentProcess, (DWORD64)STACK[i], nullptr, &symbol);
		BOOL SymGetLineFromAddr64Result = SymGetLineFromAddr64(CurrentProcess, (DWORD64)STACK[i], &displacement, &line);


		bool sdfsdfd = false;
	}
	*/
	return StackFrames;
#endif
}
