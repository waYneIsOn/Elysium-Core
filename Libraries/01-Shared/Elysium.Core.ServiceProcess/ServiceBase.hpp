/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICEBASE
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICEBASE

#ifndef ELYSIUM_CORE_SERVICEPROCESS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_POWERBROADCASTSTATUS
#include "PowerBroadcastStatus.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEDESCRIPTION
#include "SessionChangeDescription.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
	class ELYSIUM_CORE_SERVICEPROCESS_SERVICEBASE ServiceBase
	{
	public:
		ServiceBase();
		virtual ~ServiceBase();

		const int MaxNameLength = 80;

		static void Run(const ServiceBase* Service);
		static void Run(size_t ServiceCount, const ServiceBase* Services[]);
		static void Stop();

		bool GetAutoLog() const;
		const wchar_t* GetServiceName() const;

		void SetAutoLog(bool Value);
		void SetServiceName(const wchar_t* Name);

		void RequestAdditionalTime(int Milliseconds);
		void ServiceMainCallback(unsigned long ArgumentCount, wchar_t* Arguments[]);
	protected:
		virtual void OnContinue() = 0;
		virtual void OnCustomCommand(int Command) = 0;
		virtual void OnPause() = 0;
		virtual void OnPowerEvent(const PowerBroadcastStatus* PowerStatus) = 0;
		virtual void OnSessionChange(const SessionChangeDescription* ChangeDescription) = 0;
		virtual void OnShutdown() = 0;
		virtual void OnStart(int ArgumentCount, wchar_t* Arguments[]) = 0;
		virtual void OnStop() = 0;
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

		static void MainCallback(unsigned long ArgumentCount, wchar_t* Arguments[]);
		static void ReportServiceStatus(unsigned long CurrentState, unsigned long Win32ExitCode, unsigned long WaitHint);
		static void __stdcall ServiceControlHandler(unsigned long ControlCode);
	};
}
#endif
