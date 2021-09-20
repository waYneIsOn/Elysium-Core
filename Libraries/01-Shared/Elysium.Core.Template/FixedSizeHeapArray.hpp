/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_FIXEDSIZEHEAPARRAY
#define ELYSIUM_CORE_TEMPLATE_COLLECTIONS_FIXEDSIZEHEAPARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_ARRAY
#include "Array.hpp"
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
	template <class T, const size_t Length, class Allocator = DefaultAllocator<T>>
	class FixedSizeHeapArray final
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
	private:
		inline static Allocator _Allocator = Allocator();
		inline static const size_t ElementSize = sizeof(T);
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="PerformMemoryClear"></param>
		FixedSizeHeapArray(const bool PerformMemoryClear = false);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="InitializerList"></param>
		FixedSizeHeapArray(const InitializerList<T>& InitializerList);

		/// <summary>
		/// Copies given array.
		/// </summary>
		/// <param name="Source"></param>
		FixedSizeHeapArray(const FixedSizeHeapArray& Source);

		/// <summary>
		/// Moves given array.
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		FixedSizeHeapArray(FixedSizeHeapArray&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		~FixedSizeHeapArray();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		FixedSizeHeapArray<T, Length, Allocator>& operator=(const FixedSizeHeapArray& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		FixedSizeHeapArray<T, Length, Allocator>& operator=(FixedSizeHeapArray&& Right) noexcept;

		/// <summary>
		/// Gets or sets the element at the specified index. 
		/// </summary>
		/// <param name="Index">The zero-based index of the element to get or set.</param>
		/// <returns></returns>
		Reference operator[](const size_t Index);

		/// <summary>
		/// Gets the element at the specified index.
		/// </summary>
		/// <param name="Index">The zero-based index of the element to get.</param>
		/// <returns></returns>
		ConstReference operator[](const size_t Index) const;

		/// <summary>
		/// Gets the total number of elements.
		/// </summary>
		/// <returns></returns>
		constexpr const size_t GetLength() const noexcept;

		/// <summary>
		/// Returns a forward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		Iterator GetBegin();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		//ConstIterator GetBegin() const;

		/// <summary>
		/// Returns a forward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		Iterator GetEnd();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		//ConstIterator GetEnd() const;

		/// <summary>
		/// Returns a backward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		ReverseIterator GetReverseBegin();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		//ConstReverseIterator GetReverseBegin() const;

		/// <summary>
		/// Returns a backward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		ReverseIterator GetReverseEnd();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		//ConstReverseIterator GetReverseEnd() const;
	private:
		T* _Data;
	};

	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::FixedSizeHeapArray(const bool PerformMemoryClear)
		: _Data(_Allocator.Allocate(Length))
	{
		if (PerformMemoryClear && _Data != nullptr)
		{
			Array<T>::Clear(_Data, Length);
		}
	}

	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::FixedSizeHeapArray(const InitializerList<T>& InitializerList)
		: _Data(_Allocator.Allocate(Length))
	{
		const size_t CopyLength = Length < InitializerList.size() ? Length : InitializerList.size();

		Array<T>::Copy(InitializerList.begin(), _Data, CopyLength);
	}

	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::FixedSizeHeapArray(const FixedSizeHeapArray& Source)
		: _Data(_Allocator.Allocate(Length))
	{
		Array<T>::Copy(Source._Data, _Data, Length);
	}

	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::FixedSizeHeapArray(FixedSizeHeapArray&& Right) noexcept
		: _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}
	
	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::~FixedSizeHeapArray()
	{
		_Allocator.Deallocate(_Data, Length);
	}

	template<class T, size_t Length, class Allocator>
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

	template<class T, size_t Length, class Allocator>
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
			Array<T>::Clear(Right._Data, Length);
		}
		return *this;
	}

	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::Reference FixedSizeHeapArray<T, Length, Allocator>::operator[](const size_t Index)
	{
		if (Index >= Length)
		{
			throw 1;
			// ToDo:
			//throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::ConstReference FixedSizeHeapArray<T, Length, Allocator>::operator[](const size_t Index) const
	{
		if (Index >= Length)
		{
			throw 1;
			// ToDo:
			//throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<class T, size_t Length, class Allocator>
	inline constexpr const size_t FixedSizeHeapArray<T, Length, Allocator>::GetLength() const noexcept
	{
		return Length;
	}

	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::Iterator FixedSizeHeapArray<T, Length, Allocator>::GetBegin()
	{
		return Iterator(&_Data[0]);
	}
	/*
	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::ConstIterator FixedSizeHeapArray<T, Length, Allocator>::GetBegin() const
	{
		return Iterator(&_Data[0]);
	}
	*/
	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::Iterator FixedSizeHeapArray<T, Length, Allocator>::GetEnd()
	{
		return Iterator(&_Data[Length]);
	}
	/*
	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::ConstIterator FixedSizeHeapArray<T, Length, Allocator>::GetEnd() const
	{
		return Iterator(&_Data[Length]);
	}
	*/
	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::ReverseIterator FixedSizeHeapArray<T, Length, Allocator>::GetReverseBegin()
	{
		return ReverseIterator(&_Data[Length - 1]);
	}
	/*
	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::ConstReverseIterator FixedSizeHeapArray<T, Length, Allocator>::GetReverseBegin() const
	{
		return ReverseIterator(&_Data[Length - 1]);
	}
	*/
	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::ReverseIterator FixedSizeHeapArray<T, Length, Allocator>::GetReverseEnd()
	{
		return ReverseIterator(&_Data[-1]);
	}
	/*
	template<class T, size_t Length, class Allocator>
	inline FixedSizeHeapArray<T, Length, Allocator>::ConstReverseIterator FixedSizeHeapArray<T, Length, Allocator>::GetReverseEnd() const
	{
		return ReverseIterator(&_Data[-1]);
	}
	*/
}
#endif
