/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONREADER
#define ELYSIUM_CORE_JSON_JSONREADER

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_API JsonReader
			{
			public:
				virtual ~JsonReader() {}
			protected:
				JsonReader();
			};
		}
	}
}
#endif
