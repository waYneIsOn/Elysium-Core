/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_COMMANDTYPE
#define ELYSIUM_CORE_DATA_COMMANDTYPE

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			enum class CommandType : int
			{
				Text = 1,
				StoredProcedure = 4,
				TableDirect = 512
			};
		}
	}
}
#endif
