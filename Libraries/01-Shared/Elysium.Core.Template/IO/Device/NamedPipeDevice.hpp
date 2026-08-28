/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_NAMEDPIPEDEVICE
#define ELYSIUM_CORE_TEMPLATE_IO_DEVICE_NAMEDPIPEDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINBASE_
	#include <WinBase.h>
	#endif

	#ifndef _NAMEDPIPE_H_
	#include <namedpipeapi.h>
	#endif
#endif

namespace Elysium::Core::Template::IO::Device
{
	class NamedPipeDevice
	{
	public:

	public:

	private:
		//HANDLE _NamedPipeHandle;
	};
}
#endif
