/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_FIXEDSIZEBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ALLOCATABLE
#include "../Concepts/Allocatable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Memory/DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INDEXOUTOFRANGEEXCEPTION
#include "../Exceptions/IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <class T, class Allocator = Elysium::Core::Template::Memory::DefaultAllocator<T>>
		requires Elysium::Core::Template::Concepts::Allocatable<T>
	class FixedSizeBuffer
	{
	public:
		using Pointer = T*;

		using Reference = T&;
		using ConstReference = const T&;
	public:
		constexpr FixedSizeBuffer() = delete;

		inline constexpr FixedSizeBuffer(const Elysium::Core::Template::System::size Capacity)
			: _Allocator(), _Capacity(Capacity == 0 ? 1 : Capacity), _Data(_Allocator.Allocate(_Capacity))
		{ }

		constexpr FixedSizeBuffer(const FixedSizeBuffer& Source) = delete;

		constexpr FixedSizeBuffer(FixedSizeBuffer&& Right) noexcept = delete;

		inline ~FixedSizeBuffer()
		{
			_Allocator.Deallocate(_Data, _Capacity);
			_Data = nullptr;
		}
	public:
		constexpr FixedSizeBuffer& operator=(const FixedSizeBuffer& Source) = delete;

		constexpr FixedSizeBuffer& operator=(FixedSizeBuffer&& Right) noexcept = delete;
	public:
		inline constexpr Reference operator[](const Elysium::Core::Template::System::size Index) noexcept
		{
			return _Data[Index];
		}

		inline constexpr ConstReference operator[](const Elysium::Core::Template::System::size Index) const noexcept
		{
			return _Data[Index];
		}
	public:
		inline constexpr const Elysium::Core::Template::System::size GetCapacity() const
		{
			return _Capacity;
		}
	public:
		inline constexpr Reference GetAt(const Elysium::Core::Template::System::size Index)
		{
			if (Index >= _Capacity)
			{
				throw Exceptions::IndexOutOfRangeException();
			}

			return _Data[Index];
		}

		inline constexpr ConstReference GetAt(const Elysium::Core::Template::System::size Index) const
		{
			if (Index >= _Capacity)
			{
				throw Exceptions::IndexOutOfRangeException();
			}

			return _Data[Index];
		}
	private:
		Allocator _Allocator;
		Elysium::Core::Template::System::size _Capacity;
		Pointer _Data;
	};
}
#endif
