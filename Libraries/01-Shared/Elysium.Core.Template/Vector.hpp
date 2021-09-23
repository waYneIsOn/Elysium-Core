/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR

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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_BACKWARDITERATOR
#include "BackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_CONSTBACKWARDITERATOR
#include "ConstBackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_CONSTFORWARDITERATOR
#include "ConstForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FORWARDITERATOR
#include "ForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "InitializerList.hpp"
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
	template <Concepts::NonConstant T, class Allocator = DefaultAllocator<T>>
	class Vector final
	{
	public:
		using Value = T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;

		using Iterator = ForwardIterator<Vector<T, Allocator>>;
		using ConstIterator = ConstForwardIterator<Vector<T, Allocator>>;

		using ReverseIterator = BackwardIterator<Vector<T, Allocator>>;
		using ConstReverseIterator = ConstBackwardIterator<Vector<T, Allocator>>;
	private:
		inline static Allocator _Allocator = Allocator();
	public:
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		Vector();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Capacity"></param>
		Vector(const size_t Capacity);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="InitializerList"></param>
		Vector(const InitializerList<T>& InitializerList);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		Vector(const Vector& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		Vector(Vector&& Right) noexcept;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		~Vector();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		Vector<T, Allocator>& operator=(const Vector& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		Vector<T, Allocator>& operator=(Vector&& Right) noexcept;

		/// <summary>
		/// Gets or sets the element at the specified index without checking boundaries. 
		/// </summary>
		/// <param name="Index">The zero-based index of the element to get or set.</param>
		/// <returns></returns>
		Reference operator[](const size_t Index);

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
		/// Gets the total number of elements the internal data structure can hold without resizing.
		/// </summary>
		/// <returns></returns>
		constexpr const size_t GetCapacity() const noexcept;

		/// <summary>
		/// Gets the number of elements contained in the list.
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
		/// Sets the total number of elements the internal data structure can hold.
		/// </summary>
		/// <param name="Value"></param>
		void SetCapacity(const size_t Value);

		/// <summary>
		/// Returns a forward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		Iterator GetBegin();

		/// <summary>
		/// Returns a const forward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		ConstIterator GetBegin() const;

		/// <summary>
		/// Returns a forward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		Iterator GetEnd();

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

		/// <summary>
		/// 
		/// </summary>
		void Clear();
	private:
		size_t _Capacity;
		size_t _Count;
		Pointer _Data;
	};

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector()
		: _Capacity(0), _Count(0), _Data(nullptr)
	{ }

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector(const size_t Capacity)
		: _Capacity(Capacity), _Count(0), _Data(_Allocator.Allocate(_Capacity))
	{ }

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector(const InitializerList<T>& InitializerList)
		: _Capacity(InitializerList.size()), _Count(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{
		Array<T>::Copy(InitializerList.begin(), _Data, _Capacity);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector(const Vector& Source)
		: _Capacity(Source._Capacity), _Count(Source._Count), _Data(_Allocator.Allocate(_Capacity))
	{
		Array<T>::Copy(Source._Data, _Data, _Capacity);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector(Vector&& Right) noexcept
		: _Capacity(0), _Count(0), _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::~Vector()
	{
		_Allocator.Deallocate(_Data, _Count);
	}

	template<Concepts::NonConstant T,  class Allocator>
	inline Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& Source)
	{
		if (this != &Source)
		{
			if (Source._Capacity > _Capacity)
			{
				_Allocator.Deallocate(_Data, _Count);

				_Capacity = Source._Capacity;
				_Data = _Allocator.Allocate(Source._Capacity);
			}

			_Count = Source._Count;
			Array<T>::Copy(Source._Data, _Data, _Capacity);
			/*
			if (_Capacity > Source._Capacity)
			{
				Array<T>::Clear(&_Data[_Capacity - Source._Capacity - 1], _Capacity - Source._Capacity);
			}
			*/
		}
		return *this;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& Right) noexcept
	{
		if (this != &Right)
		{
			_Allocator.Deallocate(_Data, _Count);

			_Capacity = Functional::Move(Right._Capacity);
			_Count = Functional::Move(Right._Count);
			_Data = Functional::Move(Right._Data);

			Right._Capacity = 0;
			Right._Count = 0;
			Right._Data = nullptr;
		}
		return *this;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Reference Vector<T, Allocator>::operator[](const size_t Index)
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstReference Vector<T, Allocator>::operator[](const size_t Index) const
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const size_t Vector<T, Allocator>::GetMaximumSize()
	{
		return static_cast<size_t>(-1) / sizeof(T);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const size_t Vector<T, Allocator>::GetCapacity() const noexcept
	{
		return _Capacity;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const size_t Vector<T, Allocator>::GetSize() const noexcept
	{
		return _Count;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstPointer Vector<T, Allocator>::GetData() const noexcept
	{
		return _Data;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Reference Vector<T, Allocator>::GetAt(const size_t Index)
	{
		if (Index >= _Count)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}
	
	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstReference Vector<T, Allocator>::GetAt(const size_t Index) const
	{
		if (Index >= _Count)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::SetCapacity(const size_t Value)
	{
		if (Value >= _Capacity)
		{
			return;
		}

		const size_t OldCount = _Count;
		Pointer OldData = _Data;
		_Capacity = Value;
		_Data = _Allocator.Allocate(_Capacity);

		for (size_t i = 0; i < _Count; i++)
		{
			_Data[i] = Functional::Move(OldData[0]);
		}

		_Allocator.Deallocate(OldData, OldCount);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Iterator Vector<T, Allocator>::GetBegin()
	{
		return Iterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetBegin() const
	{
		return ConstIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Iterator Vector<T, Allocator>::GetEnd()
	{
		return Iterator(&_Data[_Count]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetEnd() const
	{
		return ConstIterator(&_Data[_Count]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseBegin()
	{
		return ReverseIterator(&_Data[_Count - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseBegin() const
	{
		return ConstReverseIterator(&_Data[_Count - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseEnd()
	{
		return ReverseIterator(&_Data[-1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseEnd() const
	{
		return ConstReverseIterator(&_Data[-1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::Clear()
	{
		_Count = 0;
	}
}
#endif
