/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_FILEMODE
#define ELYSIUM_CORE_IO_FILEMODE

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			enum class FileMode : long
			{
				CreateNew = 1,
				Create = 2,
				Open = 3,
				OpenOrCreate = 4,
				Truncate = 5,
				Append = 6
			};
		}
	}
}
#endif
