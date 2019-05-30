/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_ILIST
#define ELYSIUM_CORE_COLLECTIONS_ILIST

#ifndef ELYSIUM_CORE_COLLECTIONS_ICOLLECTION
#include "ICollection.hpp"
#endif

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Collections
		{
			/// Represents a non-generic collection of objects that can be individually accessed by index.
			template <class T>
			class EXPORT IList : public ICollection<T>
			{
			public:
				/// <summary>
				/// Destroy the object using the virtual destructor
				/// </summary>
				virtual ~IList() {}

				virtual const size_t IndexOf(const T& Item) const = 0;
				virtual void Insert(size_t Index, const T& Item) = 0;
				virtual void RemoveAt(size_t Index) = 0;

				virtual T& operator[](size_t Index) const = 0;
			};
		}
	}
}
#endif
