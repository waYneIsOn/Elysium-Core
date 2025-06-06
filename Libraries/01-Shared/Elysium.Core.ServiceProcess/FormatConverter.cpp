#include "FormatConverter.hpp"

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Template::System::int32_t Elysium::Core::ServiceProcess::FormatConverter::Translate(const ServiceControllerStatus ServiceControllerStatus)
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
		throw NotImplementedException(u8"Unhandled ServiceControllerStatus.");
	}
}

Elysium::Core::Template::System::int32_t Elysium::Core::ServiceProcess::FormatConverter::Translate(const ServiceType ServiceType)
{	// @ToDo: ServiceType is a flag - a simple switch case won't cut it!!
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
		throw NotImplementedException(u8"Unhandled ServiceType.");
	}
}
