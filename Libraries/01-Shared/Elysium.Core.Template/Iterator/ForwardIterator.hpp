/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_FORWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_ITERATOR_FORWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Functional/Move.hpp"
#endif

namespace Elysium::Core::Template::Iterator
{
	template <class Collection>
	class ForwardIterator final
	{
	public:
		using CollectionPointer = typename Collection::IteratorPointer;
		using CollectionReference = typename Collection::IteratorReference;
	public:
		constexpr ForwardIterator() = delete;

		inline constexpr ForwardIterator(CollectionPointer Current) noexcept
			: _Current(Current)
		{ }

		inline constexpr ForwardIterator(const ForwardIterator& Source) noexcept
			: _Current(Source._Current)
		{ }

		inline constexpr ForwardIterator(ForwardIterator&& Right) noexcept
			: _Current(nullptr)
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		constexpr ~ForwardIterator() noexcept = default;
	public:
		inline constexpr ForwardIterator<Collection>& operator=(const ForwardIterator& Source) noexcept
		{
			if (this != &Source)
			{
				_Current = Source._Current;
			}

			return *this;
		}

		inline constexpr ForwardIterator<Collection>& operator=(ForwardIterator&& Right) noexcept
		{
			if (this != &Right)
			{
				_Current = Elysium::Core::Template::Functional::Move(Right._Current);

				Right._Current = nullptr;
			}

			return *this;
		}
	public:
		inline constexpr const bool operator!=(const ForwardIterator& Other) const noexcept
		{
			return _Current < Other._Current;
		}
	public:
		inline constexpr ForwardIterator<Collection>& operator++() noexcept
		{
			++_Current;

			return *this;
		}

		inline constexpr ForwardIterator<Collection>& operator--() noexcept
		{
			--_Current;

			return *this;
		}
	public:
		inline constexpr Elysium::Core::Template::System::size operator-(const ForwardIterator<Collection>& Other) const noexcept
		{
			return _Current - Other._Current;
		}
	public:
		inline constexpr ForwardIterator<Collection>& operator+=(const Elysium::Core::Template::System::size Count) noexcept
		{
			_Current += Count;

			return *this;
		}

		inline constexpr ForwardIterator<Collection> operator+(const Elysium::Core::Template::System::size Count) const noexcept
		{
			ForwardIterator<Collection> Temp = *this;
			Temp += Count;

			return Temp;
		}

		inline constexpr ForwardIterator<Collection>& operator-=(const Elysium::Core::Template::System::size Count) noexcept
		{
			_Current -= Count;

			return *this;
		}

		inline constexpr ForwardIterator<Collection> operator-(const Elysium::Core::Template::System::size Count) const noexcept
		{
			ForwardIterator<Collection> Temp = *this;
			Temp -= Count;

			return Temp;
		}
	public:
		inline constexpr CollectionReference operator*()
		{
			return *_Current;
		}
	private:
		CollectionPointer _Current;
	};
}
#endif
