/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MEMORY_OBSERVERPOINTEROFTPIO
#define ELYSIUM_CORE_MEMORY_OBSERVERPOINTEROFTPIO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef _WINNT_
#include <winnt.h>
#endif

namespace Elysium::Core::Memory
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::ObserverPointer<TP_IO>;

	using ObserverPointerOfTPIO = Elysium::Core::Template::Memory::ObserverPointer<TP_IO>;
}
#endif
#endif
