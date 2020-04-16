/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_ILIST
#define ELYSIUM_CORE_COLLECTIONS_ILIST

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_ICOLLECTION
#include "ICollection.hpp"
#endif

namespace Elysium::Core::Collections
{
	/// Represents a non-generic collection of objects that can be individually accessed by index.
	template <typename T>
	class IList : public ICollection<T>
	{
	public:
		/// <summary>
		/// Destroy the object using the virtual destructor
		/// </summary>
		virtual ~IList() {}

		virtual T& operator[](size_t Index) const = 0;

		virtual const size_t IndexOf(const T& Item) const = 0;
		virtual void Insert(size_t Index, const T& Item) = 0;
		virtual void RemoveAt(size_t Index) = 0;
	};
}
#endif
