/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_FORWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_COLLECTIONS_FORWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Collections
{
	template <class Collection>
	class ForwardIterator
	{
	public:
		using CollectionValue = typename Collection::Value;
		using CollectionPointer = typename Collection::Pointer;
		using CollectionReference = typename Collection::Reference;
		using ConstCollectionReference = typename Collection::ConstReference;
	public:
		ForwardIterator() noexcept;
		ForwardIterator(CollectionPointer Current) noexcept;
		ForwardIterator(const ForwardIterator&Source) noexcept;
		ForwardIterator(ForwardIterator && Right) noexcept = delete;
		virtual ~ForwardIterator() noexcept;

		ForwardIterator<Collection>& operator=(const ForwardIterator& Source) noexcept = delete;
		ForwardIterator<Collection>& operator=(ForwardIterator&& Right) noexcept = delete;

		const bool operator==(const ForwardIterator& Other) const;
		const bool operator!=(const ForwardIterator& Other) const;
		const bool operator<(const ForwardIterator& Other) const;
		const bool operator>(const ForwardIterator& Other) const;
		const bool operator<=(const ForwardIterator& Other) const;
		const bool operator>=(const ForwardIterator& Other) const;

		ForwardIterator<Collection>& operator++();

		CollectionReference operator*();

		ConstCollectionReference operator*() const;
	private:
		CollectionPointer _Current;
	};

	template <class Collection>
	inline ForwardIterator<Collection>::ForwardIterator() noexcept
		: _Current(nullptr)
	{ }

	template<class Collection>
	inline ForwardIterator<Collection>::ForwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline ForwardIterator<Collection>::ForwardIterator(const ForwardIterator&Source) noexcept
		: _Current(Source._Current)
	{ }

	template <class Collection>
	inline ForwardIterator<Collection>::~ForwardIterator() noexcept
	{ }

	template <class Collection>
	const bool ForwardIterator<Collection>::operator==(const ForwardIterator & Other) const
	{
		return _Current == Other._Current;
	}

	template <class Collection>
	const bool ForwardIterator<Collection>::operator!=(const ForwardIterator& Other) const
	{
		return _Current != Other._Current;
	}

	template <class Collection>
	const bool ForwardIterator<Collection>::operator<(const ForwardIterator& Other) const
	{
		return _Current < Other._Current;
	}

	template <class Collection>
	const bool ForwardIterator<Collection>::operator>(const ForwardIterator& Other) const
	{
		return _Current > Other._Current;
	}

	template <class Collection>
	const bool ForwardIterator<Collection>::operator<=(const ForwardIterator& Other) const
	{
		return _Current <= Other._Current;
	}

	template <class Collection>
	const bool ForwardIterator<Collection>::operator>=(const ForwardIterator& Other) const
	{
		return _Current >= Other._Current;
	}

	template<class Collection>
	inline ForwardIterator<Collection>& ForwardIterator<Collection>::operator++()
	{
		_Current++;

		return *this;
	}
	template<class Collection>
	inline ForwardIterator<Collection>::CollectionReference ForwardIterator<Collection>::operator*()
	{
		return *_Current;
	}

	template<class Collection>
	inline ForwardIterator<Collection>::ConstCollectionReference ForwardIterator<Collection>::operator*() const
	{
		return *_Current;
	}
}
#endif
