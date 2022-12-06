/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKTRACE
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKTRACE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKFRAME
#include "StackFrame.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
// ToDo: template!
#include "../Elysium.Core/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESS
// ToDo: template!
#include "../Elysium.Core.Diagnostics/Process.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _DBGHELP_
#include <DbgHelp.h>

#pragma comment(lib, "Dbghelp.lib")
#endif
#endif

namespace Elysium::Core::Template::Diagnostics
{
	class StackTrace final
	{
	public:
		StackTrace();

		StackTrace(const System::uint16_t MaximumFramesToCapture);

		StackTrace(const StackTrace& Source) = delete;

		StackTrace(StackTrace&& Right) noexcept = delete;

		~StackTrace() noexcept;
	public:
		StackTrace& operator=(const StackTrace& Source) = delete;

		StackTrace& operator=(StackTrace&& Right) noexcept = delete;
	public:
		const Container::Vector<StackFrame>& GetFrames() const noexcept;
	public:
		//Utf8String ToUtf8String();
	private:
		Container::Vector<StackFrame> CaptureStackFrames(const System::uint16_t MaximumFramesToCapture);
	public:
		static constexpr const System::uint16_t DefaultFramesToCapture = 0xFFFF;
	private:
		static constexpr const System::uint16_t MaxFunctionNameLength = 1024;
	private:
		Container::Vector<StackFrame> _StackFrames;
	};

	inline Elysium::Core::Template::Diagnostics::StackTrace::StackTrace()
		: _StackFrames(CaptureStackFrames(DefaultFramesToCapture))
	{ }

	inline StackTrace::StackTrace(const System::uint16_t MaximumFramesToCapture)
		: _StackFrames(CaptureStackFrames(MaximumFramesToCapture))
	{ }

	inline Elysium::Core::Template::Diagnostics::StackTrace::~StackTrace()
	{ }

	const Elysium::Core::Template::Container::Vector<StackFrame>& Elysium::Core::Template::Diagnostics::StackTrace::GetFrames() const noexcept
	{
		return _StackFrames;
	}

	inline Elysium::Core::Template::Container::Vector<StackFrame> Elysium::Core::Template::Diagnostics::StackTrace::CaptureStackFrames(const System::uint16_t MaximumFramesToCapture)
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		// https://learn.microsoft.com/en-us/windows/win32/debug/capturestackbacktrace
		// https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-symfromaddr?source=recommendations
		//		-> All DbgHelp functions, such as this one, are single threaded. Therefore, calls from more than one thread to this function will 
		//		likely result in unexpected behavior or memory corruption. To avoid this, you must synchronize all concurrent calls from more than one 
		//		thread to this function.
		// should use this due to multithreading:
		// https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-stackwalk
		//		-> All DbgHelp functions, such as this one, are single threaded. Therefore, calls from more than one thread to this function will...
		//			-> will still need to work with criticalsection!

		CONTEXT NativeContextFrame;
		RtlCaptureContext(&NativeContextFrame);

		STACKFRAME64 NativeStackFrame;
		memset(&NativeStackFrame, 0, sizeof(STACKFRAME64));
		NativeStackFrame.AddrPC.Mode = AddrModeFlat;
		NativeStackFrame.AddrStack.Mode = AddrModeFlat;
		NativeStackFrame.AddrFrame.Mode = AddrModeFlat;

		// https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/ns-dbghelp-stackframe
#ifdef _M_IX86
		NativeStackFrame.AddrPC.Offset = context.Eip;
		NativeStackFrame.AddrStack.Offset = context.Esp;
		NativeStackFrame.AddrFrame.Offset = context.Ebp;

		DWORD MachineType = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
		NativeStackFrame.AddrPC.Offset = NativeContextFrame.Rip;
		NativeStackFrame.AddrStack.Offset = NativeContextFrame.Rsp;
		NativeStackFrame.AddrFrame.Offset = NativeContextFrame.Rsp;

		DWORD MachineType = IMAGE_FILE_MACHINE_AMD64;
#elif _M_IA64
		NativeStackFrame.AddrPC.Offset = context.StIIP;
		NativeStackFrame.AddrStack.Offset = context.IntSp;
		NativeStackFrame.AddrFrame.Offset = context.IntSp;
		NativeStackFrame.AddrBStore.Offset = context.RsBSP;

		DWORD MachineType = IMAGE_FILE_MACHINE_IA64;
#elif _M_ARM64
		NativeStackFrame.AddrPC.Offset = context.Pc;
		NativeStackFrame.AddrStack.Offset = context.Sp;
		NativeStackFrame.AddrFrame.Offset = context.Fp;

		DWORD MachineType = IMAGE_FILE_MACHINE_ARM64;
#else
#error "Unknown architecture"
#endif

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

		HANDLE CurrentProcessHandle = Elysium::Core::Diagnostics::Process::CurrentProcess()._ProcessHandle;

		Container::Vector<StackFrame> StackFrames = Container::Vector<StackFrame>(1);
		Template::System::uint16_t FrameCount;
		for (FrameCount = 0; FrameCount < MaximumFramesToCapture; ++FrameCount)
		{
			BOOL StackWalk64Result = StackWalk64(MachineType, CurrentProcessHandle, GetCurrentThread(), &NativeStackFrame, &NativeContextFrame, nullptr,
				SymFunctionTableAccess64, SymGetModuleBase64, nullptr);
			if (StackWalk64Result != TRUE)
			{
				break;
				//throw SystemException();
			}
			/*
			if (NativeStackFrame.AddrPC.Offset == NativeStackFrame.AddrReturn.Offset)
			{	// recursion - doesn't matter as MaximumFramesToCapture defines how many frames the user wants anyways
			}
			*/
			BOOL SymGetSymFromAddr64Result = SymGetSymFromAddr64(CurrentProcessHandle, (ULONG64)NativeStackFrame.AddrPC.Offset, &Displacement, pSymbol);
			if (SymGetSymFromAddr64Result != TRUE)
			{
				//throw SystemException();
			}

			DWORD UnDecorateSymbolNameResult = UnDecorateSymbolName(pSymbol->Name, (PSTR)MethodNameBuffer, MaxFunctionNameLength, UNDNAME_NAME_ONLY);

			BOOL SymGetLineFromAddr64Result = SymGetLineFromAddr64(CurrentProcessHandle, NativeStackFrame.AddrPC.Offset, &OffsetFromLine, &Line);
			if (SymGetLineFromAddr64Result != TRUE)
			{
				//throw SystemException();
			}
			
			StackFrames.PushBack(Elysium::Core::Template::Functional::Move(StackFrame((void*)Line.Address, (const char8_t*)MethodNameBuffer,
				Line.LineNumber, 0)));
		}

		return StackFrames;
#endif
	}
}
#endif
