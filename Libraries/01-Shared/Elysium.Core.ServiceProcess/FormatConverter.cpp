#include "FormatConverter.hpp"

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

int Elysium::Core::ServiceProcess::FormatConverter::Translate(ServiceControllerStatus ServiceControllerStatus)
{
	switch (ServiceControllerStatus)
	{
	case ServiceControllerStatus::ContinuePending:
		return SERVICE_CONTINUE_PENDING;
	case ServiceControllerStatus::Paused:
		return SERVICE_PAUSED;
	case ServiceControllerStatus::PausePending:
		return SERVICE_PAUSE_PENDING;
	case ServiceControllerStatus::Running:
		return SERVICE_RUNNING;
	case ServiceControllerStatus::StartPending:
		return SERVICE_START_PENDING;
	case ServiceControllerStatus::Stopped:
		return SERVICE_STOPPED;
	case ServiceControllerStatus::StopPending:
		return SERVICE_STOP_PENDING;
	default:
		throw NotImplementedException(u"unhandled ServiceControllerStatus");
	}
}
int Elysium::Core::ServiceProcess::FormatConverter::Translate(ServiceType ServiceType)
{	// ToDo: ServiceType is a flag - a simple switch case won't cut it!!
	switch (ServiceType)
	{
	case ServiceType::KernelDriver:
		return SERVICE_KERNEL_DRIVER;
	case ServiceType::FileSystemDriver:
		return SERVICE_FILE_SYSTEM_DRIVER;
	case ServiceType::Adapter:
		return SERVICE_ADAPTER;
	case ServiceType::RecognizerDriver:
		return SERVICE_RECOGNIZER_DRIVER;
	case ServiceType::Win32OwnProcess:
		return SERVICE_WIN32_OWN_PROCESS;
	case ServiceType::Win32ShareProcess:
		return SERVICE_WIN32_SHARE_PROCESS;
	case ServiceType::InteractiveProcess:
		return SERVICE_INTERACTIVE_PROCESS;
	default:
		throw NotImplementedException(u"unhandled ServiceType");
	}
}

Elysium::Core::ServiceProcess::FormatConverter::FormatConverter()
{
}
Elysium::Core::ServiceProcess::FormatConverter::~FormatConverter()
{
}