/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESS
#define ELYSIUM_CORE_DIAGNOSTICS_PROCESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESSSTARTINFO
#include "ProcessStartInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Diagnostics::Internal
{
	class WinSymbols;
}

namespace Elysium::Core::Template::Diagnostics
{
	class StackTrace;
}

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API Process final
	{
		friend class Elysium::Core::Template::Diagnostics::StackTrace;
		friend class Internal::WinSymbols;
	private:
		Process(const Elysium::Core::Utf8String MachineName, const bool IsRemoteMachine, const Elysium::Core::uint32_t ProcessId);
	public:
		Process();

		Process(const Process& Source) = delete;

		Process(Process&& Right) noexcept = delete;

		~Process();
	public:
		Process& operator=(const Process& Source) = delete;

		Process& operator=(Process&& Right) noexcept = delete;
	public:
		const bool GetHasExited() const;

		const Elysium::Core::uint32_t GetId() const;
	public:
		const bool Start(const ProcessStartInfo& StartInfo);

		void Close();

		const bool CloseMainWindow();

		void Kill(const bool EntireProcessTree);

		void Refresh();

		void WaitForExit();

		void WaitForExit(const Elysium::Core::int32_t Milliseconds);
	public:
		static void EnterDebugMode();

		static void LeaveDebugMode();

		static const Process& CurrentProcess();

		static const Elysium::Core::Collections::Template::Array<Process> GetProcesses();

		static const Elysium::Core::Collections::Template::Array<Process> GetProcesses(const Elysium::Core::Utf8String& MachineName);

		static Process GetProcessById(const Elysium::Core::uint32_t ProcessId);

		static const Elysium::Core::Collections::Template::Array<Process> GetProcessesByName(const Elysium::Core::Utf8String& ProcessName);

		static const Elysium::Core::Collections::Template::Array<Process> GetProcessesByName(const Elysium::Core::Utf8String& ProcessName, const Elysium::Core::Utf8String& MachineName);
	private:
		static inline Elysium::Core::Utf8String _LocalMachineName = Elysium::Core::Utf8String(u8".");
	private:
		static Process _CurrentProcess;
	private:
		Elysium::Core::Utf8String _MachineName;
		bool _IsRemoteMachine;
		Elysium::Core::uint32_t _ProcessId;
		bool _HasProcessId;
		Elysium::Core::uint32_t _ThreadId;
		bool _HasThreadId;
		void* _ProcessHandle;
		void* _ThreadHandle;
	};
}
#endif
