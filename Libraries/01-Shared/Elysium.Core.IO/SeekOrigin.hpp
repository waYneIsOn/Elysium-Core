/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_SEEKORIGIN
#define ELYSIUM_CORE_IO_SEEKORIGIN

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			enum class SeekOrigin : int
			{
				Begin = 0,
				Current = 1,
				End = 2
			};
		}
	}
}
#endif
