/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONEXCEPTION
#define ELYSIUM_CORE_JSON_JSONEXCEPTION

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../Elysium.Core/Exception.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_API JsonException : public Elysium::Core::Exception
			{
			public:
				JsonException();
				JsonException(const String& Message);
				virtual ~JsonException();
			};
		}
	}
}
#endif
