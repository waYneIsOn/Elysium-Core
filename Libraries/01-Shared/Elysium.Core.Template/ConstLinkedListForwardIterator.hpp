/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTLINKEDLISTFORWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTLINKEDLISTFORWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Iterator
{
	template <class Collection>
	class ConstLinkedListForwardIterator final
	{
	public:
		using CollectionPointer = typename Collection::IteratorPointer;
		using ConstCollectionReference = typename Collection::ConstIteratorReference;
	public:
		ConstLinkedListForwardIterator() = delete;
		ConstLinkedListForwardIterator(CollectionPointer Current) noexcept;
		ConstLinkedListForwardIterator(const ConstLinkedListForwardIterator& Source) = delete;
		ConstLinkedListForwardIterator(ConstLinkedListForwardIterator&& Right) noexcept = delete;
		~ConstLinkedListForwardIterator() noexcept;
	public:
		ConstLinkedListForwardIterator<Collection>& operator=(const ConstLinkedListForwardIterator& Source) noexcept = delete;
		ConstLinkedListForwardIterator<Collection>& operator=(ConstLinkedListForwardIterator&& Right) noexcept = delete;

		const bool operator!=(const ConstLinkedListForwardIterator& Other) const;

		ConstLinkedListForwardIterator<Collection>& operator++();

		ConstCollectionReference operator*() const;
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline ConstLinkedListForwardIterator<Collection>::ConstLinkedListForwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline ConstLinkedListForwardIterator<Collection>::~ConstLinkedListForwardIterator() noexcept
	{ }

	template <class Collection>
	const bool ConstLinkedListForwardIterator<Collection>::operator!=(const ConstLinkedListForwardIterator& Other) const
	{
		return _Current != nullptr && _Current <= Other._Current;
	}

	template<class Collection>
	inline ConstLinkedListForwardIterator<Collection>& ConstLinkedListForwardIterator<Collection>::operator++()
	{
		_Current = _Current->GetNext();

		return *this;
	}

	template<class Collection>
	inline typename ConstLinkedListForwardIterator<Collection>::ConstCollectionReference ConstLinkedListForwardIterator<Collection>::operator*() const
	{
		return *_Current;
	}
}
#endif
