/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_DATAROWVERSION
#define ELYSIUM_CORE_DATA_DATAROWVERSION

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			enum class DataRowVersion : int
			{
				Original = 256,
				Current = 512,
				Proposed = 1024,
				Default = 1536
			};
		}
	}
}
#endif
