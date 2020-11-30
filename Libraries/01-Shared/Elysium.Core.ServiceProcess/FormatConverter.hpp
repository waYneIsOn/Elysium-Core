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

namespace Elysium::Core::ServiceProcess
{
	class FormatConverter
	{
	public:
		//static int Translate(PowerBroadcastStatus PowerBroadcastStatus);
		//static int Translate(ServiceAccount ServiceAccount);
		//static int Translate(ServiceControllerPermissionAccess ServiceControllerPermissionAccess);
		static int Translate(ServiceControllerStatus ServiceControllerStatus);
		//static int Translate(ServiceStartMode ServiceStartMode);
		static int Translate(ServiceType ServiceType);
		//static int Translate(SessionChangeReason SessionChangeReason);
	private:
		FormatConverter();
		~FormatConverter();
	};
}
#endif
