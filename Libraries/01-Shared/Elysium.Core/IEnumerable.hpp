/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_IENUMERABLE
#define ELYSIUM_CORE_COLLECTIONS_IENUMERABLE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Collections
{
	/// Exposes an enumerator, which supports a simple iteration over a non-generic collection.
	template <typename T>
	class IEnumerable
	{
	public:
		/// <summary>
		/// Destroy the object using the virtual destructor
		/// </summary>
		virtual ~IEnumerable() {}

		//virtual Generic::Enumerator<T> GetEnumerator() = 0;

		//virtual Generic::IEnumerator<T> GetEnumerator() = 0;
		//virtual const IEnumerator<T> GetEnumerator() = 0;

		//typedef T iterator;
		//typedef const T const_iterator;

		//virtual iterator& begin() = 0;
		//virtual iterator& end() = 0;

		//virtual const_iterator& begin() = 0;
		//virtual const_iterator& end() = 0;
	};
}
#endif
