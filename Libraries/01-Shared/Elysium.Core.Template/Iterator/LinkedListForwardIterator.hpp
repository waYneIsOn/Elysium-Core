/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_LINKEDLISTFORWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_ITERATOR_LINKEDLISTFORWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Iterator
{
	template <class Collection>
	class LinkedListForwardIterator final
	{
	public:
		using CollectionPointer = typename Collection::IteratorPointer;
		using CollectionReference = typename Collection::IteratorReference;
	public:
		LinkedListForwardIterator() = delete;
		LinkedListForwardIterator(CollectionPointer Current) noexcept;
		LinkedListForwardIterator(const LinkedListForwardIterator& Source) = delete;
		LinkedListForwardIterator(LinkedListForwardIterator&& Right) noexcept = delete;
		~LinkedListForwardIterator() noexcept;
	public:
		LinkedListForwardIterator<Collection>& operator=(const LinkedListForwardIterator& Source) noexcept = delete;
		LinkedListForwardIterator<Collection>& operator=(LinkedListForwardIterator&& Right) noexcept = delete;

		const bool operator!=(const LinkedListForwardIterator& Other) const;

		LinkedListForwardIterator<Collection>& operator++();

		CollectionReference operator*();
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline LinkedListForwardIterator<Collection>::LinkedListForwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline LinkedListForwardIterator<Collection>::~LinkedListForwardIterator() noexcept
	{ }

	template <class Collection>
	const bool LinkedListForwardIterator<Collection>::operator!=(const LinkedListForwardIterator& Other) const
	{
		return _Current != nullptr && _Current <= Other._Current;
	}

	template<class Collection>
	inline LinkedListForwardIterator<Collection>& LinkedListForwardIterator<Collection>::operator++()
	{
		_Current = _Current->GetNext();

		return *this;
	}

	template<class Collection>
	inline typename LinkedListForwardIterator<Collection>::CollectionReference LinkedListForwardIterator<Collection>::operator*()
	{
		return *_Current;
	}
}
#endif
