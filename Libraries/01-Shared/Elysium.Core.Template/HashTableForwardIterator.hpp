/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_HASHTABLEFORWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_ITERATOR_HASHTABLEFORWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Iterator
{
	template <class Collection>
	class HashTableForwardIterator final
	{
	public:
		using LinkedListPointer = typename Collection::BucketPointer;
		using LinkedListReference = typename Collection::BucketReference;

		using LinkedListNodePointer = typename Collection::BucketNodePointer;
	public:
		HashTableForwardIterator() = delete;
		HashTableForwardIterator(LinkedListPointer CurrentBucket, LinkedListNodePointer CurrentEntry) noexcept;
		HashTableForwardIterator(const HashTableForwardIterator& Source) = delete;
		HashTableForwardIterator(HashTableForwardIterator&& Right) noexcept = delete;
		~HashTableForwardIterator() noexcept;
	public:
		HashTableForwardIterator<Collection>& operator=(const HashTableForwardIterator& Source) noexcept = delete;
		HashTableForwardIterator<Collection>& operator=(HashTableForwardIterator&& Right) noexcept = delete;

		const bool operator==(const HashTableForwardIterator& Other) const;
		const bool operator!=(const HashTableForwardIterator& Other) const;

		HashTableForwardIterator<Collection>& operator++();

		HashTableForwardIterator<Collection>::LinkedListNodePointer operator*();
	private:
		LinkedListPointer _CurrentBucket;
		LinkedListNodePointer _CurrentEntry;

		void GetNextNoneEmptyBucket();
	};

	template<class Collection>
	inline HashTableForwardIterator<Collection>::HashTableForwardIterator(LinkedListPointer CurrentBucket, LinkedListNodePointer CurrentEntry) noexcept
		: _CurrentBucket(CurrentBucket), _CurrentEntry(CurrentEntry)
	{ }

	template <class Collection>
	inline HashTableForwardIterator<Collection>::~HashTableForwardIterator() noexcept
	{ }

	template <class Collection>
	const bool HashTableForwardIterator<Collection>::operator==(const HashTableForwardIterator& Other) const
	{
		return _CurrentEntry == Other._CurrentEntry;
	}

	template <class Collection>
	const bool HashTableForwardIterator<Collection>::operator!=(const HashTableForwardIterator& Other) const
	{
		return _CurrentEntry != Other._CurrentEntry;
	}

	template<class Collection>
	inline HashTableForwardIterator<Collection>& HashTableForwardIterator<Collection>::operator++()
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
	inline typename HashTableForwardIterator<Collection>::LinkedListNodePointer HashTableForwardIterator<Collection>::operator*()
	{
		return _CurrentEntry;
	}

	template<class Collection>
	void HashTableForwardIterator<Collection>::GetNextNoneEmptyBucket()
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
