/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESSSTARTINFO
#define ELYSIUM_CORE_DIAGNOSTICS_PROCESSSTARTINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSSTARTINFO
#include "../Elysium.Core.Template/ProcessStartInfo.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	//class ELYSIUM_CORE_API Elysium::Core::Template::Diagnostics::ProcessStartInfo;

	using ProcessStartInfo = Elysium::Core::Template::Diagnostics::ProcessStartInfo;
}
#endif
