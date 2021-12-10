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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
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

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	template <Concepts::NonConstant T, class Allocator = Memory::DefaultAllocator<T>>
	class Vector final
	{
	public:
		using Value = T;
		using ConstValue = const T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;
		using RValueReference = T&&;

		using IteratorPointer = T*;
		using IteratorReference = T&;
		using ConstIteratorReference = const T&;

		using FIterator = Iterator::ForwardIterator<Vector<T, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<Vector<T, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<Vector<T, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<Vector<T, Allocator>>;
	public:
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		Vector() noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Capacity"></param>
		Vector(const Elysium::Core::size Capacity);

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
	public:
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
	public:
		/// <summary>
		/// Returns a reference to the element at the specified index without checking boundaries.
		/// </summary>
		/// <param name="Index"></param>
		/// <returns></returns>
		Reference operator[](const Elysium::Core::size Index);

		/// <summary>
		/// Returns a const reference to the element at the specified index without checking boundaries.
		/// </summary>
		/// <param name="Index">The zero-based index of the element to get.</param>
		/// <returns></returns>
		ConstReference operator[](const Elysium::Core::size Index) const;
	public:
		/// <summary>
		/// Gets the maximum size the internal data structure can hold.
		/// </summary>
		/// <returns></returns>
		static constexpr const Elysium::Core::size GetMaximumSize();

		/// <summary>
		/// Gets the total number of elements the internal data structure can hold without resizing.
		/// </summary>
		/// <returns></returns>
		constexpr const Elysium::Core::size GetCapacity() const noexcept;

		/// <summary>
		/// Gets the number of elements contained in the list.
		/// </summary>
		/// <returns></returns>
		constexpr const Elysium::Core::size GetLength() const noexcept;

		/// <summary>
		/// Gets the internal data structure.
		/// </summary>
		/// <returns></returns>
		constexpr ConstPointer GetData() const noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		constexpr const bool GetIsEmpty() const noexcept;

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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <param name="Length"></param>
		void Assign(ConstValue Value, const Elysium::Core::size Length);

		/// <summary>
		/// Calls destructor for all contained items and sets size to zero. (Does not cause reallocation.)
		/// </summary>
		void Clear();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <param name="Index"></param>
		void Insert(ConstValue Value, const Elysium::Core::size Index);

		/// <summary>
		/// Adds given item to the end of the vector. (May cause reallocation.)
		/// </summary>
		/// <param name="Item"></param>
		void PushBack(ConstReference Item);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Item"></param>
		void PushBack(RValueReference Item);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <param name="FirstIndex"></param>
		/// <param name="Length"></param>
		void PushBackRange(const Vector<T>& Source, const Elysium::Core::size FirstIndex, const Elysium::Core::size Length);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="FirstItem"></param>
		/// <param name="Length"></param>
		void PushBackRange(ConstPointer FirstItem, const Elysium::Core::size Length);

		/// <summary>
		/// Removes last item. (Does not cause reallocation.)
		/// </summary>
		void PopBack();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="DesiredCapacity"></param>
		void Reserve(const Elysium::Core::size DesiredCapacity);

		/// <summary>
		/// 
		/// </summary>
		void ShrinkToFit();
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		Elysium::Core::size _Capacity;
		Elysium::Core::size _Size;
		Pointer _Data;
	private:
		const Elysium::Core::size CalculateCapacityGrowth(const Elysium::Core::size DesiredCapacity);
	};

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector() noexcept
		: _Capacity(1), _Size(0), _Data(_Allocator.Allocate(_Capacity))
	{ }

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector(const Elysium::Core::size Capacity)
		: _Capacity(Capacity == 0 ? 1 : Capacity), _Size(0), _Data(_Allocator.Allocate(_Capacity))
	{ }

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector(const InitializerList<T>& InitializerList)
		: _Capacity(InitializerList.size() == 0 ? 1 : InitializerList.size()), _Size(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{
		Array<T>::Copy(InitializerList.begin(), _Data, _Capacity);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector(const Vector& Source)
		: _Capacity(Source._Capacity), _Size(Source._Size), _Data(_Allocator.Allocate(_Capacity))
	{
		Array<T>::Copy(Source._Data, _Data, _Size);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Vector(Vector&& Right) noexcept
		: _Capacity(0), _Size(0), _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::~Vector()
	{
		_Allocator.Deallocate(_Data, _Size);
	}

	template<Concepts::NonConstant T,  class Allocator>
	inline Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& Source)
	{
		if (this != &Source)
		{
			if (Source._Capacity > _Capacity)
			{
				_Allocator.Deallocate(_Data, _Size);

				_Capacity = Source._Capacity;
				_Data = _Allocator.Allocate(Source._Capacity);
			}

			_Size = Source._Size;
			Array<T>::Copy(Source._Data, _Data, _Size);
		}
		return *this;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& Right) noexcept
	{
		if (this != &Right)
		{
			_Allocator.Deallocate(_Data, _Size);

			_Capacity = Functional::Move(Right._Capacity);
			_Size = Functional::Move(Right._Size);
			_Data = Functional::Move(Right._Data);

			Right._Capacity = 0;
			Right._Size = 0;
			Right._Data = nullptr;
		}
		return *this;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Reference Vector<T, Allocator>::operator[](const Elysium::Core::size Index)
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstReference Vector<T, Allocator>::operator[](const Elysium::Core::size Index) const
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const Elysium::Core::size Vector<T, Allocator>::GetMaximumSize()
	{
		return static_cast<Elysium::Core::size>(-1) / sizeof(T);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const Elysium::Core::size Vector<T, Allocator>::GetCapacity() const noexcept
	{
		return _Capacity;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const Elysium::Core::size Vector<T, Allocator>::GetLength() const noexcept
	{
		return _Size;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstPointer Vector<T, Allocator>::GetData() const noexcept
	{
		return _Data;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const bool Vector<T, Allocator>::GetIsEmpty() const noexcept
	{
		return _Size == 0;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::Reference Vector<T, Allocator>::GetAt(const Elysium::Core::size Index)
	{
		if (Index >= _Size)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstReference Vector<T, Allocator>::GetAt(const Elysium::Core::size Index) const
	{
		if (Index >= _Size)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}
	
	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::FIterator Vector<T, Allocator>::GetBegin()
	{
		return FIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetBegin() const
	{
		return ConstIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::FIterator Vector<T, Allocator>::GetEnd()
	{
		return FIterator(&_Data[_Size - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetEnd() const
	{
		return ConstIterator(&_Data[_Size - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseBegin()
	{
		return ReverseIterator(&_Data[_Size - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseBegin() const
	{
		return ConstReverseIterator(&_Data[_Size - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseEnd()
	{
		return ReverseIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseEnd() const
	{
		return ConstReverseIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::Assign(ConstValue Value, const Elysium::Core::size Length)
	{
		const Elysium::Core::size RequiredSize = _Size + Length;
		if (RequiredSize > _Capacity)
		{
			Reserve(CalculateCapacityGrowth(RequiredSize));
		}

		for (Elysium::Core::size i = 0; i < Length; i++)
		{
			_Data[_Size++] = Value;
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::Clear()
	{
		for (Elysium::Core::size i = 0; i < _Size; i++)
		{
			_Data[i].~T();
		}

		_Size = 0;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::Insert(ConstValue Value, const Elysium::Core::size Index)
	{
		/*
		if (_Size == _Capacity)
		{	// don't call Reserve(...) here as to reduce the amount of copies/moves
			Pointer OldData = _Data;
			_Capacity = CalculateCapacityGrowth(_Capacity + 1);
			_Data = _Allocator.Allocate(_Capacity);

			Array<T>::Move(OldData, _Data, Index);
			_Data[Index] = Value;
			//Array<T>::Move(OldData, _Data, Index);

			_Allocator.Deallocate(OldData, _Size);
		}
		else
		{

		}
		*/
		throw 1;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::PushBack(ConstReference Item)
	{
		if (_Size == _Capacity)
		{
			Reserve(CalculateCapacityGrowth(_Capacity + 1));
		}

		_Data[_Size++] = Item;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::PushBack(RValueReference Item)
	{
		if (_Size == _Capacity)
		{
			Reserve(CalculateCapacityGrowth(_Capacity + 1));
		}

		_Data[_Size++] = Functional::Move(Item);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::PushBackRange(const Vector<T>& Source, const Elysium::Core::size FirstIndex, const Elysium::Core::size Length)
	{
		PushBackRange(&Source[FirstIndex], Length);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::PushBackRange(ConstPointer FirstItem, const Elysium::Core::size Length)
	{
		const Elysium::Core::size RequiredSize = _Size + Length;
		if (RequiredSize > _Capacity)
		{
			Reserve(CalculateCapacityGrowth(RequiredSize));
		}

		for (Elysium::Core::size i = 0; i < Length; i++)
		{
			_Data[_Size++] = FirstItem[i];
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::PopBack()
	{
		if (_Size > 0)
		{
			_Data[_Size--].~T();
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::Reserve(const Elysium::Core::size DesiredCapacity)
	{
		if (DesiredCapacity > _Capacity)
		{
			Pointer OldData = _Data;
			_Capacity = CalculateCapacityGrowth(DesiredCapacity);
			_Data = _Allocator.Allocate(_Capacity);

			Array<T>::Move(OldData, _Data, _Size);

			_Allocator.Deallocate(OldData, _Size);
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::ShrinkToFit()
	{
		if (_Size != _Capacity)
		{
			/*
			// option 1: simply set capacity to size (no copies/moves caused but memory partially stays unused until another reallocation happens)
			_Capacity = _Size;
			*/
			// option 2: reallocate (while copies/moves might happen, the memory used is exactly as much as required)
			Pointer OldData = _Data;
			_Capacity = _Size;
			_Data = _Allocator.Allocate(_Capacity);

			Array<T>::Move(OldData, _Data, _Size);

			_Allocator.Deallocate(OldData, _Size);
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline const Elysium::Core::size Vector<T, Allocator>::CalculateCapacityGrowth(const Elysium::Core::size DesiredCapacity)
	{
		constexpr const Elysium::Core::size MaximumSize = GetMaximumSize();
		if (_Capacity == MaximumSize)
		{
			// ToDo: throw specific exception (no more memory can be allocated!)
			throw 1;
		}

		constexpr const double GrowthFactor = 2;	// ToDo: check whether a growth factor of 1.5 would be better
		Elysium::Core::size NewCapacity = _Capacity == 0 ? 1 : _Capacity * GrowthFactor;
		while (NewCapacity < DesiredCapacity)
		{
			NewCapacity *= GrowthFactor;
		}
		if (NewCapacity > MaximumSize)
		{
			return MaximumSize;
		}

		return NewCapacity;
	}
}
#endif
