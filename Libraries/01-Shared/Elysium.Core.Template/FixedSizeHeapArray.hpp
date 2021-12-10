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
	template <Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator = Memory::DefaultAllocator<T>>
	class FixedSizeHeapArray final
	{
	public:
		using Value = T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;

		using IteratorPointer = T*;
		using IteratorReference = T&;
		using ConstIteratorReference = const T&;

		using FIterator = Iterator::ForwardIterator<FixedSizeHeapArray<T, Length, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<FixedSizeHeapArray<T, Length, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<FixedSizeHeapArray<T, Length, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<FixedSizeHeapArray<T, Length, Allocator>>;
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
	public:
		/// <summary>
		/// Copies given array to this instance.
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		FixedSizeHeapArray<T, Length, Allocator>& operator=(const FixedSizeHeapArray& Source);

		/// <summary>
		/// Moves given array to this instance.
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		FixedSizeHeapArray<T, Length, Allocator>& operator=(FixedSizeHeapArray&& Right) noexcept;

		/// <summary>
		/// Gets the element at the specified index without checking boundaries.
		/// </summary>
		/// <param name="Index">The zero-based index of the element to get.</param>
		/// <returns></returns>
		ConstReference operator[](const Elysium::Core::size Index) const;

		/// <summary>
		/// Gets the maximum size the internal data structure can hold.
		/// </summary>
		/// <returns></returns>
		static constexpr const Elysium::Core::size GetMaximumLength();

		/// <summary>
		/// Gets the total number of elements of the array.
		/// </summary>
		/// <returns></returns>
		constexpr const Elysium::Core::size GetLength() const noexcept;

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
		Reference GetAt(const Elysium::Core::size Index);

		/// <summary>
		/// Gets the element at the specified index while checking boundaries.
		/// </summary>
		/// <param name="Index"></param>
		/// <returns></returns>
		ConstReference GetAt(const Elysium::Core::size Index) const;

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

	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::FixedSizeHeapArray()
		: _Data(_Allocator.Allocate(Length))
	{ }

	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::FixedSizeHeapArray(const InitializerList<T>& InitializerList)
		: _Data(_Allocator.Allocate(Length))
	{
		const Elysium::Core::size CopyLength = Length < InitializerList.size() ? Length : InitializerList.size();
		Array<T>::Copy(InitializerList.begin(), _Data, CopyLength);
	}

	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::FixedSizeHeapArray(const FixedSizeHeapArray& Source)
		: _Data(_Allocator.Allocate(Length))
	{
		Array<T>::Copy(Source._Data, _Data, Length);
	}

	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::FixedSizeHeapArray(FixedSizeHeapArray&& Right) noexcept
		: _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}
	
	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::~FixedSizeHeapArray()
	{
		_Allocator.Deallocate(_Data, Length);
	}

	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>& FixedSizeHeapArray<T, Length, Allocator>::operator=(const FixedSizeHeapArray& Source)
	{
		if (this != &Source)
		{
			if (_Data != nullptr)
			{
				_Allocator.Deallocate(_Data, Length);
			}

			_Data = _Allocator.Allocate(Length);
			Array<T>::Copy(Source._Data, _Data, Length);
		}
		return *this;
	}

	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>& FixedSizeHeapArray<T, Length, Allocator>::operator=(FixedSizeHeapArray&& Right) noexcept
	{
		if (this != &Right)
		{
			if (_Data != nullptr)
			{
				_Allocator.Deallocate(_Data, Length);
			}

			_Data = Right._Data;

			Right._Data = _Allocator.Allocate(Length);
			memset(&Right._Data[0], 0x00, sizeof(T) * Length);
		}
		return *this;
	}

	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::ConstReference FixedSizeHeapArray<T, Length, Allocator>::operator[](const Elysium::Core::size Index) const
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, Elysium::Core::size Length, class Allocator>
	inline constexpr const Elysium::Core::size FixedSizeHeapArray<T, Length, Allocator>::GetMaximumLength()
	{
		return static_cast<Elysium::Core::size>(-1) / sizeof(T);
	}

	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline constexpr const Elysium::Core::size FixedSizeHeapArray<T, Length, Allocator>::GetLength() const noexcept
	{
		return Length;
	}

	template<Concepts::NonConstant T, Elysium::Core::size Length, class Allocator>
	inline constexpr typename FixedSizeHeapArray<T, Length, Allocator>::ConstPointer FixedSizeHeapArray<T, Length, Allocator>::GetData() const noexcept
	{
		return _Data;
	}

	template<Concepts::NonConstant T, Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::Reference FixedSizeHeapArray<T, Length, Allocator>::GetAt(const Elysium::Core::size Index)
	{
		if (Index >= Length)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::ConstReference FixedSizeHeapArray<T, Length, Allocator>::GetAt(const Elysium::Core::size Index) const
	{
		if (Index >= Length)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::FIterator FixedSizeHeapArray<T, Length, Allocator>::GetBegin()
	{
		return FIterator(&_Data[0]);
	}
	
	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::ConstIterator FixedSizeHeapArray<T, Length, Allocator>::GetBegin() const
	{
		return ConstIterator(&_Data[0]);
	}
	
	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::FIterator FixedSizeHeapArray<T, Length, Allocator>::GetEnd()
	{
		return FIterator(&_Data[Length - 1]);
	}
	
	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::ConstIterator FixedSizeHeapArray<T, Length, Allocator>::GetEnd() const
	{
		return ConstIterator(&_Data[Length - 1]);
	}
	
	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::ReverseIterator FixedSizeHeapArray<T, Length, Allocator>::GetReverseBegin()
	{
		return ReverseIterator(&_Data[Length - 1]);
	}
	
	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::ConstReverseIterator FixedSizeHeapArray<T, Length, Allocator>::GetReverseBegin() const
	{
		return ConstReverseIterator(&_Data[Length - 1]);
	}
	
	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::ReverseIterator FixedSizeHeapArray<T, Length, Allocator>::GetReverseEnd()
	{
		return ReverseIterator(&_Data[0]);
	}
	
	template<Concepts::NonConstant T, const Elysium::Core::size Length, class Allocator>
	inline typename FixedSizeHeapArray<T, Length, Allocator>::ConstReverseIterator FixedSizeHeapArray<T, Length, Allocator>::GetReverseEnd() const
	{
		return ConstReverseIterator(&_Data[0]);
	}
}
#endif
