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

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESSSTARTINFO
#include "ProcessStartInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESSMODULE
#include "ProcessModule.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API Process final
	{
	private:
		Process(const char8_t* Name, const char8_t* MachineName, const bool IsRemoteMachine, const Elysium::Core::Template::System::uint32_t ProcessId);
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

		const Elysium::Core::Template::System::uint32_t GetId() const;

		const Elysium::Core::Template::Container::Vector<ProcessModule> GetModules() const;

		const Utf8String& GetProcessName() const;
	public:
		const bool Start(const ProcessStartInfo& StartInfo);

		void Close();

		const bool CloseMainWindow();

		void Kill(const bool EntireProcessTree);

		void WaitForExit(const Elysium::Core::Template::System::uint32_t Milliseconds = 0xFFFFFFFF);
	public:
		static const Process CurrentProcess();

		static const Elysium::Core::Template::Container::Vector<Process> GetProcesses(const char8_t* MachineName = _LocalMachineName);

		static Process GetProcessById(const Template::System::uint32_t ProcessId);

		static const Elysium::Core::Template::Container::Vector<Process> GetProcessesByName(const char8_t* ProcessName, const char8_t* MachineName = _LocalMachineName);
	private:
		inline static const char8_t* _LocalMachineName = u8".";
	private:
		Elysium::Core::Template::Text::String<char8_t> _Name;

		Elysium::Core::Template::Text::String<char8_t> _MachineName;
		bool _IsRemoteMachine;

		Elysium::Core::Template::System::uint32_t _ProcessId;
		bool _HasProcessId;

		Elysium::Core::Template::System::uint32_t _ThreadId;
		bool _HasThreadId;

		void* _ProcessHandle;
		void* _ThreadHandle;
	private:
		struct WindowHandleData
		{
			Elysium::Core::Template::System::uint32_t ProcessId;
			HANDLE WindowHandle;
		};

		static const HANDLE GetMainWindowHandle(const Elysium::Core::Template::System::uint32_t ProcessId);

		static BOOL GetMainWindowHandleCallback(HWND WindowHandle, LPARAM Parameter);

		static const bool IsMainWindow(HWND WindowHandle);
	};
}
#endif
