/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_IENUMERATOR
#define ELYSIUM_CORE_COLLECTIONS_GENERIC_IENUMERATOR

#ifndef _XUTILITY_
#include <xutility>
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Collections
		{
			namespace Generic
			{
				template <typename T>
				class IEnumerator : std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T*, T&>
				{
				public:
					/// <summary>
					/// Destroy the object using the virtual destructor
					/// </summary>
					virtual ~IEnumerator() {}
					
					virtual bool MoveNext() = 0;
					//virtual T GetCurrent() = 0;
				};
			}
		}
	}
}
#endif
