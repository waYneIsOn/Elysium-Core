/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTBACKWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTBACKWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Iterator
{
	template <class Collection>
	class ConstBackwardIterator final
	{
	public:
		using CollectionPointer = typename Collection::IteratorPointer;
		using ConstCollectionReference = typename Collection::ConstIteratorReference;
	public:
		constexpr ConstBackwardIterator() = delete;

		constexpr ConstBackwardIterator(CollectionPointer Current) noexcept;

		constexpr ConstBackwardIterator(const ConstBackwardIterator& Source) = delete;

		constexpr ConstBackwardIterator(ConstBackwardIterator&& Right) noexcept = delete;

		constexpr ~ConstBackwardIterator() noexcept;
	public:
		constexpr ConstBackwardIterator<Collection>& operator=(const ConstBackwardIterator& Source) noexcept = delete;

		constexpr ConstBackwardIterator<Collection>& operator=(ConstBackwardIterator&& Right) noexcept = delete;
	public:
		constexpr const bool operator!=(const ConstBackwardIterator& Other) const;

		constexpr ConstBackwardIterator<Collection>& operator--();

		constexpr ConstCollectionReference operator*() const;
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline constexpr ConstBackwardIterator<Collection>::ConstBackwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline constexpr ConstBackwardIterator<Collection>::~ConstBackwardIterator() noexcept
	{ }

	template<class Collection>
	inline constexpr const bool ConstBackwardIterator<Collection>::operator!=(const ConstBackwardIterator& Other) const
	{
		return _Current >= Other._Current;
	}

	template <class Collection>
	inline constexpr ConstBackwardIterator<Collection>& ConstBackwardIterator<Collection>::operator--()
	{
		_Current--;

		return *this;
	}

	template <class Collection>
	inline constexpr typename ConstBackwardIterator<Collection>::ConstCollectionReference ConstBackwardIterator<Collection>::operator*() const
	{
		return *_Current;
	}
}
#endif
