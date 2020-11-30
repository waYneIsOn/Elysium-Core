/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEDESCRIPTION
#define ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEDESCRIPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON
#include "SessionChangeReason.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
	typedef struct _SessionChangeDescription
	{
		SessionChangeReason Reason;
		int SessionId;
	} SessionChangeDescription;
}
#endif
