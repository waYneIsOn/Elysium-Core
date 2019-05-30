/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_COMMANDBEHAVIOUR
#define ELYSIUM_CORE_DATA_COMMANDBEHAVIOUR

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			enum class CommandBehaviour : int
			{
				Default = 0,
				SingleResult = 1,
				SchemaOnly = 2,
				KeyInfo = 4,
				SingleRow = 8,
				SequentialAccess = 16,
				CloseConnection = 32
			};
		}
	}
}
#endif
