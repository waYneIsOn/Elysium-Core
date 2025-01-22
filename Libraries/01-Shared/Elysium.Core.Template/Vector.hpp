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

#ifndef ELYSIUM_CORE_TEMPLATE_COMMON_ENABLEIF
#include "EnableIf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ALLOCATABLE
#include "Concepts/Allocatable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_TRIVIAL
#include "Concepts/Trivial.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTNULLEXCEPTION
#include "ArgumentNullException.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#include "MemSet.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "Compiler.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVEASSIGNABLE
#include "IsMoveAssignable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVECONSTRUCTIBLE
#include "IsMoveConstructible.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	template <Concepts::Allocatable T, class Allocator = Memory::DefaultAllocator<T>>
	class Vector
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
		constexpr FIterator EraseAt(const System::size Index);

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
		void InPlaceConstruct();

		const System::size CalculateCapacityGrowth(const System::size DesiredCapacity);
	private:
		Allocator _Allocator;
		System::size _Capacity;
		System::size _Length;
		Pointer _Data;
	};

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector() noexcept
		: _Allocator(Allocator()), _Capacity(1), _Length(0), _Data(_Allocator.Allocate(_Capacity))
	{
		InPlaceConstruct();
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(const Elysium::Core::Template::System::size Capacity)
		: _Allocator(Allocator()), _Capacity(Capacity == 0 ? 1 : Capacity), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{
		InPlaceConstruct();
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(const InitializerList<T>& InitializerList)
		: _Allocator(Allocator()), _Capacity(InitializerList.size() == 0 ? 1 : InitializerList.size()), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{
		InPlaceConstruct();

		Elysium::Core::Template::System::size Index = 0;
		const T* Iterator = InitializerList.begin();
		const T* LastElement = InitializerList.end();
		for (; Iterator != LastElement; ++Iterator)
		{
#pragma warning(disable : 6011)	// _Data won't be nullptr if InitializerList contains elements
			_Data[Index++] = *Iterator;
#pragma warning(default : 6011)
		}
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(const Vector& Source)
		: _Allocator(Allocator()), _Capacity(Source._Capacity), _Length(Source._Length), _Data(_Allocator.Allocate(_Capacity))
	{
		InPlaceConstruct();

		for (Elysium::Core::Template::System::size i = 0; i < _Length; ++i)
		{
			_Data[i] = Source._Data[i];
		}
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(Vector&& Right) noexcept
		: _Allocator(Allocator()), _Capacity(0), _Length(0), _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::~Vector()
	{
		for (Elysium::Core::Template::System::size i = 0; i < _Length; ++i)
		{
			_Data[i].~T();
		}
		
		_Allocator.Deallocate(_Data, _Capacity);
		_Data = nullptr;
	}

	template<Concepts::Allocatable T,  class Allocator>
	inline constexpr Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& Source)
	{
		if (this != &Source)
		{
			if (Source._Capacity > _Capacity)
			{
				_Allocator.Deallocate(_Data, _Capacity);

				_Capacity = Source._Capacity;
				_Data = _Allocator.Allocate(Source._Capacity);

				InPlaceConstruct();
			}

			_Length = Source._Length;
			for (Elysium::Core::Template::System::size i = 0; i < _Length; ++i)
			{
				_Data[i] = Source._Data[i];
			}
		}
		return *this;
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& Right) noexcept
	{
		if (this != &Right)
		{
			_Allocator.Deallocate(_Data, _Capacity);

			_Capacity = Functional::Move(Right._Capacity);
			_Length = Functional::Move(Right._Length);
			_Data = Functional::Move(Right._Data);

			Right._Capacity = 0;
			Right._Length = 0;
			Right._Data = nullptr;
		}
		return *this;
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::Reference Vector<T, Allocator>::operator[](const Elysium::Core::Template::System::size Index)
	{
		return _Data[Index];
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReference Vector<T, Allocator>::operator[](const Elysium::Core::Template::System::size Index) const
	{
		return _Data[Index];
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<T, Allocator>::GetMaximumSize()
	{
		return static_cast<Elysium::Core::Template::System::size>(-1) / sizeof(T);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<T, Allocator>::GetCapacity() const noexcept
	{
		return _Capacity;
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<T, Allocator>::GetLength() const noexcept
	{
		return _Length;
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstPointer Vector<T, Allocator>::GetData() const noexcept
	{
		return _Data;
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr const bool Vector<T, Allocator>::GetIsEmpty() const noexcept
	{
		return _Length == 0;
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::Reference Vector<T, Allocator>::GetAt(const Elysium::Core::Template::System::size Index)
	{
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReference Vector<T, Allocator>::GetAt(const Elysium::Core::Template::System::size Index) const
	{
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}
	
	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::FIterator Vector<T, Allocator>::GetBegin() noexcept
	{
		return FIterator(&_Data[0]);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetBegin() const noexcept
	{
		return ConstIterator(&_Data[0]);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::FIterator Vector<T, Allocator>::GetEnd() noexcept
	{
		return FIterator(&_Data[_Length - 1]);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetEnd() const noexcept
	{
		return ConstIterator(&_Data[_Length - 1]);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseBegin() noexcept
	{
		return ReverseIterator(&_Data[_Length - 1]);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseBegin() const noexcept
	{
		return ConstReverseIterator(&_Data[_Length - 1]);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseEnd() noexcept
	{
		return ReverseIterator(&_Data[0]);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseEnd() const noexcept
	{
		return ConstReverseIterator(&_Data[0]);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline void Vector<T, Allocator>::Assign(ConstValue Value, const Elysium::Core::Template::System::size Length)
	{
		const Elysium::Core::Template::System::size RequiredSize = _Length + Length;
		if (RequiredSize > _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			Reserve(CalculateCapacityGrowth(RequiredSize));
		}

		for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
		{
			_Data[_Length++] = Value;
		}
	}

	template<Concepts::Allocatable T, class Allocator>
	inline void Vector<T, Allocator>::Clear()
	{
		for (Elysium::Core::Template::System::size i = 0; i < _Length; ++i)
		{
			_Data[i].~T();
		}
		
		_Length = 0;
	}

	template<Concepts::Allocatable T, class Allocator>
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

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr Container::Vector<T, Allocator>::FIterator Container::Vector<T, Allocator>::EraseAt(const System::size Index)
	{	// @ToDo: have a look at std::vector::erase in regards to returning the last element?
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}
		
		// ensure object destruction
		_Data[Index].~T();

		if constexpr (Elysium::Core::Template::TypeTraits::IsMoveAssignableValue<T>)
		{
			for (Elysium::Core::Template::System::size i = Index; i < _Length; ++i)
			{
				_Data[i] = Elysium::Core::Template::Functional::Move(_Data[i + 1]);
			}
		}
		else
		{
			for (Elysium::Core::Template::System::size i = Index; i < _Length; ++i)
			{
				_Data[i] = _Data[i + 1];
			}
		}
		
		_Length--;

		return GetEnd();
	}

	template<Concepts::Allocatable T, class Allocator>
	inline void Vector<T, Allocator>::Insert(const Elysium::Core::Template::System::size Index, ConstValue Value)
	{
		if (Index >= _Capacity)
		{
			throw 1;
		}

		if (_Length == _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			const Elysium::Core::Template::System::size DesiredCapacity = CalculateCapacityGrowth(_Capacity + 1);

			throw 1;
			//Reserve(CalculateCapacityGrowth(_Capacity + 1));
		}
		else ELYSIUM_CORE_PATH_LIKELY
		{
			if constexpr (Elysium::Core::Template::TypeTraits::IsMoveAssignableValue<T>)
			{
				for (Elysium::Core::Template::System::size i = _Length; i > Index; --i)
				{
					_Data[i + 1] = Elysium::Core::Template::Functional::Move(_Data[i]);
				}
			}
			else
			{
				for (Elysium::Core::Template::System::size i = _Length; i > Index; --i)
				{
					_Data[i + 1] = _Data[i];
				}
			}

			// don't need to in-place-construct in between (as long as InPlaceConstruct() creates for whole _Capacity);
			/*
			for (Elysium::Core::Template::System::size i = Index - 1; i > _Length; --i)
			{
				new (&_Data[i]) T();
			}
			*/
			
			_Data[Index] = Value;

			_Length += Index > _Length ? Index - _Length : 1;
		}
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr void Vector<T, Allocator>::PushBack(ConstReference Item)
	{
		if (_Length == _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			Reserve(CalculateCapacityGrowth(_Capacity + 1));
		}

		_Data[_Length++] = Item;
	}

	template<Concepts::Allocatable T, class Allocator>
	inline constexpr void Vector<T, Allocator>::PushBack(RValueReference Item)
	{
		if (_Length == _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			Reserve(CalculateCapacityGrowth(_Capacity + 1));
		}

		_Data[_Length++] = Functional::Move(Item);
	}

	template<Concepts::Allocatable T, class Allocator>
	inline void Vector<T, Allocator>::PushBackRange(ConstPointer FirstItem, const Elysium::Core::Template::System::size Length)
	{
		if (FirstItem == nullptr)
		{
			//throw Elysium::Core::Template::Exceptions::ArgumentNullException(nameof(FirstItem));
			throw Elysium::Core::Template::Exceptions::ArgumentNullException();
		}

		const Elysium::Core::Template::System::size RequiredSize = _Length + Length;
		if (RequiredSize > _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			Reserve(CalculateCapacityGrowth(RequiredSize));
		}

		for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
		{
			_Data[_Length++] = FirstItem[i];
		}
	}

	template<Concepts::Allocatable T, class Allocator>
	inline void Vector<T, Allocator>::PopBack()
	{
		if (_Length > 0)
		{
			_Data[_Length--].~T();
		}
	}

	template<Concepts::Allocatable T, class Allocator>
	inline void Vector<T, Allocator>::Reserve(const Elysium::Core::Template::System::size DesiredCapacity)
	{
		if (DesiredCapacity > _Capacity)
		{
			Pointer OldData = _Data;
			_Capacity = DesiredCapacity;
			_Data = _Allocator.Allocate(_Capacity);
			InPlaceConstruct();

			if constexpr (Elysium::Core::Template::TypeTraits::IsMoveAssignableValue<T>)
			{
				for (Elysium::Core::Template::System::size i = 0; i < _Length; ++i)
				{
					_Data[i] = Functional::Move(OldData[i]);
				}
			}
			else
			{
				for (Elysium::Core::Template::System::size i = 0; i < _Length; ++i)
				{
					_Data[i] = OldData[i];
				}
			}

			_Allocator.Deallocate(OldData, _Capacity);
		}
	}

	template<Concepts::Allocatable T, class Allocator>
	inline void Vector<T, Allocator>::ShrinkToFit()
	{
		if (_Length != _Capacity)
		{
			Pointer OldData = _Data;
			_Capacity = _Length;
			_Data = _Allocator.Allocate(_Capacity);
			InPlaceConstruct();

			if constexpr (Elysium::Core::Template::TypeTraits::IsMoveAssignableValue<T>)
			{
				for (Elysium::Core::Template::System::size i = 0; i < _Length; ++i)
				{
					_Data[i] = Functional::Move(OldData[i]);
				}
			}
			else
			{
				for (Elysium::Core::Template::System::size i = 0; i < _Length; ++i)
				{
					_Data[i] = OldData[i];
				}
			}

			_Allocator.Deallocate(OldData, _Capacity);
		}
	}

	template<Concepts::Allocatable T, class Allocator>
	inline void Vector<T, Allocator>::InPlaceConstruct()
	{
		// @ToDo: check whether I can get away with only in place constructing up until _Length 
		// (and in place construct the rest when necessary)
		for (Elysium::Core::Template::System::size i = 0; i < _Capacity; ++i)
		{
			new (&_Data[i]) T();
		}
	}

	template<Concepts::Allocatable T, class Allocator>
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
	
	/// <summary>
	/// Specialized vector for trivially copyable types.
	/// </summary>
	/// <typeparam name="Allocator"></typeparam>
	/// <typeparam name="T"></typeparam>
	template <Elysium::Core::Template::Concepts::Trivial T, class Allocator>
	class Vector<T, Allocator>
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
	public:
		using FIterator = Iterator::ForwardIterator<Vector<T, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<Vector<T, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<Vector<T, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<Vector<T, Allocator>>;
	public:
		constexpr Vector() noexcept;

		constexpr Vector(const System::size Capacity);

		constexpr Vector(const InitializerList<T>& InitializerList);

		constexpr Vector(const Vector& Source);

		constexpr Vector(Vector&& Right) noexcept;

		constexpr ~Vector();
	public:
		constexpr Vector<T, Allocator>& operator=(const Vector& Source);

		constexpr Vector<T, Allocator>& operator=(Vector&& Right) noexcept;
	public:
		constexpr Reference operator[](const System::size Index);

		constexpr ConstReference operator[](const System::size Index) const;
	public:
		static constexpr const System::size GetMaximumSize();

		constexpr const System::size GetCapacity() const noexcept;

		constexpr const System::size GetLength() const noexcept;

		constexpr ConstPointer GetData() const noexcept;

		constexpr const bool GetIsEmpty() const noexcept;

		constexpr Reference GetAt(const System::size Index);

		constexpr ConstReference GetAt(const System::size Index) const;
	public:
		constexpr FIterator GetBegin() noexcept;

		constexpr ConstIterator GetBegin() const noexcept;

		constexpr FIterator GetEnd() noexcept;

		constexpr ConstIterator GetEnd() const noexcept;

		constexpr ReverseIterator GetReverseBegin() noexcept;

		constexpr ConstReverseIterator GetReverseBegin() const noexcept;

		constexpr ReverseIterator GetReverseEnd() noexcept;

		constexpr ConstReverseIterator GetReverseEnd() const noexcept;
	public:
		void Assign(ConstValue Value, const System::size Length);

		void Clear();

		constexpr FIterator Erase(ConstValue Value);

		constexpr FIterator EraseAt(const System::size Index);

		void Insert(const System::size Index, ConstValue Value);

		constexpr void PushBack(ConstReference Item);

		constexpr void PushBack(RValueReference Item);
		
		void PushBackRange(ConstPointer FirstItem, const System::size Length);

		void PopBack();

		void Reserve(const System::size DesiredCapacity);

		void ShrinkToFit();
	private:
		const System::size CalculateCapacityGrowth(const System::size DesiredCapacity);
	private:
		Allocator _Allocator;
		System::size _Capacity;
		System::size _Length;
		Pointer _Data;
	};

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector() noexcept
		: _Allocator(Allocator()), _Capacity(1), _Length(0), _Data(_Allocator.Allocate(_Capacity))
	{
		Elysium::Core::Template::Memory::MemSet(_Data, 0, _Capacity * sizeof(T));
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(const Elysium::Core::Template::System::size Capacity)
		: _Allocator(Allocator()), _Capacity(Capacity == 0 ? 1 : Capacity), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{
		Elysium::Core::Template::Memory::MemSet(_Data, 0, _Capacity * sizeof(T));
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(const InitializerList<T>& InitializerList)
		: _Allocator(Allocator()), _Capacity(InitializerList.size() == 0 ? 1 : InitializerList.size()), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{
		if (InitializerList.size() == 0) ELYSIUM_CORE_PATH_UNLIKELY
		{
			Elysium::Core::Template::Memory::MemSet(_Data, 0, sizeof(T));
		}
		else
		{
			const T* SourceBegin = InitializerList.begin();
			Elysium::Core::Template::Memory::MemCpy(_Data, SourceBegin, (InitializerList.end() - SourceBegin) * sizeof(T));
		}
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(const Vector& Source)
		: _Allocator(Allocator()), _Capacity(Source._Capacity), _Length(Source._Length), _Data(_Allocator.Allocate(_Capacity))
	{
		Elysium::Core::Template::Memory::MemCpy(_Data, Source._Data, _Capacity * sizeof(T));
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::Vector(Vector&& Right) noexcept
		: _Allocator(Allocator()), _Capacity(0), _Length(0), _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::~Vector()
	{
		_Allocator.Deallocate(_Data, _Capacity);
		_Data = nullptr;
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& Source)
	{
		if (this != &Source)
		{
			if (Source._Capacity > _Capacity)
			{
				_Allocator.Deallocate(_Data, _Capacity);

				_Capacity = Source._Capacity;
				_Data = _Allocator.Allocate(Source._Capacity);

				Elysium::Core::Template::Memory::MemSet(_Data, 0, _Capacity * sizeof(T));
			}

			_Length = Source._Length;
			Elysium::Core::Template::Memory::MemCpy(_Data, Source._Data, _Capacity * sizeof(T));
		}
		return *this;
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& Right) noexcept
	{
		if (this != &Right)
		{
			_Allocator.Deallocate(_Data, _Capacity);

			_Capacity = Functional::Move(Right._Capacity);
			_Length = Functional::Move(Right._Length);
			_Data = Functional::Move(Right._Data);

			Right._Capacity = 0;
			Right._Length = 0;
			Right._Data = nullptr;
		}
		return *this;
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::Reference Vector<T, Allocator>::operator[](const Elysium::Core::Template::System::size Index)
	{
		return _Data[Index];
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReference Vector<T, Allocator>::operator[](const Elysium::Core::Template::System::size Index) const
	{
		return _Data[Index];
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<T, Allocator>::GetMaximumSize()
	{
		return static_cast<Elysium::Core::Template::System::size>(-1) / sizeof(T);
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<T, Allocator>::GetCapacity() const noexcept
	{
		return _Capacity;
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<T, Allocator>::GetLength() const noexcept
	{
		return _Length;
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstPointer Vector<T, Allocator>::GetData() const noexcept
	{
		return _Data;
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr const bool Vector<T, Allocator>::GetIsEmpty() const noexcept
	{
		return _Length == 0;
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::Reference Vector<T, Allocator>::GetAt(const Elysium::Core::Template::System::size Index)
	{
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReference Vector<T, Allocator>::GetAt(const Elysium::Core::Template::System::size Index) const
	{
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::FIterator Vector<T, Allocator>::GetBegin() noexcept
	{
		return FIterator(&_Data[0]);
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetBegin() const noexcept
	{
		return ConstIterator(&_Data[0]);
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::FIterator Vector<T, Allocator>::GetEnd() noexcept
	{
		return FIterator(&_Data[_Length - 1]);
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetEnd() const noexcept
	{
		return ConstIterator(&_Data[_Length - 1]);
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseBegin() noexcept
	{
		return ReverseIterator(&_Data[_Length - 1]);
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseBegin() const noexcept
	{
		return ConstReverseIterator(&_Data[_Length - 1]);
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseEnd() noexcept
	{
		return ReverseIterator(&_Data[0]);
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseEnd() const noexcept
	{
		return ConstReverseIterator(&_Data[0]);
	}

	template<Concepts::Trivial T, class Allocator>
	inline void Vector<T, Allocator>::Assign(ConstValue Value, const Elysium::Core::Template::System::size Length)
	{
		const Elysium::Core::Template::System::size RequiredSize = _Length + Length;
		if (RequiredSize > _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			Reserve(CalculateCapacityGrowth(RequiredSize));
		}

		for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
		{
			Elysium::Core::Template::Memory::MemCpy(&_Data[_Length++], &Value, sizeof(T));
		}
	}

	template<Concepts::Trivial T, class Allocator>
	inline void Vector<T, Allocator>::Clear()
	{
		_Length = 0;
	}

	template<Concepts::Trivial T, class Allocator>
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

	template<Concepts::Trivial T, class Allocator>
	inline constexpr Container::Vector<T, Allocator>::FIterator Container::Vector<T, Allocator>::EraseAt(const System::size Index)
	{
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		// @ToDo: have a look at whether copying twice (once to temporary) and then back in one swoop might be faster
		// (maybe dependand on difference between Index and _Length)
		for (Elysium::Core::Template::System::size i = Index; i < _Length; ++i)
		{
			Elysium::Core::Template::Memory::MemCpy(&_Data[i], &_Data[i + 1], sizeof(T));
		}

		// ToDo: have a look at std::vector::erase in regards to returning the last element?
		return GetEnd();
	}

	template<Concepts::Trivial T, class Allocator>
	inline void Vector<T, Allocator>::Insert(const Elysium::Core::Template::System::size Index, ConstValue Value)
	{
		if (Index >= _Capacity)
		{
			throw 1;
		}

		if (_Length == _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			const Elysium::Core::Template::System::size DesiredCapacity = CalculateCapacityGrowth(_Capacity + 1);

			throw 1;
		}
		else ELYSIUM_CORE_PATH_LIKELY
		{
			for (Elysium::Core::Template::System::size i = _Length; i > Index; --i)
			{
				Elysium::Core::Template::Memory::MemCpy(&_Data[i + 1], &_Data[i], sizeof(T));
			}
			
			Elysium::Core::Template::Memory::MemCpy(&_Data[Index], &Value, sizeof(T));

			_Length += Index > _Length ? Index - _Length : 1;
		}
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr void Vector<T, Allocator>::PushBack(ConstReference Item)
	{
		if (_Length == _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			Reserve(CalculateCapacityGrowth(_Capacity + 1));
		}

		Elysium::Core::Template::Memory::MemCpy(&_Data[_Length++], &Item, sizeof(T));
	}

	template<Concepts::Trivial T, class Allocator>
	inline constexpr void Vector<T, Allocator>::PushBack(RValueReference Item)
	{
		if (_Length == _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			Reserve(CalculateCapacityGrowth(_Capacity + 1));
		}
		Elysium::Core::Template::Memory::MemCpy(&_Data[_Length++], &Item, sizeof(T));
	}

	template<Concepts::Trivial T, class Allocator>
	inline void Vector<T, Allocator>::PushBackRange(ConstPointer FirstItem, const Elysium::Core::Template::System::size Length)
	{
		if (FirstItem == nullptr)
		{
			//throw Elysium::Core::Template::Exceptions::ArgumentNullException(nameof(FirstItem));
			throw Elysium::Core::Template::Exceptions::ArgumentNullException();
		}

		const Elysium::Core::Template::System::size RequiredSize = _Length + Length;
		if (RequiredSize > _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
		{
			Reserve(CalculateCapacityGrowth(RequiredSize));
		}

		Elysium::Core::Template::Memory::MemCpy(&_Data[_Length], FirstItem, Length * sizeof(T));
		_Length += Length;
	}

	template<Concepts::Trivial T, class Allocator>
	inline void Vector<T, Allocator>::PopBack()
	{
		if (_Length > 0)
		{
			Elysium::Core::Template::Memory::MemSet(&_Data[_Length--], 0, sizeof(T));
		}
	}

	template<Concepts::Trivial T, class Allocator>
	inline void Vector<T, Allocator>::Reserve(const Elysium::Core::Template::System::size DesiredCapacity)
	{
		if (DesiredCapacity > _Capacity)
		{
			Pointer OldData = _Data;
			_Capacity = DesiredCapacity;
			_Data = _Allocator.Allocate(_Capacity);
			
			Elysium::Core::Template::Memory::MemSet(_Data, 0, _Capacity * sizeof(T));
			Elysium::Core::Template::Memory::MemCpy(_Data, OldData, _Length *sizeof(T));

			_Allocator.Deallocate(OldData, _Capacity);
		}
	}

	template<Concepts::Trivial T, class Allocator>
	inline void Vector<T, Allocator>::ShrinkToFit()
	{
		if (_Length != _Capacity)
		{
			Pointer OldData = _Data;
			_Capacity = _Length;
			_Data = _Allocator.Allocate(_Capacity);

			Elysium::Core::Template::Memory::MemSet(_Data, 0, _Capacity * sizeof(T));
			Elysium::Core::Template::Memory::MemCpy(_Data, OldData, _Length * sizeof(T));

			_Allocator.Deallocate(OldData, _Capacity);
		}
	}

	template<Concepts::Trivial T, class Allocator>
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
	/// <summary>
	/// Specialized vector for boolean.
	/// </summary>
	/// <typeparam name="Allocator"></typeparam>
	template <class Allocator>
	class Vector<bool, Allocator>
	{
	public:
		using Value = bool;
		using ConstValue = const bool;
		using Pointer = bool*;
		using ConstPointer = const bool*;
		using Reference = bool&;
		using ConstReference = const bool&;
		using RValueReference = bool&&;

		using IteratorPointer = bool*;
		using IteratorReference = bool&;
		using ConstIteratorReference = const bool&;
	public:
		using FIterator = Iterator::ForwardIterator<Vector<bool, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<Vector<bool, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<Vector<bool, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<Vector<bool, Allocator>>;
	public:
		constexpr Vector() noexcept;

		constexpr Vector(const System::size Capacity);

		constexpr Vector(const InitializerList<bool>& InitializerList);

		constexpr Vector(const Vector& Source);

		constexpr Vector(Vector&& Right) noexcept;

		constexpr ~Vector();
	public:
		constexpr Vector<bool, Allocator>& operator=(const Vector& Source);

		constexpr Vector<bool, Allocator>& operator=(Vector&& Right) noexcept;
	public:
		constexpr Reference operator[](const System::size Index);

		constexpr ConstReference operator[](const System::size Index) const;
	public:
		static constexpr const System::size GetMaximumSize();

		constexpr const System::size GetCapacity() const noexcept;

		constexpr const System::size GetLength() const noexcept;

		constexpr ConstPointer GetData() const noexcept;

		constexpr const bool GetIsEmpty() const noexcept;

		constexpr Reference GetAt(const System::size Index);

		constexpr ConstReference GetAt(const System::size Index) const;
	public:
		constexpr FIterator GetBegin() noexcept;

		constexpr ConstIterator GetBegin() const noexcept;

		constexpr FIterator GetEnd() noexcept;

		constexpr ConstIterator GetEnd() const noexcept;

		constexpr ReverseIterator GetReverseBegin() noexcept;

		constexpr ConstReverseIterator GetReverseBegin() const noexcept;

		constexpr ReverseIterator GetReverseEnd() noexcept;

		constexpr ConstReverseIterator GetReverseEnd() const noexcept;
	public:
		void Assign(ConstValue Value, const System::size Length);

		void Clear();

		constexpr FIterator Erase(ConstValue Value);

		constexpr FIterator EraseAt(const System::size Index);

		void Insert(const System::size Index, ConstValue Value);

		constexpr void PushBack(ConstReference Item);

		constexpr void PushBack(RValueReference Item);

		void PushBackRange(const Vector<bool>& Source, const System::size FirstIndex, const System::size Length);

		void PushBackRange(ConstPointer FirstItem, const System::size Length);

		void PopBack();

		void Reserve(const System::size DesiredCapacity);

		void ShrinkToFit();
	private:
		const System::size CalculateCapacityGrowth(const System::size DesiredCapacity);
	private:
		Allocator _Allocator;
		System::size _Capacity;
		System::size _Length;
		Pointer _Data;
	};

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::Vector() noexcept
		: _Allocator(Allocator()), _Capacity(1), _Length(0), _Data(_Allocator.Allocate(_Capacity))
	{

	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::Vector(const Elysium::Core::Template::System::size Capacity)
		: _Allocator(Allocator()), _Capacity(Capacity == 0 ? 1 : Capacity), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{

	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::Vector(const InitializerList<bool>& InitializerList)
		: _Allocator(Allocator()), _Capacity(InitializerList.size() == 0 ? 1 : InitializerList.size()), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
	{

	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::Vector(const Vector& Source)
		: _Allocator(Allocator()), _Capacity(Source._Capacity), _Length(Source._Length), _Data(_Allocator.Allocate(_Capacity))
	{

	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::Vector(Vector&& Right) noexcept
		: _Allocator(Allocator()), _Capacity(0), _Length(0), _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::~Vector()
	{
		_Allocator.Deallocate(_Data, _Capacity);
		_Data = nullptr;
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>& Vector<bool, Allocator>::operator=(const Vector& Source)
	{
		if (this != &Source)
		{

		}
		return *this;
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>& Vector<bool, Allocator>::operator=(Vector&& Right) noexcept
	{
		if (this != &Right)
		{

		}
		return *this;
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::Reference Vector<bool, Allocator>::operator[](const Elysium::Core::Template::System::size Index)
	{
		return _Data[Index];
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::ConstReference Vector<bool, Allocator>::operator[](const Elysium::Core::Template::System::size Index) const
	{
		return _Data[Index];
	}

	template<class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<bool, Allocator>::GetMaximumSize()
	{
		return static_cast<Elysium::Core::Template::System::size>(-1) / sizeof(bool);
	}

	template<class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<bool, Allocator>::GetCapacity() const noexcept
	{
		return _Capacity;
	}

	template<class Allocator>
	inline constexpr const Elysium::Core::Template::System::size Vector<bool, Allocator>::GetLength() const noexcept
	{
		return _Length;
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::ConstPointer Vector<bool, Allocator>::GetData() const noexcept
	{
		return _Data;
	}

	template<class Allocator>
	inline constexpr const bool Vector<bool, Allocator>::GetIsEmpty() const noexcept
	{
		return _Length == 0;
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::Reference Vector<bool, Allocator>::GetAt(const Elysium::Core::Template::System::size Index)
	{
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::ConstReference Vector<bool, Allocator>::GetAt(const Elysium::Core::Template::System::size Index) const
	{
		if (Index >= _Length)
		{
			throw Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::FIterator Vector<bool, Allocator>::GetBegin() noexcept
	{
		return FIterator(&_Data[0]);
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::ConstIterator Vector<bool, Allocator>::GetBegin() const noexcept
	{
		return ConstIterator(&_Data[0]);
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::FIterator Vector<bool, Allocator>::GetEnd() noexcept
	{
		return FIterator(&_Data[_Length - 1]);
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::ConstIterator Vector<bool, Allocator>::GetEnd() const noexcept
	{
		return ConstIterator(&_Data[_Length - 1]);
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::ReverseIterator Vector<bool, Allocator>::GetReverseBegin() noexcept
	{
		return ReverseIterator(&_Data[_Length - 1]);
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::ConstReverseIterator Vector<bool, Allocator>::GetReverseBegin() const noexcept
	{
		return ConstReverseIterator(&_Data[_Length - 1]);
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::ReverseIterator Vector<bool, Allocator>::GetReverseEnd() noexcept
	{
		return ReverseIterator(&_Data[0]);
	}

	template<class Allocator>
	inline constexpr Vector<bool, Allocator>::ConstReverseIterator Vector<bool, Allocator>::GetReverseEnd() const noexcept
	{
		return ConstReverseIterator(&_Data[0]);
	}

	template<class Allocator>
	inline void Vector<bool, Allocator>::Assign(ConstValue Value, const Elysium::Core::Template::System::size Length)
	{

	}

	template<class Allocator>
	inline void Vector<bool, Allocator>::Clear()
	{
		_Length = 0;
	}

	template<class Allocator>
	inline constexpr Container::Vector<bool, Allocator>::FIterator Container::Vector<bool, Allocator>::Erase(ConstValue Value)
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

	template<class Allocator>
	inline constexpr Container::Vector<bool, Allocator>::FIterator Container::Vector<bool, Allocator>::EraseAt(const System::size Index)
	{

		// ToDo: have a look at std::vector::erase in regards to returning the last element?
		return GetEnd();
	}

	template<class Allocator>
	inline void Vector<bool, Allocator>::Insert(const Elysium::Core::Template::System::size Index, ConstValue Value)
	{

	}

	template<class Allocator>
	inline constexpr void Vector<bool, Allocator>::PushBack(ConstReference Item)
	{

	}

	template<class Allocator>
	inline constexpr void Vector<bool, Allocator>::PushBack(RValueReference Item)
	{

	}

	template<class Allocator>
	inline void Vector<bool, Allocator>::PushBackRange(ConstPointer FirstItem, const Elysium::Core::Template::System::size Length)
	{

	}

	template<class Allocator>
	inline void Vector<bool, Allocator>::PopBack()
	{

	}

	template<class Allocator>
	inline void Vector<bool, Allocator>::Reserve(const Elysium::Core::Template::System::size DesiredCapacity)
	{

	}

	template<class Allocator>
	inline void Vector<bool, Allocator>::ShrinkToFit()
	{

	}

	template<class Allocator>
	inline const Elysium::Core::Template::System::size Vector<bool, Allocator>::CalculateCapacityGrowth(const Elysium::Core::Template::System::size DesiredCapacity)
	{
		return 0;
	}
	*/
}
#endif
