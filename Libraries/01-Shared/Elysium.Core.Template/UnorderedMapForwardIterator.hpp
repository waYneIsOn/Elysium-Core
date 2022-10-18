/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_UNORDEREDMAPFORWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_ITERATOR_UNORDEREDMAPFORWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Iterator
{
	template <class Collection>
	class UnorderedMapForwardIterator final
	{
	public:
		using LinkedListPointer = typename Collection::BucketPointer;
		using LinkedListReference = typename Collection::BucketReference;

		using LinkedListNodePointer = typename Collection::BucketNodePointer;
	public:
		UnorderedMapForwardIterator() = delete;

		UnorderedMapForwardIterator(LinkedListPointer CurrentBucket, LinkedListNodePointer CurrentEntry) noexcept;

		UnorderedMapForwardIterator(const UnorderedMapForwardIterator& Source) = delete;

		UnorderedMapForwardIterator(UnorderedMapForwardIterator&& Right) noexcept = delete;

		~UnorderedMapForwardIterator() noexcept;
	public:
		UnorderedMapForwardIterator<Collection>& operator=(const UnorderedMapForwardIterator& Source) noexcept = delete;

		UnorderedMapForwardIterator<Collection>& operator=(UnorderedMapForwardIterator&& Right) noexcept = delete;
	public:
		const bool operator==(const UnorderedMapForwardIterator& Other) const;

		const bool operator!=(const UnorderedMapForwardIterator& Other) const;
	public:
		UnorderedMapForwardIterator<Collection>& operator++();

		UnorderedMapForwardIterator<Collection>::LinkedListNodePointer operator*();
	private:
		LinkedListPointer _CurrentBucket;
		LinkedListNodePointer _CurrentEntry;

		void GetNextNoneEmptyBucket();
	};

	template<class Collection>
	inline UnorderedMapForwardIterator<Collection>::UnorderedMapForwardIterator(LinkedListPointer CurrentBucket, LinkedListNodePointer CurrentEntry) noexcept
		: _CurrentBucket(CurrentBucket), _CurrentEntry(CurrentEntry)
	{ }

	template <class Collection>
	inline UnorderedMapForwardIterator<Collection>::~UnorderedMapForwardIterator() noexcept
	{ }

	template <class Collection>
	const bool UnorderedMapForwardIterator<Collection>::operator==(const UnorderedMapForwardIterator& Other) const
	{
		return _CurrentEntry == Other._CurrentEntry;
	}

	template <class Collection>
	const bool UnorderedMapForwardIterator<Collection>::operator!=(const UnorderedMapForwardIterator& Other) const
	{
		return _CurrentEntry != Other._CurrentEntry;
	}

	template<class Collection>
	inline UnorderedMapForwardIterator<Collection>& UnorderedMapForwardIterator<Collection>::operator++()
	{
		do
		{
			_CurrentEntry = _CurrentEntry->GetNext();
			if (_CurrentEntry == nullptr)
			{
				GetNextNoneEmptyBucket();
			}
		} while (_CurrentEntry == nullptr);

		return *this;
	}

	template<class Collection>
	inline typename UnorderedMapForwardIterator<Collection>::LinkedListNodePointer UnorderedMapForwardIterator<Collection>::operator*()
	{
		return _CurrentEntry;
	}

	template<class Collection>
	void UnorderedMapForwardIterator<Collection>::GetNextNoneEmptyBucket()
	{
		_CurrentBucket++;
		_CurrentEntry = _CurrentBucket->GetHead();

		if (_CurrentEntry == nullptr)
		{
			GetNextNoneEmptyBucket();
		}
	}
}
#endif
