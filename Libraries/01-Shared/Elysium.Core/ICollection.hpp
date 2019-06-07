/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_ICOLLECTION
#define ELYSIUM_CORE_COLLECTIONS_ICOLLECTION

#ifndef ELYSIUM_CORE_COLLECTIONS_IENUMERABLE
#include "IEnumerable.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Collections
		{
			/// Defines size, enumerators, and synchronization methods for all nongeneric collections.
			template <class T>
			class ICollection : public IEnumerable<T>
			{
			public:
				/// <summary>
				/// Destroy the object using the virtual destructor
				/// </summary>
				virtual ~ICollection() {}

				virtual const size_t GetCount() const = 0;
				virtual const bool GetIsReadOnly() const = 0;

				virtual void Add(const T& Item) = 0;
				virtual void Add(const T* Item) = 0;
				virtual void Clear() = 0;
				virtual bool Contains(const T& Item) = 0;
				virtual bool Remove(const T& Item) = 0;
			};
		}
	}
}
#endif
