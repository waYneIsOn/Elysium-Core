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
		ForwardIterator() = delete;
		ForwardIterator(CollectionPointer Current) noexcept;
		ForwardIterator(const ForwardIterator&Source) = delete;
		ForwardIterator(ForwardIterator && Right) noexcept = delete;
		~ForwardIterator() noexcept;
	public:
		ForwardIterator<Collection>& operator=(const ForwardIterator& Source) noexcept = delete;
		ForwardIterator<Collection>& operator=(ForwardIterator&& Right) noexcept = delete;

		const bool operator!=(const ForwardIterator& Other) const;

		ForwardIterator<Collection>& operator++();

		CollectionReference operator*();
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline ForwardIterator<Collection>::ForwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline ForwardIterator<Collection>::~ForwardIterator() noexcept
	{ }

	template <class Collection>
	const bool ForwardIterator<Collection>::operator!=(const ForwardIterator& Other) const
	{
		return _Current <= Other._Current;
	}

	template<class Collection>
	inline ForwardIterator<Collection>& ForwardIterator<Collection>::operator++()
	{
		_Current++;

		return *this;
	}

	template<class Collection>
	inline typename ForwardIterator<Collection>::CollectionReference ForwardIterator<Collection>::operator*()
	{
		return *_Current;
	}
}
#endif
