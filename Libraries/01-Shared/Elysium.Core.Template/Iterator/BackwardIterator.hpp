/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_BACKWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_ITERATOR_BACKWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Iterator
{
	template <class Collection>
	class BackwardIterator final
	{
	public:
		using CollectionPointer = typename Collection::IteratorPointer;
		using CollectionReference = typename Collection::IteratorReference;
	public:
		constexpr BackwardIterator() = delete;

		constexpr BackwardIterator(CollectionPointer Current) noexcept;

		constexpr BackwardIterator(const BackwardIterator& Source) = delete;

		constexpr BackwardIterator(BackwardIterator&& Right) noexcept = delete;

		constexpr ~BackwardIterator() noexcept;
	public:
		constexpr BackwardIterator<Collection>& operator=(const BackwardIterator& Source) noexcept = delete;

		constexpr BackwardIterator<Collection>& operator=(BackwardIterator&& Right) noexcept = delete;
	public:
		constexpr const bool operator!=(const BackwardIterator& Other) const;

		constexpr BackwardIterator<Collection>& operator--();

		constexpr CollectionReference operator*();
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline constexpr BackwardIterator<Collection>::BackwardIterator(BackwardIterator<Collection>::CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline constexpr BackwardIterator<Collection>::~BackwardIterator() noexcept
	{ }

	template <class Collection>
	inline constexpr const bool BackwardIterator<Collection>::operator!=(const BackwardIterator<Collection>& Other) const
	{
		return _Current >= Other._Current;
	}

	template<class Collection>
	inline constexpr BackwardIterator<Collection>& BackwardIterator<Collection>::operator--()
	{
		_Current--;

		return *this;
	}

	template<class Collection>
	inline constexpr typename BackwardIterator<Collection>::CollectionReference BackwardIterator<Collection>::operator*()
	{
		return *_Current;
	}
}
#endif
