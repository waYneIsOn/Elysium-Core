/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_COMMON_DBEXCEPTION
#define ELYSIUM_CORE_DATA_COMMON_DBEXCEPTION

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_RUNTIME_INTEROPSERVICES_EXTERNALEXCEPTION
#include "../Elysium.Core/ExternalException.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			namespace Common
			{
				class ELYSIUM_CORE_DATA_API DbException : public Elysium::Core::Runtime::InteropServices::ExternalException
				{
				public:
					DbException();
					DbException(const String& Message);
					DbException(const String& Message, const int ErrorCode);
					~DbException();
				};
			}
		}
	}
}
#endif
