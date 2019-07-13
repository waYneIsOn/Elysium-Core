/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION
#define ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Exception.hpp"

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			class ELYSIUM_CORE_API InvalidDataException : public Exception
			{
			public:
				InvalidDataException();
				InvalidDataException(const String& Message);
				~InvalidDataException();
			};
		}
	}
}
#endif
