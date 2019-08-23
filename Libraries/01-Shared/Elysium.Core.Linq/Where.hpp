/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_LINQ_WHERE
#define ELYSIUM_CORE_LINQ_WHERE

#ifndef _ALGORITHM_
#include <algorithm>
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Linq
		{
			struct WhereContainer
			{
				template<class ContainerType, class LambdaType>
				ContainerType operator()(ContainerType & Container, LambdaType & Lambda)
				{
					// ToDo: can we somehow create a new empty ContainerType?
					ContainerType Result = ContainerType(Container);
					Result.clear();
					std::copy_if(cbegin(Container), cend(Container), std::back_inserter(Result), Lambda);
					
					return Result;
				}
			};
		}
	}
}
#endif
