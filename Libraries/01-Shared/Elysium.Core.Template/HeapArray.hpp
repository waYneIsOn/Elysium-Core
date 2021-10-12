/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_HEAPARRAY
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_HEAPARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "../Elysium.Core/IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_BACKWARDITERATOR
#include "BackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTBACKWARDITERATOR
#include "ConstBackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTFORWARDITERATOR
#include "ConstForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_FORWARDITERATOR
#include "ForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif
/*
namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	template <Concepts::NonConstant T, class Allocator = Memory::DefaultAllocator<T>>
	class HeapArray final
	{
	public:
		using Value = T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;

		using FIterator = Iterator::ForwardIterator<HeapArray<T, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<HeapArray<T, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<HeapArray<T, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<HeapArray<T, Allocator>>;
	public:
		HeapArray(const size_t Length);
		HeapArray(const InitializerList<T>& InitializerList);
		HeapArray(const HeapArray& Source);
		HeapArray(HeapArray&& Right) noexcept;
		~HeapArray();

		HeapArray<T, Allocator>& operator=(const HeapArray& Source);
		HeapArray<T, Allocator>& operator=(HeapArray&& Right) noexcept;

		Reference operator[](const size_t Index);
		ConstReference operator[](const size_t Index) const;

		static constexpr const size_t GetMaximumSize();

		constexpr const size_t GetSize() const noexcept;

		constexpr ConstPointer GetData() const noexcept;

		Reference GetAt(const size_t Index);

		ConstReference GetAt(const size_t Index) const;

		FIterator GetBegin();
		ConstIterator GetBegin() const;

		FIterator GetEnd();
		ConstIterator GetEnd() const;

		ReverseIterator GetReverseBegin();
		ConstReverseIterator GetReverseBegin() const;

		ReverseIterator GetReverseEnd();
		ConstReverseIterator GetReverseEnd() const;
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		size_t _Size;
		Pointer _Data;
	};
}
*/
#endif
