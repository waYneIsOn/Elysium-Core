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
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <Elysium::Core::Template::Concepts::NonConstant T, class Allocator = Elysium::Core::Template::Memory::DefaultAllocator<T>>
	class RingBuffer
	{
	public:
		using Value = T;
		using Pointer = T*;
		using Reference = T&;
	public:
		constexpr RingBuffer(const Elysium::Core::Template::System::size Capacity) noexcept;

		constexpr RingBuffer(const RingBuffer& Source) = delete;

		constexpr RingBuffer(RingBuffer&& Right) noexcept = delete;

		constexpr ~RingBuffer();
	public:
		constexpr RingBuffer<T, Allocator>& operator=(const RingBuffer& Source) = delete;

		constexpr RingBuffer<T, Allocator>& operator=(RingBuffer&& Right) noexcept = delete;
	public:
		constexpr const Elysium::Core::Template::System::size GetLength() const noexcept;

		constexpr const bool GetIsEmpty() const noexcept;

		constexpr const bool GetIsFull() const noexcept;
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		Elysium::Core::Template::System::size _Capacity;
		T* _Data;
		T* _Begin;
		T* _End;
	};

	template<Elysium::Core::Template::Concepts::NonConstant T, class Allocator>
	inline constexpr RingBuffer<T, Allocator>::RingBuffer(const Elysium::Core::Template::System::size Capacity) noexcept
		: _Capacity(Capacity), _Data(_Allocator.Allocate(_Capacity)), _Begin(nullptr), _End(nullptr)
	{ }

	template<Elysium::Core::Template::Concepts::NonConstant T, class Allocator>
	inline constexpr RingBuffer<T, Allocator>::~RingBuffer()
	{
		_Allocator.Deallocate(_Data, GetLength());
	}

	template<Elysium::Core::Template::Concepts::NonConstant T, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size RingBuffer<T, Allocator>::GetLength() const noexcept
	{
		return (_End - _Begin + _Capacity) % _Capacity;
	}

	template<Elysium::Core::Template::Concepts::NonConstant T, class Allocator>
	inline constexpr const bool RingBuffer<T, Allocator>::GetIsEmpty() const noexcept
	{
		return GetLength() == 0;
	}

	template<Elysium::Core::Template::Concepts::NonConstant T, class Allocator>
	inline constexpr const bool RingBuffer<T, Allocator>::GetIsFull() const noexcept
	{
		return GetLength() == _Capacity;
	}
}
#endif
