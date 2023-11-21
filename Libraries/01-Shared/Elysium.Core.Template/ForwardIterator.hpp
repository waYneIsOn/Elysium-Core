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

		constexpr ForwardIterator(CollectionPointer Current) noexcept;

		constexpr ForwardIterator(const ForwardIterator&Source) = delete;

		constexpr ForwardIterator(ForwardIterator && Right) noexcept = delete;

		constexpr ~ForwardIterator() noexcept;
	public:
		constexpr ForwardIterator<Collection>& operator=(const ForwardIterator& Source) noexcept = delete;

		constexpr ForwardIterator<Collection>& operator=(ForwardIterator&& Right) noexcept = delete;
	public:
		constexpr const bool operator!=(const ForwardIterator& Other) const;

		constexpr ForwardIterator<Collection>& operator++();

		constexpr CollectionReference operator*();
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline constexpr ForwardIterator<Collection>::ForwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline constexpr ForwardIterator<Collection>::~ForwardIterator() noexcept
	{ }

	template <class Collection>
	inline constexpr const bool ForwardIterator<Collection>::operator!=(const ForwardIterator& Other) const
	{
		return _Current <= Other._Current;
	}

	template<class Collection>
	inline constexpr ForwardIterator<Collection>& ForwardIterator<Collection>::operator++()
	{
		_Current++;

		return *this;
	}

	template<class Collection>
	inline constexpr typename ForwardIterator<Collection>::CollectionReference ForwardIterator<Collection>::operator*()
	{
		return *_Current;
	}
}
#endif
