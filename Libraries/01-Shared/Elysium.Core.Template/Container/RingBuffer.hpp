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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_MULTISPAN
#include "View/MultiSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_MULTISPAN
#include "../Container/View/MultiSpan.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../System/Compiler.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Allocator"></typeparam>
	/// <typeparam name="T"></typeparam>
	template <Elysium::Core::Template::Concepts::NonConstant T, bool AllowOverflow = false, class Allocator = Elysium::Core::Template::Memory::DefaultAllocator<T>>
	class RingBuffer
	{
	public:
		using Value = T;
		using ConstValue = const T;

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
		constexpr RingBuffer<T, AllowOverflow, Allocator>& operator=(const RingBuffer& Source) = delete;

		constexpr RingBuffer<T, AllowOverflow, Allocator>& operator=(RingBuffer&& Right) noexcept = delete;
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
		inline void Clear()
		{
			_Length = 0;
			_Head = 0;
			_Tail = 0;
		}

		inline void Push(ConstPointer FirstItem, const Elysium::Core::Template::System::size Length)
		{
			if constexpr (AllowOverflow)
			{
				if (Length > GetRemainingSpace())
				{	// @ToDo: throw specific exception (OverflowException?)
					throw 1;
				}
			}

			Elysium::Core::Template::System::size FirstChunkLength = Elysium::Core::Template::Math::Min(Length, _Capacity - _Tail);
			Elysium::Core::Template::Memory::MemCpy(&_Data[_Tail], FirstItem, FirstChunkLength);

			Elysium::Core::Template::System::size RemainingLength = Length - FirstChunkLength;
			if (0 < RemainingLength)
			{
				Elysium::Core::Template::Memory::MemCpy(&_Data[0], &FirstItem[FirstChunkLength], RemainingLength);
			}

			_Tail = (_Tail + Length) % _Capacity;
			_Length += Length;
		}

		inline void Read(Pointer TargetBuffer, const Elysium::Core::Template::System::size Length)
		{
			if constexpr (AllowOverflow)
			{
				if (Length > _Length)
				{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
					throw 1;
				}
			}

			Elysium::Core::Template::System::size FirstChunkLength = Elysium::Core::Template::Math::Min(Length, _Capacity - _Head);
			Elysium::Core::Template::Memory::MemCpy(TargetBuffer, &_Data[_Head], FirstChunkLength);

			Elysium::Core::Template::System::size RemainingLength = Length - FirstChunkLength;
			if (0 < RemainingLength)
			{
				Elysium::Core::Template::Memory::MemCpy(&TargetBuffer[FirstChunkLength], &_Data[0], RemainingLength);
			}
		}

		inline void Pop(Pointer TargetBuffer, const Elysium::Core::Template::System::size Length)
		{
			Read(TargetBuffer, Length);
			Pop(Length);
		}

		inline void Pop(const Elysium::Core::Template::System::size Length)
		{
			if constexpr (AllowOverflow)
			{
				if (Length > _Length)
				{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
					throw 1;
				}
			}

			_Head = (_Head + Length) % _Length;
			_Length -= Length;
		}
	public:
		inline const Elysium::Core::Template::Container::View::MultiSpan<Value, 1024, 2> RequestReadableSpan() const noexcept
		{
			if (GetIsEmpty())
			{
				return { nullptr, 0, nullptr, 0 };
			}
			
			if (_Head < _Tail)
			{	// continuous memory can simply be held by the first span
				return { &_Data[_Head], _Tail - _Head, nullptr, 0 };
			}

			return { &_Data[_Head], _Capacity - _Head, &_Data[0], _Tail };
		}

		template <class T>
		inline T* TryGetContiguous(Elysium::Core::Template::Container::View::MultiSpan<Value, 1024, 2> Spans)
		{
			if (Spans.GetFirst().GetLength() >= sizeof(T)) ELYSIUM_CORE_PATH_LIKELY
			{
				return reinterpret_cast<T*>(Spans.GetFirst().GetData());
			}

			return nullptr;
		}

		template <class T>
		inline T* TryGetContiguous(Elysium::Core::Template::Container::View::MultiSpan<Value, 1024, 2> Spans, const Elysium::Core::Template::System::size Length)
		{
			if (Spans.GetFirst().GetLength() >= sizeof(T) * Length) ELYSIUM_CORE_PATH_LIKELY
			{
				return reinterpret_cast<T*>(Spans.GetFirst().GetData());
			}

			return nullptr;
		}

		inline void CommitReadableSpan(const Elysium::Core::Template::System::size Length)
		{
			if (Length > _Length)
			{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
				throw 1;
			}

			_Head = (_Head + Length) % _Capacity;
			_Length -= Length;
		}
	public:
		inline Elysium::Core::Template::Container::View::MultiSpan<Value, 1024, 2> RequestWriteableSpan() const noexcept
		{
			if (GetIsFull())
			{
				return { nullptr, 0, nullptr, 0 };
			}

			if (_Tail < _Head)
			{	// continuous memory can simply be held by the first span
				return { &_Data[_Tail], _Head - _Tail, nullptr, 0 };
			}

			const Elysium::Core::Template::System::size Length0 = _Capacity - _Tail; 
			const Elysium::Core::Template::System::size Available = GetRemainingSpace();

			if (Length0 >= Available)
			{	// there is enough room from _Tail to _Data[_Capacity] to fit everything into a single span here as well
				return { &_Data[_Tail], Available, nullptr, 0 };
			}
			else
			{
				const Elysium::Core::Template::System::size Length1 = Elysium::Core::Template::Math::Min(_Head, Available - Length0);
				return { &_Data[_Tail], Length0, &_Data[0], Length1 };
			}
		}

		inline void CommitWritableSpan(const Elysium::Core::Template::System::size Length)
		{
			if (Length > (_Capacity - _Length))
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
