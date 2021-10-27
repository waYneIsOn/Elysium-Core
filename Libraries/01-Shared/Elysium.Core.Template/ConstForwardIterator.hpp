/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTFORWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTFORWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Iterator
{
	template <class Collection>
	class ConstForwardIterator final
	{
	public:
		using CollectionPointer = typename Collection::IteratorPointer;
		using ConstCollectionReference = typename Collection::ConstIteratorReference;
	public:
		ConstForwardIterator() = delete;
		ConstForwardIterator(CollectionPointer Current) noexcept;
		ConstForwardIterator(const ConstForwardIterator& Source) = delete;
		ConstForwardIterator(ConstForwardIterator&& Right) noexcept = delete;
		~ConstForwardIterator() noexcept;
	public:
		ConstForwardIterator<Collection>& operator=(const ConstForwardIterator& Source) noexcept = delete;
		ConstForwardIterator<Collection>& operator=(ConstForwardIterator&& Right) noexcept = delete;

		const bool operator!=(const ConstForwardIterator& Other) const;

		ConstForwardIterator<Collection>& operator++();

		ConstCollectionReference operator*() const;
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline ConstForwardIterator<Collection>::ConstForwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline ConstForwardIterator<Collection>::~ConstForwardIterator() noexcept
	{ }

	template <class Collection>
	const bool ConstForwardIterator<Collection>::operator!=(const ConstForwardIterator& Other) const
	{
		return _Current <= Other._Current;
	}

	template<class Collection>
	inline ConstForwardIterator<Collection>& ConstForwardIterator<Collection>::operator++()
	{
		_Current++;

		return *this;
	}

	template<class Collection>
	inline typename ConstForwardIterator<Collection>::ConstCollectionReference ConstForwardIterator<Collection>::operator*() const
	{
		return *_Current;
	}
}
#endif
