/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_RINGBUFFER
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_RINGBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "../Concepts/NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_KEYVALUEPAIR
#include "KeyValuePair.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#include "../Math/Min.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Memory/DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <Elysium::Core::Template::Concepts::NonConstant T, class Allocator = Elysium::Core::Template::Memory::DefaultAllocator<T>>
	class RingBuffer
	{
	public:
		using Value = T;

		using Pointer = T*;
		using ConstPointer = const T*;

		using Reference = T&;
		using ConstReference = const T&;
		using RValueReference = T&&;
	public:
		inline constexpr RingBuffer(const Elysium::Core::Template::System::size Capacity) noexcept
			: _Allocator(), _Capacity(0 == Capacity ? 1 : Capacity), _Length(0), _Data(_Allocator.Allocate(_Capacity)), _Head(0), _Tail(0)
		{ }

		constexpr RingBuffer(const RingBuffer& Source) = delete;

		constexpr RingBuffer(RingBuffer&& Right) noexcept = delete;

		inline constexpr ~RingBuffer()
		{
			_Allocator.Deallocate(_Data, GetLength());
		}
	public:
		constexpr RingBuffer<T, Allocator>& operator=(const RingBuffer& Source) = delete;

		constexpr RingBuffer<T, Allocator>& operator=(RingBuffer&& Right) noexcept = delete;
	public:

	public:
		inline constexpr const Elysium::Core::Template::System::size GetCapacity() const noexcept
		{
			return _Capacity;
		}

		inline constexpr const Elysium::Core::Template::System::size GetLength() const noexcept
		{
			return _Length;
		}

		inline constexpr const Elysium::Core::Template::System::size GetHead() const noexcept
		{
			return _Head;
		}

		inline constexpr const Elysium::Core::Template::System::size GetTail() const noexcept
		{
			return _Tail;
		}

		inline constexpr const Elysium::Core::Template::System::size GetRemainingSpace() const noexcept
		{
			return _Capacity - _Length;
		}

		inline constexpr const bool GetIsEmpty() const noexcept
		{
			return 0 == _Length;
		}

		inline constexpr const bool GetIsFull() const noexcept
		{
			return _Length == _Capacity;
		}
	public:
		inline constexpr Reference operator[](const Elysium::Core::Template::System::size Index)
		{
			return _Data[Index];
		}

		inline constexpr ConstReference operator[](const Elysium::Core::Template::System::size Index) const
		{
			return _Data[Index];
		}
	public:
		inline void Push(ConstPointer FirstItem, const Elysium::Core::Template::System::size Length)
		{
			if (Length > GetRemainingSpace())
			{	// @ToDo: throw specific exception (OverflowException?)
				throw 1;
			}

			Elysium::Core::Template::System::size FirstChunkLength = Elysium::Core::Template::Math::Min(Length, _Capacity - _Tail);
			Elysium::Core::Template::Memory::MemCpy(&_Data[_Tail], FirstItem, FirstChunkLength);

			Elysium::Core::Template::System::size RemainingLength = Length - FirstChunkLength;
			if (0 < RemainingLength)
			{
				Elysium::Core::Template::Memory::MemCpy(&_Data[0], &FirstItem[FirstChunkLength], RemainingLength);
			}

			_Tail = (_Tail + Length) % _Length;
			_Length += Length;
		}

		inline void Pop(Pointer Buffer, const Elysium::Core::Template::System::size Length)
		{
			if (Length > _Length)
			{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
				throw 1;
			}

			Elysium::Core::Template::System::size FirstChunkLength = Elysium::Core::Template::Math::Min(Length, _Capacity - _Head);
			Elysium::Core::Template::Memory::MemCpy(Buffer, &_Data[_Head], FirstChunkLength);

			Elysium::Core::Template::System::size RemainingLength = Length - FirstChunkLength;
			if (0 < RemainingLength)
			{
				Elysium::Core::Template::Memory::MemCpy(&Buffer[FirstChunkLength], &_Data[0], RemainingLength);
			}

			Pop(Length);
		}

		inline void Pop(const Elysium::Core::Template::System::size Length)
		{
			if (Length > _Length)
			{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
				throw 1;
			}

			_Head = (_Head + Length) % _Length;
			_Length -= Length;
		}
	public:
		inline KeyValuePair<Pointer, Elysium::Core::Template::System::size> RequestReadableSpan()
		{
			if (GetIsEmpty())
			{
				return { nullptr, 0 };
			}

			const Elysium::Core::Template::System::size RemainingSpace = (_Head < _Tail) ? _Tail - _Head : _Capacity - _Head;
			return { &_Data[_Head], RemainingSpace };
		}

		inline void CommitReadableSpan(const Elysium::Core::Template::System::size Length)
		{
			if (!GetIsFull() && Length > _Length)
			{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
				throw 1;
			}

			_Head = (_Head + Length) % _Capacity;
			_Length -= Length;
		}

		inline KeyValuePair<Pointer, Elysium::Core::Template::System::size> RequestWriteableSpan()
		{
			if (GetIsFull())
			{
				return { nullptr, 0 };
			}

			const Elysium::Core::Template::System::size RemainingSpace = (_Tail >= _Head) ? _Capacity - _Tail : _Head - _Tail;
			return { &_Data[_Tail], RemainingSpace };
		}

		inline void CommitWritableSpan(const Elysium::Core::Template::System::size Length)
		{
			if (!GetIsEmpty() && Length > _Length)
			{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
				throw 1;
			}

			_Tail = (_Tail + Length) % _Capacity;
			_Length += Length;
		}
	private:
		Allocator _Allocator;
		Elysium::Core::Template::System::size _Capacity;
		Elysium::Core::Template::System::size _Length;
		Pointer _Data;

		Elysium::Core::Template::System::size _Head;
		Elysium::Core::Template::System::size _Tail;
	};
}
#endif
