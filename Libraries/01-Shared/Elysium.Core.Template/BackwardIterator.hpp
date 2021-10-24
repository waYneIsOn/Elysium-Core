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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
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
		BackwardIterator() = delete;
		BackwardIterator(CollectionPointer Current) noexcept;
		BackwardIterator(const BackwardIterator& Source) = delete;
		BackwardIterator(BackwardIterator&& Right) noexcept = delete;
		~BackwardIterator() noexcept;
	public:
		BackwardIterator<Collection>& operator=(const BackwardIterator& Source) noexcept = delete;
		BackwardIterator<Collection>& operator=(BackwardIterator&& Right) noexcept = delete;

		const bool operator==(const BackwardIterator& Other) const;
		const bool operator!=(const BackwardIterator& Other) const;
		const bool operator<(const BackwardIterator& Other) const;
		const bool operator>(const BackwardIterator& Other) const;
		const bool operator<=(const BackwardIterator& Other) const;
		const bool operator>=(const BackwardIterator& Other) const;

		BackwardIterator<Collection>& operator--();

		CollectionReference operator*();
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline BackwardIterator<Collection>::BackwardIterator(BackwardIterator<Collection>::CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline BackwardIterator<Collection>::~BackwardIterator() noexcept
	{ }

	template <class Collection>
	const bool BackwardIterator<Collection>::operator==(const BackwardIterator<Collection>& Other) const
	{
		return _Current == Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator!=(const BackwardIterator<Collection>& Other) const
	{
		return _Current != Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator<(const BackwardIterator<Collection>& Other) const
	{
		return _Current < Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator>(const BackwardIterator<Collection>& Other) const
	{
		return _Current > Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator<=(const BackwardIterator<Collection>& Other) const
	{
		return _Current <= Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator>=(const BackwardIterator<Collection>& Other) const
	{
		return _Current >= Other._Current;
	}

	template<class Collection>
	inline BackwardIterator<Collection>& BackwardIterator<Collection>::operator--()
	{
		_Current--;

		return *this;
	}

	template<class Collection>
	inline typename BackwardIterator<Collection>::CollectionReference BackwardIterator<Collection>::operator*()
	{
		return *_Current;
	}
}
#endif
