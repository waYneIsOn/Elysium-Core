/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_FORMATCONVERTER
#define ELYSIUM_CORE_SERVICEPROCESS_FORMATCONVERTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_POWERBROADCASTSTATUS
#include "PowerBroadcastStatus.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICEACCOUNT
#include "ServiceAccount.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERPERMISSIONACCESS
#include "ServiceControllerPermissionAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERSTATUS
#include "ServiceControllerStatus.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICESTARTMODE
#include "ServiceStartMode.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICETYPE
#include "ServiceType.hpp"
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON
#include "SessionChangeReason.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
	class FormatConverter
	{
	public:
		FormatConverter() = delete;

		~FormatConverter() = delete;
	public:
		//static Elysium::Core::Template::System::int32_t Translate(PowerBroadcastStatus PowerBroadcastStatus);
		
		//static Elysium::Core::Template::System::int32_t Translate(ServiceAccount ServiceAccount);
		
		//static Elysium::Core::Template::System::int32_t Translate(ServiceControllerPermissionAccess ServiceControllerPermissionAccess);

		static Elysium::Core::Template::System::int32_t Translate(const ServiceControllerStatus ServiceControllerStatus);

		//static Elysium::Core::Template::System::int32_t Translate(ServiceStartMode ServiceStartMode);

		static Elysium::Core::Template::System::int32_t Translate(const ServiceType ServiceType);

		//static Elysium::Core::Template::System::int32_t Translate(SessionChangeReason SessionChangeReason);
	};
}
#endif
