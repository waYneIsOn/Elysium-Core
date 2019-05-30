/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_PARAMETERDIRECTION
#define ELYSIUM_CORE_DATA_PARAMETERDIRECTION

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			enum class ParameterDirection : int
			{
				Input = 1,
				Output = 2,
				InputOutput = 3,
				ReturnValue = 6,
			};
		}
	}
}
#endif
