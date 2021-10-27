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
		ConstBackwardIterator() = delete;
		ConstBackwardIterator(CollectionPointer Current) noexcept;
		ConstBackwardIterator(const ConstBackwardIterator& Source) = delete;
		ConstBackwardIterator(ConstBackwardIterator&& Right) noexcept = delete;
		~ConstBackwardIterator() noexcept;
	public:
		ConstBackwardIterator<Collection>& operator=(const ConstBackwardIterator& Source) noexcept = delete;
		ConstBackwardIterator<Collection>& operator=(ConstBackwardIterator&& Right) noexcept = delete;

		const bool operator!=(const ConstBackwardIterator& Other) const;

		ConstBackwardIterator<Collection>& operator--();

		ConstCollectionReference operator*() const;
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline ConstBackwardIterator<Collection>::ConstBackwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline ConstBackwardIterator<Collection>::~ConstBackwardIterator() noexcept
	{ }

	template<class Collection>
	inline const bool ConstBackwardIterator<Collection>::operator!=(const ConstBackwardIterator& Other) const
	{
		return _Current >= Other._Current;
	}

	template <class Collection>
	inline ConstBackwardIterator<Collection>& ConstBackwardIterator<Collection>::operator--()
	{
		_Current--;

		return *this;
	}

	template <class Collection>
	inline typename ConstBackwardIterator<Collection>::ConstCollectionReference ConstBackwardIterator<Collection>::operator*() const
	{
		return *_Current;
	}
}
#endif
