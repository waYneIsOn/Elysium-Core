/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEHEAPARRAY
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEHEAPARRAY

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

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	template <Concepts::NonConstant T, const size_t Size, class Allocator = Memory::DefaultAllocator<T>>
	class FixedSizeHeapArray final
	{
	public:
		using Value = T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;

		using FIterator = Iterator::ForwardIterator<FixedSizeHeapArray<T, Size, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<FixedSizeHeapArray<T, Size, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<FixedSizeHeapArray<T, Size, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<FixedSizeHeapArray<T, Size, Allocator>>;
	public:
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		FixedSizeHeapArray();

		/// <summary>
		/// Creates a new fixed size array on the heap copying each element of given InitializerList.
		/// </summary>
		/// <param name="InitializerList"></param>
		FixedSizeHeapArray(const InitializerList<T>& InitializerList);

		/// <summary>
		/// Copies given array to this instance.
		/// </summary>
		/// <param name="Source"></param>
		FixedSizeHeapArray(const FixedSizeHeapArray& Source);

		/// <summary>
		/// Moves given array to this instance.
		/// </summary>
		/// <param name="Right"></param>
		FixedSizeHeapArray(FixedSizeHeapArray&& Right) noexcept;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		~FixedSizeHeapArray();

		/// <summary>
		/// Copies given array to this instance.
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		FixedSizeHeapArray<T, Size, Allocator>& operator=(const FixedSizeHeapArray& Source);

		/// <summary>
		/// Moves given array to this instance.
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		FixedSizeHeapArray<T, Size, Allocator>& operator=(FixedSizeHeapArray&& Right) noexcept;

		/// <summary>
		/// Gets the element at the specified index without checking boundaries.
		/// </summary>
		/// <param name="Index">The zero-based index of the element to get.</param>
		/// <returns></returns>
		ConstReference operator[](const size_t Index) const;

		/// <summary>
		/// Gets the maximum size the internal data structure can hold.
		/// </summary>
		/// <returns></returns>
		static constexpr const size_t GetMaximumSize();

		/// <summary>
		/// Gets the total number of elements of the array.
		/// </summary>
		/// <returns></returns>
		constexpr const size_t GetSize() const noexcept;

		/// <summary>
		/// Gets the internal data structure.
		/// </summary>
		/// <returns></returns>
		constexpr ConstPointer GetData() const noexcept;

		/// <summary>
		/// Gets the element at the specified index while checking boundaries.
		/// </summary>
		/// <param name="Index"></param>
		/// <returns></returns>
		Reference GetAt(const size_t Index);

		/// <summary>
		/// Gets the element at the specified index while checking boundaries.
		/// </summary>
		/// <param name="Index"></param>
		/// <returns></returns>
		ConstReference GetAt(const size_t Index) const;

		/// <summary>
		/// Returns a forward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		FIterator GetBegin();

		/// <summary>
		/// Returns a const forward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		ConstIterator GetBegin() const;

		/// <summary>
		/// Returns a forward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		FIterator GetEnd();

		/// <summary>
		/// Returns a const forward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		ConstIterator GetEnd() const;

		/// <summary>
		/// Returns a backward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		ReverseIterator GetReverseBegin();

		/// <summary>
		/// Returns a const backward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		ConstReverseIterator GetReverseBegin() const;

		/// <summary>
		/// Returns a backward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		ReverseIterator GetReverseEnd();

		/// <summary>
		/// Returns a const backward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		ConstReverseIterator GetReverseEnd() const;
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		Pointer _Data;
	};

	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::FixedSizeHeapArray()
		: _Data(_Allocator.Allocate(Size))
	{ }

	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::FixedSizeHeapArray(const InitializerList<T>& InitializerList)
		: _Data(_Allocator.Allocate(Size))
	{
		const size_t CopyLength = Size < InitializerList.size() ? Size : InitializerList.size();
		Array<T>::Copy(InitializerList.begin(), _Data, CopyLength);
	}

	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::FixedSizeHeapArray(const FixedSizeHeapArray& Source)
		: _Data(_Allocator.Allocate(Size))
	{
		Array<T>::Copy(Source._Data, _Data, Size);
	}

	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::FixedSizeHeapArray(FixedSizeHeapArray&& Right) noexcept
		: _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}
	
	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::~FixedSizeHeapArray()
	{
		_Allocator.Deallocate(_Data, Size);
	}

	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>& FixedSizeHeapArray<T, Size, Allocator>::operator=(const FixedSizeHeapArray& Source)
	{
		if (this != &Source)
		{
			if (_Data != nullptr)
			{
				_Allocator.Deallocate(_Data, Size);
			}

			_Data = _Allocator.Allocate(Size);
			Array<T>::Copy(Source._Data, _Data, Size);
		}
		return *this;
	}

	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>& FixedSizeHeapArray<T, Size, Allocator>::operator=(FixedSizeHeapArray&& Right) noexcept
	{
		if (this != &Right)
		{
			if (_Data != nullptr)
			{
				_Allocator.Deallocate(_Data, Size);
			}

			_Data = Right._Data;

			Right._Data = _Allocator.Allocate(Size);
			Array<T>::Clear(Right._Data, Size);
		}
		return *this;
	}

	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::ConstReference FixedSizeHeapArray<T, Size, Allocator>::operator[](const size_t Index) const
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, size_t Size, class Allocator>
	inline constexpr const size_t FixedSizeHeapArray<T, Size, Allocator>::GetMaximumSize()
	{
		return static_cast<size_t>(-1) / sizeof(T);
	}

	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline constexpr const size_t FixedSizeHeapArray<T, Size, Allocator>::GetSize() const noexcept
	{
		return Size;
	}

	template<Concepts::NonConstant T, size_t Size, class Allocator>
	inline constexpr FixedSizeHeapArray<T, Size, Allocator>::ConstPointer FixedSizeHeapArray<T, Size, Allocator>::GetData() const noexcept
	{
		return _Data;
	}

	template<Concepts::NonConstant T, size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::Reference FixedSizeHeapArray<T, Size, Allocator>::GetAt(const size_t Index)
	{
		if (Index >= Size)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::ConstReference FixedSizeHeapArray<T, Size, Allocator>::GetAt(const size_t Index) const
	{
		if (Index >= Size)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::FIterator FixedSizeHeapArray<T, Size, Allocator>::GetBegin()
	{
		return FIterator(&_Data[0]);
	}
	
	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::ConstIterator FixedSizeHeapArray<T, Size, Allocator>::GetBegin() const
	{
		return ConstIterator(&_Data[0]);
	}
	
	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::FIterator FixedSizeHeapArray<T, Size, Allocator>::GetEnd()
	{
		return FIterator(&_Data[Size]);
	}
	
	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::ConstIterator FixedSizeHeapArray<T, Size, Allocator>::GetEnd() const
	{
		return ConstIterator(&_Data[Size]);
	}
	
	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::ReverseIterator FixedSizeHeapArray<T, Size, Allocator>::GetReverseBegin()
	{
		return ReverseIterator(&_Data[Size - 1]);
	}
	
	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::ConstReverseIterator FixedSizeHeapArray<T, Size, Allocator>::GetReverseBegin() const
	{
		return ConstReverseIterator(&_Data[Size - 1]);
	}
	
	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::ReverseIterator FixedSizeHeapArray<T, Size, Allocator>::GetReverseEnd()
	{
		return ReverseIterator(&_Data[-1]);
	}
	
	template<Concepts::NonConstant T, const size_t Size, class Allocator>
	inline FixedSizeHeapArray<T, Size, Allocator>::ConstReverseIterator FixedSizeHeapArray<T, Size, Allocator>::GetReverseEnd() const
	{
		return ConstReverseIterator(&_Data[-1]);
	}
}
#endif
