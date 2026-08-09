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

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "../Numeric/NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../System/Compiler.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#include <cassert>

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Allocator"></typeparam>
	/// <typeparam name="T"></typeparam>
	template <Elysium::Core::Template::Concepts::NonConstant T, Elysium::Core::Template::System::size Capacity, class Allocator = Elysium::Core::Template::Memory::DefaultAllocator<T>>
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
		inline static constexpr const bool CanUseFastModulo = Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::size>::IsPowerOfTwo(Capacity);

		inline static constexpr const Elysium::Core::Template::System::size Mask = (Capacity - 1);
	public:
		inline constexpr RingBuffer() noexcept
			: _Allocator(), _Length(0), _Data(_Allocator.Allocate(Capacity)), _Head(0), _Tail(0)
		{ }

		constexpr RingBuffer(const RingBuffer& Source) = delete;

		constexpr RingBuffer(RingBuffer&& Right) noexcept = delete;

		inline constexpr ~RingBuffer()
		{
			_Allocator.Deallocate(_Data, GetLength());
		}
	public:
		constexpr RingBuffer<T, Capacity, Allocator>& operator=(const RingBuffer& Source) = delete;

		constexpr RingBuffer<T, Capacity, Allocator>& operator=(RingBuffer&& Right) noexcept = delete;
	public:
		inline constexpr Reference operator[](const Elysium::Core::Template::System::size Index)
		{
			const Elysium::Core::Template::System::size WrappedIndex = CanUseFastModulo ? (_Head + Index) & Mask : (_Head + Index) % Capacity;
			return _Data[WrappedIndex];
		}

		inline constexpr ConstReference operator[](const Elysium::Core::Template::System::size Index) const
		{
			const Elysium::Core::Template::System::size WrappedIndex = CanUseFastModulo ? (_Head + Index) & Mask : (_Head + Index) % Capacity;
			return _Data[WrappedIndex];
		}
	public:
		inline constexpr const Elysium::Core::Template::System::size GetCapacity() const noexcept
		{
			return Capacity;
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
			return Capacity - _Length;
		}

		inline constexpr const bool GetIsEmpty() const noexcept
		{
			return 0 == _Length;
		}

		inline constexpr const bool GetIsFull() const noexcept
		{
			return _Length == Capacity;
		}
	public:
		inline void Clear()
		{
			_Length = 0;
			_Head = 0;
			_Tail = 0;
		}
		/*
		inline void Read(Pointer TargetBuffer, const Elysium::Core::Template::System::size Length)
		{
			if (Length > _Length)
			{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
				throw 1;
			}

			Elysium::Core::Template::System::size FirstChunkLength = Elysium::Core::Template::Math::Min(Length, Capacity - _Head);
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
			if (Length > _Length)
			{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
				throw 1;
			}

			_Head = (_Head + Length) % _Length;
			_Length -= Length;
		}
		*/
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

			return { &_Data[_Head], Capacity - _Head, &_Data[0], _Tail };
		}
		
		inline void CommitReadableSpan(const Elysium::Core::Template::System::size Length)
		{
			if (0 == Length)
			{
				return;
			}

			if (Length > _Length)
			{	// @ToDo: throw specific exception (OverflowException? actual underflow but w/e)
				throw 1;
			}

			_Head = CanUseFastModulo ? (_Head + Length) & Mask : (_Head + Length) % Capacity;
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

			const Elysium::Core::Template::System::size Length0 = Capacity - _Tail; 
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
			if (0 == Length)
			{
				return;
			}

			if (Length > Capacity - _Length)
			{	// @ToDo: throw specific exception (OverflowException?)
				throw 1;
			}

			_Tail = CanUseFastModulo ? (_Tail + Length) & Mask : (_Tail + Length) % Capacity;
			_Length += Length;
			if (_Length > Capacity)
			{
				const Elysium::Core::Template::System::size Overflow = _Length - Capacity;

				_Length = Capacity;
				_Head = CanUseFastModulo ? (_Head + Overflow) & Mask : (_Head + Overflow) % Capacity;
			}
		}
	public:
		inline void CopyFromHistory(const Elysium::Core::Template::System::size Distance, const Elysium::Core::Template::System::size Length)
		{
			assert(Distance > 0);
			assert(Distance <= _Length);
			assert(Length > 0);
			
			if (Distance >= Length)
			{	// no overlap of source- and destination-ranges 
				const Elysium::Core::Template::System::size SourceIndex = CanUseFastModulo ? (_Tail - Distance) & Mask : (_Tail - Distance) % Capacity;
				const Elysium::Core::Template::System::size TargetIndex = _Tail;

				const bool SourceFits = SourceIndex + Length <= Capacity;
				const bool TargetFits = TargetIndex + Length <= Capacity;

				if (SourceFits && TargetFits)
				{
					Elysium::Core::Template::Memory::MemCpy(&_Data[TargetIndex], &_Data[SourceIndex], Length * sizeof(Value));

					_Tail = CanUseFastModulo ? (_Tail + Length) & Mask : (_Tail + Length) % Capacity;
					_Length += Length;

					if (_Length > Capacity)
					{
						const Elysium::Core::Template::System::size Overflow = _Length - Capacity;

						_Length = Capacity;
						_Head = CanUseFastModulo ? (_Head + Overflow) & Mask : (_Head + Overflow) % Capacity;
					}

					return;
				}
			}
			
			// overlap or ...
			Elysium::Core::Template::System::size SourceIndex = CanUseFastModulo ? (_Tail - Distance) & Mask : (_Tail - Distance) % Capacity;
			Elysium::Core::Template::System::size TargetIndex = _Tail;
			for (Elysium::Core::Template::System::size i = 0; i < Length; ++i)
			{
				const Value Symbol = _Data[SourceIndex];

				_Data[TargetIndex] = Symbol;

				if constexpr (CanUseFastModulo)
				{
					SourceIndex = (++SourceIndex) & Mask;
					TargetIndex = (++TargetIndex) & Mask;
				}
				else
				{
					SourceIndex = (++SourceIndex) % Capacity;
					TargetIndex = (++TargetIndex) % Capacity;
				}
			}

			_Tail = CanUseFastModulo ? (_Tail + Length) & Mask : (_Tail + Length) % Capacity;
			_Length += Length;
			if (_Length > Capacity)
			{
				const Elysium::Core::Template::System::size Overflow = _Length - Capacity;

				_Length = Capacity;
				_Head = CanUseFastModulo ? (_Head + Overflow) & Mask : (_Head + Overflow) % Capacity;
			}
		}
	private:
		Allocator _Allocator;
		Elysium::Core::Template::System::size _Length;
		Pointer _Data;

		Elysium::Core::Template::System::size _Head;
		Elysium::Core::Template::System::size _Tail;
	};
}
#endif
