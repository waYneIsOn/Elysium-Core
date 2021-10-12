/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DOUBLEBUFFER
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_DOUBLEBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_ARRAY
#include "Array.hpp"
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
	template <class T, class Allocator = Memory::DefaultAllocator<T>>
	class DoubleBuffer final
	{
	public:
		using Value = T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;
	private:
		inline static const size_t BUFFERSIZE = 2;
		inline static Allocator _Allocator = Allocator();
	public:
		/// <summary>
		/// 
		/// </summary>
		DoubleBuffer();

		/// <summary>
		/// 
		/// </summary>
		DoubleBuffer(const DoubleBuffer& Source);

		/// <summary>
		/// 
		/// </summary>
		DoubleBuffer(DoubleBuffer&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		~DoubleBuffer();

		/// <summary>
		/// 
		/// </summary>
		DoubleBuffer<T, Allocator>& operator=(const DoubleBuffer& Source);

		/// <summary>
		/// 
		/// </summary>
		DoubleBuffer<T, Allocator>& operator=(DoubleBuffer&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Reference GetCurrent();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ConstReference GetCurrent() const;

		/// <summary>
		/// 
		/// </summary>
		void Swap();
	private:
		Pointer _Buffer;
		Pointer _Current;
		Pointer _Next;
	};

	template<class T, class Allocator>
	inline DoubleBuffer<T, Allocator>::DoubleBuffer()
		: _Buffer(_Allocator.Allocate(BUFFERSIZE)), _Current(&_Buffer[0]), _Next(&_Buffer[1])
	{ }

	template<class T, class Allocator>
	inline DoubleBuffer<T, Allocator>::DoubleBuffer(const DoubleBuffer& Source)
		: _Buffer(_Allocator.Allocate(BUFFERSIZE)),
		_Current(Source._Current == &Source._Buffer[0] ? &_Buffer[0] : &_Buffer[1]),
		_Next(Source._Next == &Source._Buffer[0] ? &_Buffer[0] : &_Buffer[1]])
	{
		Array<T>::Copy(&_Buffer[0], &_Buffer[0], BUFFERSIZE);
	}

	template<class T, class Allocator>
	inline DoubleBuffer<T, Allocator>::DoubleBuffer(DoubleBuffer&& Right) noexcept
		: _Buffer(_Allocator.Allocate(BUFFERSIZE)), _Current(&_Buffer[0]), _Next(&_Buffer[1])
	{
		*this = Functional::Move(Right);
	}

	template<class T, class Allocator>
	inline DoubleBuffer<T, Allocator>::~DoubleBuffer()
	{
		_Allocator.Deallocate(_Buffer, BUFFERSIZE);
	}

	template<class T, class Allocator>
	inline DoubleBuffer<T, Allocator>& DoubleBuffer<T, Allocator>::operator=(const DoubleBuffer& Source)
	{
		if (this != &Source)
		{
			Array<T>::Copy(&_Buffer[0], &_Buffer[0], BUFFERSIZE);
			_Current = Source._Current == &Source._Buffer[0] ? &_Buffer[0] : &_Buffer[1];
			_Next = Source._Next == &Source._Buffer[0] ? &_Buffer[0] : &_Buffer[1];
		}
		return *this;
	}

	template<class T, class Allocator>
	inline DoubleBuffer<T, Allocator>& DoubleBuffer<T, Allocator>::operator=(DoubleBuffer&& Right) noexcept
	{
		if (this != &Right)
		{
			_Buffer = Functional::Move(Right._Buffer);
			_Current = Functional::Move(Right._Current);
			_Next = Functional::Move(Right._Next);

			_Buffer = nullptr;
			_Current = nullptr;
			_Next = nullptr;
		}
		return *this;
	}

	template<class T, class Allocator>
	inline DoubleBuffer<T, Allocator>::Reference DoubleBuffer<T, Allocator>::GetCurrent()
	{
		return *_Current;
	}

	template<class T, class Allocator>
	inline DoubleBuffer<T, Allocator>::ConstReference DoubleBuffer<T, Allocator>::GetCurrent() const
	{
		return *_Current;
	}

	template<class T, class Allocator>
	inline void DoubleBuffer<T, Allocator>::Swap()
	{	// I could use Functional::Swap(...) but deem it unnecessary to call another function here
		Pointer Temporary = _Current;
		_Current = _Next;
		_Next = Temporary;
	}
}
#endif
