/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_FILEACCESS
#define ELYSIUM_CORE_IO_FILEACCESS

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			enum class FileAccess : long
			{
				Read = 1,
				Write = 2,
				ReadWrite = 3
			};
		}
	}
}
#endif
