/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEDESCRIPTION
#define ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEDESCRIPTION

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
