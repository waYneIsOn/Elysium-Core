/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_SLIDINGWINDOW
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_SLIDINGWINDOW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "../Concepts/NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_RINGBUFFER
#include "RingBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Memory/DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <Elysium::Core::Template::Concepts::NonConstant T, class Container = Elysium::Core::Template::Container::RingBuffer<T>>
	class SlidingWindow
	{
	public:
		using Value = Container::Value;
		using ConstValue = Container::ConstValue;

		using Pointer = Container::Pointer;
		using ConstPointer = Container::ConstPointer;

		using Reference = Container::Reference;
		using ConstReference = Container::ConstReference;
		using RValueReference = Container::RValueReference;
	public:
		constexpr SlidingWindow() = delete;

		inline constexpr SlidingWindow(const Elysium::Core::Template::System::size Capacity)
			: _Buffer(Capacity)
		{ }

		constexpr SlidingWindow(const SlidingWindow& Source) = delete;

		constexpr SlidingWindow(SlidingWindow&& Right) noexcept = delete;

		inline ~SlidingWindow() = default;
	public:
		constexpr SlidingWindow& operator=(const SlidingWindow& Source) = delete;

		constexpr SlidingWindow& operator=(SlidingWindow&& Right) noexcept = delete;
	public:
		inline constexpr Reference operator[](const Elysium::Core::Template::System::size Index)
		{
			return _Buffer[Index];
		}

		inline constexpr ConstReference operator[](const Elysium::Core::Template::System::size Index) const
		{
			return _Buffer[Index];
		}
	public:
		inline constexpr Elysium::Core::Template::System::size GetCapacity() const
		{
			return _Buffer.GetCapacity();
		}

		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			return _Buffer.GetLength();
		}

		inline constexpr const Elysium::Core::Template::System::size GetTail() const noexcept
		{
			return _Buffer.GetTail();
		}

		inline constexpr const bool GetIsEmpty() const noexcept(_Buffer.GetIsEmpty())
		{
			return _Buffer.GetIsEmpty();
		}

		inline constexpr const bool GetIsFull() const noexcept(_Buffer.GetIsFull())
		{
			return _Buffer.GetIsFull();
		}
	public:
		inline constexpr Reference GetAt(const Elysium::Core::Template::System::size Index)
		{
			return _Buffer.GetAt(Index);
		}

		inline constexpr ConstReference GetAt(const Elysium::Core::Template::System::size Index) const
		{
			return _Buffer.GetAt(Index);
		}
	public:
		inline void Clear() noexcept
		{
			_Buffer.Clear();
		}

		inline void Push(ConstPointer FirstItem, const Elysium::Core::Template::System::size Length)
		{ 
			_Buffer.Push(FirstItem, Length);
		}
		/*
		inline void Read(Pointer TargetBuffer, const Elysium::Core::Template::System::size Length)
		{
			_Buffer.Read(TargetBuffer, Length);
		}
		*/
	public:
		inline const Elysium::Core::Template::Container::View::MultiSpan<Value, 1024, 2> RequestReadableSpan() const
		{
			return _Buffer.RequestReadableSpan();
		}
	public:
		Container _Buffer;
	};
}
#endif
