/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICEBASE
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICEBASE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_POWERBROADCASTSTATUS
#include "PowerBroadcastStatus.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON
#include "SessionChangeReason.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
	class ELYSIUM_CORE_SERVICEPROCESS_SERVICEBASE ServiceBase
	{
	protected:
		constexpr ServiceBase() = default;
	public:
		constexpr virtual ~ServiceBase();
	public:
		static void Run(const ServiceBase& Service);

		static void Run(const Elysium::Core::Template::System::size ServiceCount, const ServiceBase* Services[]);

		static void Stop();
	public:
		bool GetAutoLog() const;

		const wchar_t* GetServiceName() const;
	public:
		void SetAutoLog(const bool Value);

		void SetServiceName(const wchar_t* Name);
	public:
		void RequestAdditionalTime(const Elysium::Core::Template::System::int32_t Milliseconds);

		void ServiceMainCallback(const unsigned long ArgumentCount, const wchar_t* Arguments[]);
	protected:
		virtual void OnContinue() = 0;

		virtual void OnCustomCommand(const Elysium::Core::Template::System::int32_t Command) = 0;

		virtual void OnPause() = 0;

		virtual void OnPowerEvent(const PowerBroadcastStatus PowerStatus) = 0;

		virtual void OnSessionChange(const Elysium::Core::Template::System::int32_t SessionId, const SessionChangeReason Reason) = 0;

		virtual void OnShutdown() = 0;

		virtual void OnStart(const int ArgumentCount, const wchar_t* Arguments[]) = 0;

		virtual void OnStop() = 0;
	public:
		const int MaxNameLength = 80;
	private:
		bool _AutoLog = false;
		bool _CanHandlePowerEvent = true;
		bool _CanHandleSessionChangeEvent = true;
		bool _CanPauseAndContinue = true;
		bool _CanRaiseEvents = true;
		bool _CanShutdown = true;
		bool _CanStop = true;
		bool _DesignMode = false;

		//EventLog _EventLog;
		//EventHandlerList _Events;
		int _ExitCode = 0;
		wchar_t* _Name = (wchar_t*)L"";
		wchar_t* _DisplayName = (wchar_t*)L"";
	private:
		static void MainCallback(const unsigned long ArgumentCount, const wchar_t* Arguments[]);

		static void ReportServiceStatus(const unsigned long CurrentState, const unsigned long Win32ExitCode, const unsigned long WaitHint);

		static void __stdcall ServiceControlHandler(const unsigned long ControlCode);
	};
}
#endif
