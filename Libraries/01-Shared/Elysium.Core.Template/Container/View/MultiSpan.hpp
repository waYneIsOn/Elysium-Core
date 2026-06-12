/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_MULTISPAN
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_MULTISPAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#include "Span.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container::View
{
	template <class T, Elysium::Core::Template::System::size Extents, Elysium::Core::Template::System::size N>
	class MultiSpan final
	{
	public:
		using Pointer = Span<T, Extents>::Pointer;
		using ConstPointer = Span<T, Extents>::ConstPointer;
	public:
		constexpr MultiSpan() = delete;

		constexpr MultiSpan(const MultiSpan& Source) = default;

		constexpr MultiSpan(MultiSpan&& Right) noexcept = default;

		constexpr ~MultiSpan() = default;
	public:
		constexpr MultiSpan<T, Extents, N>& operator=(const MultiSpan& Source) = default;

		constexpr MultiSpan<T, Extents, N>& operator=(MultiSpan&& Right) noexcept = default;
	private:

	};

	template <class T, Elysium::Core::Template::System::size Extents>
	class MultiSpan<T, Extents, 2> final
	{
	public:
		using Span = Span<T, Extents>;

		using Pointer = Span::Pointer;
		using ConstPointer = Span::ConstPointer;
	public:
		constexpr MultiSpan() = delete;

		inline constexpr MultiSpan(ConstPointer Data0, const Elysium::Core::Template::System::size Length0, ConstPointer Data1, const Elysium::Core::Template::System::size Length1)
			: _Spans{ { Data0, Length0 }, { Data1, Length1 } }
		{ }

		inline constexpr MultiSpan(const Span Span0, const Span Span1)
			: _Spans{ Span0, Span1 }
		{ }

		constexpr MultiSpan(const MultiSpan& Source) = default;

		constexpr MultiSpan(MultiSpan&& Right) noexcept = default;

		constexpr ~MultiSpan() = default;
	public:
		constexpr MultiSpan<T, Extents, 2>& operator=(const MultiSpan& Source) = default;

		constexpr MultiSpan<T, Extents, 2>& operator=(MultiSpan&& Right) noexcept = default;
	public:
		/// <summary>
		/// Returns a copy of the first span.
		/// </summary>
		/// <returns></returns>
		inline Elysium::Core::Template::Container::View::Span<T, Extents> GetFirst()
		{
			return _Spans[0];
		}

		/// <summary>
		/// Returns a copy of the second span.
		/// </summary>
		/// <returns></returns>
		inline Elysium::Core::Template::Container::View::Span<T, Extents> GetSecond()
		{
			return _Spans[1];
		}
	private:
		Span _Spans[2];
	};
}
#endif
