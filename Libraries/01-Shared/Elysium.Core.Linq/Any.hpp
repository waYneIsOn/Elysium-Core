/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_LINQ_ANY
#define ELYSIUM_CORE_LINQ_ANY

#ifndef ELYSIUM_CORE_LINQ_API
#include "API.hpp"
#endif

namespace Elysium::Core::Linq
{
	struct ELYSIUM_CORE_LINQ_API AnyContainer
	{
		template<class ContainerType>
		bool operator()(ContainerType && Container)
		{
			for (auto Element : Container)
			{
				return true;
			}
			return false;
		}
	};
}
#endif
