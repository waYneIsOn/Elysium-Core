/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#define ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class EXPORT CultureInfo
		{
		public:
			CultureInfo(int Culture);
			~CultureInfo();

			int GetLCID();
		private:
			int _Culture;
		};
	}
}
#endif
