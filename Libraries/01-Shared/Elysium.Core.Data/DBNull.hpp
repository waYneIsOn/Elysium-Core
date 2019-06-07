/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_DBNULL
#define ELYSIUM_CORE_DATA_DBNULL

#ifndef ELYSIUM_CORE_DATA_API
#include "API.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			class ELYSIUM_CORE_DATA_API DBNull final
			{
			public:
				static const DBNull* Value();
			private:
				DBNull();
				DBNull(const DBNull& Source);
				~DBNull();

				static const DBNull _Value;
			};
		}
	}
}
#endif
