/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_IENUMERABLE
#define ELYSIUM_CORE_COLLECTIONS_IENUMERABLE

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Collections
		{
			/// Exposes an enumerator, which supports a simple iteration over a non-generic collection.
			template <class T>
			class EXPORT IEnumerable
			{
			public:
				/// <summary>
				/// Destroy the object using the virtual destructor
				/// </summary>
				virtual ~IEnumerable() {}

				//virtual const auto & GetIterator() = 0;
			};
		}
	}
}
#endif
