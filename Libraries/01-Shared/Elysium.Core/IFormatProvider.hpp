/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IFORMATPROVIDER
#define ELYSIUM_CORE_IFORMATPROVIDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API IFormatProvider
	{
	public:
		virtual ~IFormatProvider() { };

		//void* GetFormat(const Type& FormatType);
	};
}
#endif
