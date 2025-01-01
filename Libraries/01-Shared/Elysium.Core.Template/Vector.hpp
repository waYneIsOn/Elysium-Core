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

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COMMON_ENABLEIF
#include "EnableIf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OUTOFMEMORYEXCEPTION
#include "OutOfMemoryException.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVECONSTRUCTIBLE
#include "IsMoveConstructible.hpp"
#endif




// @ToDo: remove asap
namespace Elysium::Core::Collections::Template
{
	template <Elysium::Core::Template::Concepts::NonConstant T>
	class Array;
}




namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	template <Concepts::NonConstant T, class Allocator = Memory::DefaultAllocator<T>>
	class Vector
	{
		// @ToDo: remove asap
		friend class Elysium::Core::Collections::Template::Array<T>;
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
	public:
		using FIterator = Iterator::ForwardIterator<Vector<T, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<Vector<T, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<Vector<T, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<Vector<T, Allocator>>;
	public:
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		constexpr Vector() noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Capacity"></param>
		constexpr Vector(const System::size Capacity);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="InitializerList"></param>
		constexpr Vector(const InitializerList<T>& InitializerList);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		constexpr Vector(const Vector& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		constexpr Vector(Vector&& Right) noexcept;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		constexpr ~Vector();
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		constexpr Vector<T, Allocator>& operator=(const Vector& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		constexpr Vector<T, Allocator>& operator=(Vector&& Right) noexcept;
	public:
		/// <summary>
		/// Returns a reference to the element at the specified index without checking boundaries.
		/// </summary>
		/// <param name="Index"></param>
		/// <returns></returns>
		constexpr Reference operator[](const System::size Index);

		/// <summary>
		/// Returns a const reference to the element at the specified index without checking boundaries.
		/// </summary>
		/// <param name="Index">The zero-based index of the element to get.</param>
		/// <returns></returns>
		constexpr ConstReference operator[](const System::size Index) const;
	public:
		/// <summary>
		/// Gets the maximum size the internal data structure can hold.
		/// </summary>
		/// <returns></returns>
		static constexpr const System::size GetMaximumSize();

		/// <summary>
		/// Gets the total number of elements the internal data structure can hold without resizing.
		/// </summary>
		/// <returns></returns>
		constexpr const System::size GetCapacity() const noexcept;

		/// <summary>
		/// Gets the number of elements contained in the list.
		/// </summary>
		/// <returns></returns>
		constexpr const System::size GetLength() const noexcept;

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
		constexpr Reference GetAt(const System::size Index);

		/// <summary>
		/// Gets the element at the specified index while checking boundaries.
		/// </summary>
		/// <param name="Index"></param>
		/// <returns></returns>
		constexpr ConstReference GetAt(const System::size Index) const;
	public:
		/// <summary>
		/// Returns a forward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		constexpr FIterator GetBegin() noexcept;

		/// <summary>
		/// Returns a const forward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		constexpr ConstIterator GetBegin() const noexcept;

		/// <summary>
		/// Returns a forward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		constexpr FIterator GetEnd() noexcept;

		/// <summary>
		/// Returns a const forward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		constexpr ConstIterator GetEnd() const noexcept;

		/// <summary>
		/// Returns a backward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		constexpr ReverseIterator GetReverseBegin() noexcept;

		/// <summary>
		/// Returns a const backward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		constexpr ConstReverseIterator GetReverseBegin() const noexcept;

		/// <summary>
		/// Returns a backward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		constexpr ReverseIterator GetReverseEnd() noexcept;

		/// <summary>
		/// Returns a const backward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		constexpr ConstReverseIterator GetReverseEnd() const noexcept;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <param name="Length"></param>
		void Assign(ConstValue Value, const System::size Length);

		/// <summary>
		/// Calls destructor for all contained items and sets size to zero. (Does not cause reallocation.)
		/// </summary>
		void Clear();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Value"></param>
		/// <returns></returns>
		constexpr FIterator Erase(ConstValue Value);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Index"></param>
		/// <returns></returns>
		FIterator EraseAt(const System::size Index);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Index"></param>
		/// <param name="Value"></param>
		void Insert(const System::size Index, ConstValue Value);

		/// <summary>
		/// Adds given item to the end of the vector. (May cause reallocation.)
		/// </summary>
		/// <param name="Item"></param>
		constexpr void PushBack(ConstReference Item);

		/// <summary>
		/// Moves given item to the end of the vector. (May cause reallocation.)
		/// </summary>
		/// <param name="Item"></param>
		constexpr void PushBack(RValueReference Item);
			//typename Elysium::Core::Template::Common::EnableIf<Elysium::Core::Template::TypeTraits::IsMoveConstructible<T>::Value>::Type* = nullptr;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <param name="FirstIndex"></param>
		/// <param name="Length"></param>
		void PushBackRange(const Vector<T>& Source, const System::size FirstIndex, const System::size Length);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="FirstItem"></param>
		/// <param name="Length"></param>
		void PushBackRange(ConstPointer FirstItem, const System::size Length);

		/// <summary>
		/// Removes last item. (Does not cause reallocation.)
		/// </summary>
		void PopBack();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="DesiredCapacity"></param>
		void Reserve(const System::size DesiredCapacity);

		/// <summary>
		/// 
		/// </summary>
		void ShrinkToFit();
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		const System::size CalculateCapacityGrowth(const System::size DesiredCapacity);
	private:
		System::size _Capacity;
		System::size _Length;
		Pointer _Data;
	};

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector() noexcept
		: _Capacity(1), _Length(0), _Data(_Allocator.Allocate(_Capacity))
	{ }

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(const Elysium::Core::Template::System::size Capacity)
		: _Capacity(Capacity == 0 ? 1 : Capacity), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{ }

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(const InitializerList<T>& InitializerList)
		: _Capacity(InitializerList.size() == 0 ? 1 : InitializerList.size()), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{
		const Elysium::Core::Template::System::size InitializerListLength = InitializerList.size();
		for (Elysium::Core::Template::System::size i = 0; i < InitializerListLength; i++)
		{
			_Data[i] = InitializerList.begin()[i];
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(const Vector& Source)
		: _Capacity(Source._Capacity), _Length(Source._Length), _Data(_Allocator.Allocate(_Capacity))
	{
		for (Elysium::Core::Template::System::size i = 0; i < _Length; i++)
		{
			_Data[i] = Source._Data[i];
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(Vector&& Right) noexcept
		: _Capacity(0), _Length(0), _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::~Vector()
	{
		_Allocator.Deallocate(_Data, _Length);
	}

	template<Concepts::NonConstant T,  class Allocator>
	inline constexpr Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& Source)
	{
		if (this != &Source)
		{
			if (Source._Capacity > _Capacity)
			{
				_Allocator.Deallocate(_Data, _Length);

				_Capacity = Source._Capacity;
				_Data = _Allocator.Allocate(Source._Capacity);
			}

			_Length = Source._Length;
			for (Elysium::Core::Template::System::size i = 0; i < _Length; i++)
			{
				_Data[i] = Source._Data[i];
			}
		}
		return *this;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& Right) noexcept
	{
		if (this != &Right)
		{
			_Allocator.Deallocate(_Data, _Length);

			_Capacity = Functional::Move(Right._Capacity);
			_Length = Functional::Move(Right._Length);
			_Data = Functional::Move(Right._Data);

			Right._Capacity = 0;
			Right._Length = 0;
			Right._Data = nullptr;
		}
		return *this;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::Reference Vector<T, Allocator>::operator[](const Elysium::Core::Template::System::size Index)
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReference Vector<T, Allocator>::operator[](const Elysium::Core::Template::System::size Index) const
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<T, Allocator>::GetMaximumSize()
	{
		return static_cast<Elysium::Core::Template::System::size>(-1) / sizeof(T);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<T, Allocator>::GetCapacity() const noexcept
	{
		return _Capacity;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<T, Allocator>::GetLength() const noexcept
	{
		return _Length;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstPointer Vector<T, Allocator>::GetData() const noexcept
	{
		return _Data;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr const bool Vector<T, Allocator>::GetIsEmpty() const noexcept
	{
		return _Length == 0;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::Reference Vector<T, Allocator>::GetAt(const Elysium::Core::Template::System::size Index)
	{
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReference Vector<T, Allocator>::GetAt(const Elysium::Core::Template::System::size Index) const
	{
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}
	
	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::FIterator Vector<T, Allocator>::GetBegin() noexcept
	{
		return FIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetBegin() const noexcept
	{
		return ConstIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::FIterator Vector<T, Allocator>::GetEnd() noexcept
	{
		return FIterator(&_Data[_Length - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetEnd() const noexcept
	{
		return ConstIterator(&_Data[_Length - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseBegin() noexcept
	{
		return ReverseIterator(&_Data[_Length - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseBegin() const noexcept
	{
		return ConstReverseIterator(&_Data[_Length - 1]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseEnd() noexcept
	{
		return ReverseIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseEnd() const noexcept
	{
		return ConstReverseIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::Assign(ConstValue Value, const Elysium::Core::Template::System::size Length)
	{
		const Elysium::Core::Template::System::size RequiredSize = _Length + Length;
		if (RequiredSize > _Capacity)
		{
			Reserve(CalculateCapacityGrowth(RequiredSize));
		}

		for (Elysium::Core::Template::System::size i = 0; i < Length; i++)
		{
			_Data[_Length++] = Value;
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::Clear()
	{
		for (Elysium::Core::Template::System::size i = 0; i < _Length; i++)
		{
			_Data[i].~T();
		}

		_Length = 0;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr Container::Vector<T, Allocator>::FIterator Container::Vector<T, Allocator>::Erase(ConstValue Value)
	{
		for (System::size i = 0; i < _Length; i++)
		{
			if (_Data[i] == Value)
			{
				return EraseAt(i);
			}
		}

		// ToDo: have a look at std::vector::erase in regards to returning the last element?
		return GetEnd();
	}

	template<Concepts::NonConstant T, class Allocator>
	inline Container::Vector<T, Allocator>::FIterator Container::Vector<T, Allocator>::EraseAt(const System::size Index)
	{	// @ToDo: have a look at std::vector::erase in regards to returning the last element?
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		// ToDo: I think, in this case we can actually use memcpy - if I'm wrong at some point, use the code below 
		memcpy(&_Data[Index], &_Data[Index + 1], sizeof(T)* (_Length - Index));
		/*
		// move all old elements right of InsertionIndex to _Data using the move constructor
		for (Elysium::Core::size i = Index; i < _Count; i++)
		{
			_Data[i] = Elysium::Core::Template::Functional::Move(_Data[i + 1]);
		}
		*/
		_Length--;

		return GetEnd();
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::Insert(const Elysium::Core::Template::System::size Index, ConstValue Value)
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
	inline constexpr void Vector<T, Allocator>::PushBack(ConstReference Item)
	{
		if (_Length == _Capacity)
		{
			Reserve(CalculateCapacityGrowth(_Capacity + 1));
		}

		_Data[_Length++] = Item;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline constexpr void Vector<T, Allocator>::PushBack(RValueReference Item)
	{
		if (_Length == _Capacity)
		{
			Reserve(CalculateCapacityGrowth(_Capacity + 1));
		}

		_Data[_Length++] = Functional::Move(Item);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::PushBackRange(const Vector<T>& Source, const Elysium::Core::Template::System::size FirstIndex, const Elysium::Core::Template::System::size Length)
	{
		PushBackRange(&Source[FirstIndex], Length);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::PushBackRange(ConstPointer FirstItem, const Elysium::Core::Template::System::size Length)
	{
		const Elysium::Core::Template::System::size RequiredSize = _Length + Length;
		if (RequiredSize > _Capacity)
		{
			Reserve(CalculateCapacityGrowth(RequiredSize));
		}

		for (Elysium::Core::Template::System::size i = 0; i < Length; i++)
		{
			_Data[_Length++] = FirstItem[i];
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::PopBack()
	{
		if (_Length > 0)
		{
			_Data[_Length--].~T();
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::Reserve(const Elysium::Core::Template::System::size DesiredCapacity)
	{
		if (DesiredCapacity > _Capacity)
		{
			Pointer OldData = _Data;
			_Capacity = CalculateCapacityGrowth(DesiredCapacity);
			_Data = _Allocator.Allocate(_Capacity);

			for (Elysium::Core::Template::System::size i = 0; i < _Length; i++)
			{
				_Data[i] = Functional::Move(OldData[i]);
			}

			_Allocator.Deallocate(OldData, _Length);
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline void Vector<T, Allocator>::ShrinkToFit()
	{
		if (_Length != _Capacity)
		{
			/*
			// option 1: simply set capacity to size (no copies/moves caused but memory partially stays unused until another reallocation happens)
			_Capacity = _Size;
			*/
			// option 2: reallocate (while copies/moves might happen, the memory used is exactly as much as required)
			Pointer OldData = _Data;
			_Capacity = _Length;
			_Data = _Allocator.Allocate(_Capacity);

			for (Elysium::Core::Template::System::size i = 0; i < _Length; i++)
			{
				_Data[i] = Functional::Move(OldData[i]);
			}

			_Allocator.Deallocate(OldData, _Length);
		}
	}

	template<Concepts::NonConstant T, class Allocator>
	inline const Elysium::Core::Template::System::size Vector<T, Allocator>::CalculateCapacityGrowth(const Elysium::Core::Template::System::size DesiredCapacity)
	{
		constexpr const Elysium::Core::Template::System::size MaximumSize = GetMaximumSize();
		if (_Capacity == MaximumSize)
		{
			throw Exceptions::OutOfMemoryException();
		}

		constexpr const Elysium::Core::Template::System::size GrowthFactor = 2;	// ToDo: check whether a growth factor of 1.5 (double!) would be better
		Elysium::Core::Template::System::size NewCapacity = _Capacity == 0 ? 1 : _Capacity * GrowthFactor;
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
	/*
	// @ToDo: implement specialization (SOO as well?)
	template <bool, class Allocator = Memory::DefaultAllocator<bool>>
	class Vector
	{ };
	*/
}
#endif
