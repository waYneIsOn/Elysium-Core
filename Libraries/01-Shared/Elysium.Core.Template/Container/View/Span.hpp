/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container::View
{
	template <class T, Elysium::Core::Template::System::size Extent = 1024>
	class Span final
	{
	public:
		using Pointer = T*;
		using ConstPointer = const T*;
	public:
		constexpr Span() = default;

		inline constexpr Span(ConstPointer Data, const Elysium::Core::Template::System::size Length)
			: _Data(const_cast<Pointer>(Data)), _Length(Length)
		{ }

		constexpr Span(const Span& Source) = default;

		constexpr Span(Span&& Right) noexcept = default;

		constexpr ~Span() = default;
	public:
		constexpr Span<T, Extent>& operator=(const Span& Source) = default;

		constexpr Span<T, Extent>& operator=(Span&& Right) noexcept = default;
	public:
		inline Pointer GetData() noexcept
		{
			return _Data;
		}

		inline const Elysium::Core::Template::System::size GetLength() const noexcept
		{
			return _Length;
		}

		inline const bool IsEmpty() const noexcept
		{
			return nullptr == _Data || 0 == _Length || _Data == _Data[_Length];
		}
	public:
		inline void SetData(ConstPointer Data) noexcept
		{
			_Data = const_cast<Pointer>(Data);
		}

		inline void SetLength(const Elysium::Core::Template::System::size Length) noexcept
		{
			_Length = Length;
		}
	private:
		Pointer _Data;
		Elysium::Core::Template::System::size _Length;
	};
}
#endif
