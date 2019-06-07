/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#define ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API CultureInfo
		{
		public:
			CultureInfo();
			CultureInfo(int Culture);
			~CultureInfo();

			void GetName(String* Output) const;
			int GetLCID() const;
		private:
			int _Culture;	// locale id (LCID)
		};
	}
}
#endif
