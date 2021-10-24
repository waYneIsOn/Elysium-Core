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
#include "../Elysium.Core.Template/Primitives.hpp"
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

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API Process final
	{
	public:
		Process();
		Process(const Process& Source) = delete;
		Process(Process&& Right) noexcept = delete;
		~Process();

		Process& operator=(const Process& Source) = delete;
		Process& operator=(Process&& Right) noexcept = delete;

		const bool GetHasExited() const;
		const Elysium::Core::uint32_t GetId() const;

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

		static Process GetCurrentProcess();

		static const Elysium::Core::Collections::Template::Array<Process> GetProcesses();
		static const Elysium::Core::Collections::Template::Array<Process> GetProcesses(const Elysium::Core::String& MachineName);

		static Process GetProcessById(const Elysium::Core::uint32_t ProcessId);

		static const Elysium::Core::Collections::Template::Array<Process> GetProcessesByName(const Elysium::Core::String& ProcessName);
		static const Elysium::Core::Collections::Template::Array<Process> GetProcessesByName(const Elysium::Core::String& ProcessName, const Elysium::Core::String& MachineName);
	private:
		Elysium::Core::String _MachineName;
		bool _IsRemoteMachine;
		Elysium::Core::uint32_t _ProcessId;
		bool _HasProcessId;
		Elysium::Core::uint32_t _ThreadId;
		bool _HasThreadId;
		void* _ProcessHandle;
		void* _ThreadHandle;

		static inline Elysium::Core::String _LocalMachineName = Elysium::Core::String(u8".");

		Process(const Elysium::Core::String MachineName, const bool IsRemoteMachine, const Elysium::Core::uint32_t ProcessId);
	};
}
#endif
