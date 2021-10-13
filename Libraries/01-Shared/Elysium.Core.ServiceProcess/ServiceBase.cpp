#include "ServiceBase.hpp"

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::ServiceProcess::ServiceBase::ServiceBase()
{
}
Elysium::Core::ServiceProcess::ServiceBase::~ServiceBase()
{
}

Elysium::Core::size _ServiceCount;
std::vector<Elysium::Core::ServiceProcess::ServiceBase*> _Services;

void Elysium::Core::ServiceProcess::ServiceBase::Run(const ServiceBase * Service)
{
	const ServiceBase* Services[1];
	Services[0] = Service;

	Run(1, Services);
}
void Elysium::Core::ServiceProcess::ServiceBase::Run(Elysium::Core::size ServiceCount, const ServiceBase * Services[])
{
	// ...
	_ServiceCount = ServiceCount;
	_Services = std::vector<ServiceBase*>(ServiceCount);
	for (Elysium::Core::size i = 0; i < ServiceCount; i++)
	{
		_Services[i] = (ServiceBase*)Services[i];
	}

	// prepare all required service table entries
	std::vector<SERVICE_TABLE_ENTRY> ServiceTable(ServiceCount);
	for (Elysium::Core::size i = 0; i < ServiceCount; i++)
	{
		ServiceTable[i].lpServiceName = (wchar_t*)Services[i]->GetServiceName();
		ServiceTable[i].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)MainCallback;
	}

	// connect the main thread of the process to the service control manager (SCM)
	if (!StartServiceCtrlDispatcher(ServiceTable.data()))
	{	// ToDo: error into event viewer
		//SvcReportEvent(TEXT("StartServiceCtrlDispatcher"));
	}
}
void Elysium::Core::ServiceProcess::ServiceBase::Stop()
{
	throw NotImplementedException(u8"Elysium::Core::ServiceProcess::ServiceBase::Stop");
}

bool Elysium::Core::ServiceProcess::ServiceBase::GetAutoLog() const
{
	return _AutoLog;
}
const wchar_t * Elysium::Core::ServiceProcess::ServiceBase::GetServiceName() const
{
	return _Name;
}

void Elysium::Core::ServiceProcess::ServiceBase::SetAutoLog(bool Value)
{
	_AutoLog = Value;
}
void Elysium::Core::ServiceProcess::ServiceBase::SetServiceName(const wchar_t * Name)
{
	_Name = (wchar_t*)Name;
}

void Elysium::Core::ServiceProcess::ServiceBase::RequestAdditionalTime(int Milliseconds)
{
	throw NotImplementedException();
}
void Elysium::Core::ServiceProcess::ServiceBase::ServiceMainCallback(unsigned long ArgumentCount, wchar_t * Arguments[])
{
	// ...
}


SERVICE_STATUS          gSvcStatus;
SERVICE_STATUS_HANDLE   gSvcStatusHandle;
HANDLE                  ghSvcStopEvent = NULL;

void Elysium::Core::ServiceProcess::ServiceBase::MainCallback(unsigned long ArgumentCount, wchar_t * Arguments[])
{
	// forward the callback to each service
	for (unsigned long i = 0; i < _ServiceCount; i++)
	{
		_Services[i]->ServiceMainCallback(ArgumentCount, Arguments);
	}

	// Register the handler function for the service
	gSvcStatusHandle = RegisterServiceCtrlHandler(L"ElysiumTestService", ServiceControlHandler);
	if (!gSvcStatusHandle)
	{	// ToDo: error into event viewer
		//SvcReportEvent(TEXT("RegisterServiceCtrlHandler"));
		return;
	}

	// These SERVICE_STATUS members remain as set here
	//gSvcStatus.dwServiceType = FormatConverter::Translate(ServiceType::Win32OwnProcess);
	gSvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	gSvcStatus.dwCurrentState = SERVICE_START_PENDING;
	gSvcStatus.dwServiceSpecificExitCode = S_OK;

	// Report initial status to the SCM
	ReportServiceStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

	// init
	{
		// TO_DO: Declare and set any required variables.
		//   Be sure to periodically call ReportSvcStatus() with 
		//   SERVICE_START_PENDING. If initialization fails, call
		//   ReportSvcStatus with SERVICE_STOPPED.

		// Create an event. The control handler function, SvcCtrlHandler,
		// signals this event when it receives the stop control code.
		ghSvcStopEvent = CreateEvent(
			NULL,    // default security attributes
			TRUE,    // manual reset event
			FALSE,   // not signaled
			NULL);   // no name

		if (ghSvcStopEvent == NULL)
		{
			ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
			return;
		}

		// Report running status when initialization is complete.
		ReportServiceStatus(SERVICE_RUNNING, NO_ERROR, 0);
		for (unsigned long i = 0; i < _ServiceCount; i++)
		{
			_Services.at(i)->OnStart(ArgumentCount, Arguments);
		}

		// ToDo: Perform work until service stops.
		while (true)
		{
			// Check whether to stop the service.
			WaitForSingleObject(ghSvcStopEvent, INFINITE);

			ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
			return;
		}
	}
}
void Elysium::Core::ServiceProcess::ServiceBase::ReportServiceStatus(unsigned long CurrentState, unsigned long Win32ExitCode, unsigned long WaitHint)
{
	static DWORD dwCheckPoint = 1;

	// Fill in the SERVICE_STATUS structure.
	gSvcStatus.dwCurrentState = CurrentState;
	gSvcStatus.dwWin32ExitCode = Win32ExitCode;
	gSvcStatus.dwWaitHint = WaitHint;

	if (CurrentState == SERVICE_START_PENDING)
	{
		gSvcStatus.dwControlsAccepted = 0;
	}
	else
	{
		gSvcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	}

	if ((CurrentState == SERVICE_RUNNING) || (CurrentState == SERVICE_STOPPED))
	{
		gSvcStatus.dwCheckPoint = 0;
	}
	else
	{
		gSvcStatus.dwCheckPoint = dwCheckPoint++;
	}

	// Report the status of the service to the SCM.
	SetServiceStatus(gSvcStatusHandle, &gSvcStatus);
}
void __stdcall Elysium::Core::ServiceProcess::ServiceBase::ServiceControlHandler(unsigned long ControlCode)
{
	/*
	#define SERVICE_CONTROL_PARAMCHANGE            0x00000006
	#define SERVICE_CONTROL_NETBINDADD             0x00000007
	#define SERVICE_CONTROL_NETBINDREMOVE          0x00000008
	#define SERVICE_CONTROL_NETBINDENABLE          0x00000009
	#define SERVICE_CONTROL_NETBINDDISABLE         0x0000000A
	#define SERVICE_CONTROL_DEVICEEVENT            0x0000000B
	#define SERVICE_CONTROL_HARDWAREPROFILECHANGE  0x0000000C
	#define SERVICE_CONTROL_POWEREVENT             0x0000000D
	#define SERVICE_CONTROL_SESSIONCHANGE          0x0000000E
	#define SERVICE_CONTROL_PRESHUTDOWN            0x0000000F
	#define SERVICE_CONTROL_TIMECHANGE             0x00000010
	//#define SERVICE_CONTROL_USER_LOGOFF            0x00000011
	#define SERVICE_CONTROL_TRIGGEREVENT           0x00000020
	//reserved for internal use                    0x00000021
	//reserved for internal use                    0x00000050
	#define SERVICE_CONTROL_LOWRESOURCES           0x00000060
	#define SERVICE_CONTROL_SYSTEMLOWRESOURCES     0x00000061
	*/
	// Handle the requested control code. 
	switch (ControlCode)
	{
	case SERVICE_CONTROL_STOP:
		ReportServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);

		// inform all services
		for (unsigned long i = 0; i < _ServiceCount; i++)
		{
			_Services.at(i)->OnStop();
		}

		// Signal the service to stop.
		SetEvent(ghSvcStopEvent);
		ReportServiceStatus(gSvcStatus.dwCurrentState, NO_ERROR, 0);

		return;
	case SERVICE_CONTROL_PAUSE:
		// inform all services
		for (unsigned long i = 0; i < _ServiceCount; i++)
		{
			_Services.at(i)->OnPause();
		}
		break;
	case SERVICE_CONTROL_CONTINUE:
		// inform all services
		for (unsigned long i = 0; i < _ServiceCount; i++)
		{
			_Services.at(i)->OnContinue();
		}
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		// inform all services
		for (unsigned long i = 0; i < _ServiceCount; i++)
		{
			_Services.at(i)->OnShutdown();
		}
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
		/*
	case SERVICE_CONTROL_POWEREVENT:
		// inform all services
		for (unsigned long i = 0; i < _ServiceCount; i++)
		{
			_Services.at(i)->OnPowerEvent();
		}
		break;
		*/
	default:
		break;
	}
}
