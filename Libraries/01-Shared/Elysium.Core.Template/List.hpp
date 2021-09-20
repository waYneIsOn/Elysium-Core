/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_LIST
#define ELYSIUM_CORE_TEMPLATE_COLLECTIONS_LIST

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_BACKWARDITERATOR
#include "BackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_FORWARDITERATOR
#include "ForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_INITIALIZERLIST
#include "InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Collections
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	template <class T, class Allocator = DefaultAllocator<T>>
	class List final
	{
	public:
		using Value = T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;

		using Iterator = ForwardIterator<FixedSizeHeapArray<T, Length, Allocator>>;
		using ConstIterator = const ForwardIterator<FixedSizeHeapArray<T, Length, Allocator>>;

		using ReverseIterator = BackwardIterator<FixedSizeHeapArray<T, Length, Allocator>>;
		using ConstReverseIterator = const BackwardIterator<FixedSizeHeapArray<T, Length, Allocator>>;

		static const size_t MaximumSize = static_cast<size_t>(-1);
	private:
		inline static Allocator _Allocator = Allocator();
		inline static const size_t ElementSize = sizeof(T);
	public:

	};
}
#endif
