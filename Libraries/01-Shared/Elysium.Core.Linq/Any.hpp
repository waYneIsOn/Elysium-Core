/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_LINQ_ANY
#define ELYSIUM_CORE_LINQ_ANY

#ifdef _MSC_VER
#pragma once
#endif

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
