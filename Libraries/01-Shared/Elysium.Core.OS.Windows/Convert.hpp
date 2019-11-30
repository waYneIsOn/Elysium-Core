/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_OS_WINDOWS_CONVERT
#define ELYSIUM_CORE_OS_WINDOWS_CONVERT

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>
#endif

namespace Elysium
{
	namespace Core
	{
		namespace OS
		{
			namespace Windows
			{
				class Convert final
				{
				public:
					~Convert();

					static std::wstring ToWString(const String& Value);
				private:
					Convert();
				};
			}
		}
	}
}
#endif
