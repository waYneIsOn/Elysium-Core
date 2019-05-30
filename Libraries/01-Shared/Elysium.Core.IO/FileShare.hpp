/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_FILESHARE
#define ELYSIUM_CORE_IO_FILESHARE

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			enum class FileShare : long
			{
				None = 0,
				Read = 1,
				Write = 2,
				ReadWrite = 3,
				Delete = 4,
				Inheritable = 16,
			};
		}
	}
}
#endif
