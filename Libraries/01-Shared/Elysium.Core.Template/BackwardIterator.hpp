/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_BACKWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_COLLECTIONS_BACKWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Collections
{
	template <class Collection>
	class BackwardIterator
	{
	public:
		using CollectionValue = typename Collection::Value;
		using CollectionPointer = typename Collection::Pointer;
		using CollectionReference = typename Collection::Reference;
		using ConstCollectionReference = typename Collection::ConstReference;
	public:
		BackwardIterator() noexcept;
		BackwardIterator(CollectionPointer Current) noexcept;
		BackwardIterator(const BackwardIterator& Source) noexcept;
		BackwardIterator(BackwardIterator&& Right) noexcept = delete;
		virtual ~BackwardIterator() noexcept;

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

		ConstCollectionReference operator*() const;
	private:
		CollectionPointer _Current;
	};

	template <class Collection>
	inline BackwardIterator<Collection>::BackwardIterator() noexcept
		: _Current(nullptr)
	{ }

	template<class Collection>
	inline BackwardIterator<Collection>::BackwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline BackwardIterator<Collection>::BackwardIterator(const BackwardIterator& Source) noexcept
		: _Current(Source._Current)
	{ }

	template <class Collection>
	inline BackwardIterator<Collection>::~BackwardIterator() noexcept
	{ }

	template <class Collection>
	const bool BackwardIterator<Collection>::operator==(const BackwardIterator& Other) const
	{
		return _Current == Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator!=(const BackwardIterator& Other) const
	{
		return _Current != Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator<(const BackwardIterator& Other) const
	{
		return _Current < Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator>(const BackwardIterator& Other) const
	{
		return _Current > Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator<=(const BackwardIterator& Other) const
	{
		return _Current <= Other._Current;
	}

	template <class Collection>
	const bool BackwardIterator<Collection>::operator>=(const BackwardIterator& Other) const
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
	inline BackwardIterator<Collection>::CollectionReference BackwardIterator<Collection>::operator*()
	{
		return *_Current;
	}

	template<class Collection>
	inline BackwardIterator<Collection>::ConstCollectionReference BackwardIterator<Collection>::operator*() const
	{
		return *_Current;
	}
}
#endif
