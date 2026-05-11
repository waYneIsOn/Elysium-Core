/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DOUBLEENDEDQUEUE
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_DOUBLEENDEDQUEUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "../Concepts/NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INDEXOUTOFRANGEEXCEPTION
#include "../Exceptions/IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OUTOFMEMORYEXCEPTION
#include "../Exceptions/OutOfMemoryException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Memory/DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIALLYCOPYABLE
#include "../TypeTraits/IsTriviallyCopyable.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <Elysium::Core::Template::Concepts::NonConstant T, class Allocator = Elysium::Core::Template::Memory::DefaultAllocator<T>>
		requires Elysium::Core::Template::Concepts::Allocatable<T>
	class DoubleEndedQueue
	{
	public:
		using Value = T;

		using Pointer = T*;
		using ConstPointer = T* const;

		using Reference = T&;
		using ConstReference = T& const;

		using RValueReference = T&&;
	public:
		constexpr DoubleEndedQueue() noexcept
			: _Allocator(), _Capacity(1), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
		{ }

		constexpr DoubleEndedQueue(const Elysium::Core::Template::System::size Capacity) noexcept
			: _Allocator(), _Capacity(Capacity == 0 ? 1 : Capacity), _Length(_Capacity), _Data(_Allocator.Allocate(_Capacity))
		{}

		constexpr DoubleEndedQueue(const InitializerList<T>& InitializerList) noexcept
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

		constexpr DoubleEndedQueue(const DoubleEndedQueue& Source) = delete;

		constexpr DoubleEndedQueue(DoubleEndedQueue&& Right) noexcept = delete;

		constexpr ~DoubleEndedQueue() = default;
	public:
		constexpr DoubleEndedQueue<T, Allocator>& operator=(const DoubleEndedQueue& Source) = delete;

		constexpr DoubleEndedQueue<T, Allocator>& operator=(DoubleEndedQueue&& Right) noexcept = delete;
	public:
		inline constexpr const bool GetIsEmpty() const noexcept
		{
			return _Length == 0;
		}

		inline constexpr const Elysium::Core::Template::System::size GetLength() const noexcept
		{
			return _Length;
		}

		inline constexpr Reference GetFront()
		{
			if (0 == _Length)
			{
				throw Exceptions::IndexOutOfRangeException();
			}

			return _Data[0];
		}

		inline constexpr ConstReference GetFront() const
		{
			if (0 == _Length)
			{
				throw Exceptions::IndexOutOfRangeException();
			}

			return _Data[0];
		}
	public:
		inline static constexpr const System::size GetMaximumSize()
		{
			return static_cast<Elysium::Core::Template::System::size>(-1) / sizeof(T);
		}
	public:
		inline void PushBack(ConstReference Item)
		{
			if (_Length == _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
			{
				Reserve(CalculateCapacityGrowth(_Capacity + 1));
			}

			if constexpr (Elysium::Core::Template::TypeTraits::IsTriviallyCopyableValue<T>)
			{
				Elysium::Core::Template::Memory::MemCpy(&_Data[_Length++], &Item, sizeof(T));
			}
			else
			{
				_Data[_Length++] = Item;
			}
		}

		inline void PushBack(RValueReference Item)
		{
			if (_Length == _Capacity) ELYSIUM_CORE_PATH_UNLIKELY
			{
				Reserve(CalculateCapacityGrowth(_Capacity + 1));
			}

			if constexpr (Elysium::Core::Template::TypeTraits::IsTriviallyCopyableValue<T>)
			{
				Elysium::Core::Template::Memory::MemCpy(&_Data[_Length++], &Item, sizeof(T));
			}
			else
			{
				_Data[_Length++] = Item;
			}
		}

		inline void PopFront() noexcept
		{
			if (0 == _Length)
			{
				throw Exceptions::IndexOutOfRangeException();
			}

			// ensure object destruction
			_Data[0].~T();

			if constexpr (Elysium::Core::Template::TypeTraits::IsMoveAssignableValue<T>)
			{
				for (Elysium::Core::Template::System::size i = 1; i < _Length; ++i)
				{
					_Data[i - 1] = Elysium::Core::Template::Functional::Move(_Data[i]);
				}
			}
			else
			{
				for (Elysium::Core::Template::System::size i = 1; i < _Length; ++i)
				{
					_Data[i - 1] = _Data[i];
				}
			}

			--_Length;
		}

		inline void PopBack() noexcept
		{
			if (0 == _Length)
			{
				throw Exceptions::IndexOutOfRangeException();
			}

			// @ToDo: can I get away with just reducing the length making the last element no longer accessible?
			--_Length;
		}

		inline void Clear()
		{
			for (Elysium::Core::Template::System::size i = 0; i < _Length; ++i)
			{
				_Data[i].~T();
			}

			_Length = 0;
		}
	private:
		inline void InPlaceConstruct()
		{
			// @ToDo: check whether I can get away with only in place constructing up until _Length 
			// (and in place construct the rest when necessary)
			for (Elysium::Core::Template::System::size i = 0; i < _Capacity; ++i)
			{
				new (&_Data[i]) T();
			}
		}

		inline void Reserve(const Elysium::Core::Template::System::size DesiredCapacity)
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

		inline const Elysium::Core::Template::System::size CalculateCapacityGrowth(const Elysium::Core::Template::System::size DesiredCapacity)
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
	private:
		Allocator _Allocator;
		Elysium::Core::Template::System::size _Capacity;
		Elysium::Core::Template::System::size _Length;
		T* _Data;
	};
}
#endif
