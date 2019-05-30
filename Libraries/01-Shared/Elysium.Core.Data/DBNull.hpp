/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_DBNULL
#define ELYSIUM_CORE_DATA_DBNULL

#ifndef ELYSIUM_CORE_EXPORT
#include "../Elysium.Core/Export.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			class EXPORT DBNull final
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
