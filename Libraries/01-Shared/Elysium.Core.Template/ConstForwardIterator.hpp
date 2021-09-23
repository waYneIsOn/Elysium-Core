/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_CONSTFORWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_CONSTFORWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <class Collection>
	class ConstForwardIterator final
	{
	public:
		using CollectionPointer = typename Collection::Pointer;
		using ConstCollectionReference = typename Collection::ConstReference;
	public:
		ConstForwardIterator() noexcept;
		ConstForwardIterator(CollectionPointer Current) noexcept;
		ConstForwardIterator(const ConstForwardIterator& Source) noexcept;
		ConstForwardIterator(ConstForwardIterator&& Right) noexcept = delete;
		~ConstForwardIterator() noexcept;

		ConstForwardIterator<Collection>& operator=(const ConstForwardIterator& Source) noexcept = delete;
		ConstForwardIterator<Collection>& operator=(ConstForwardIterator&& Right) noexcept = delete;

		const bool operator==(const ConstForwardIterator& Other) const;
		const bool operator!=(const ConstForwardIterator& Other) const;
		const bool operator<(const ConstForwardIterator& Other) const;
		const bool operator>(const ConstForwardIterator& Other) const;
		const bool operator<=(const ConstForwardIterator& Other) const;
		const bool operator>=(const ConstForwardIterator& Other) const;

		ConstForwardIterator<Collection>& operator++();

		ConstCollectionReference operator*() const;
	private:
		CollectionPointer _Current;
	};

	template <class Collection>
	inline ConstForwardIterator<Collection>::ConstForwardIterator() noexcept
		: _Current(nullptr)
	{ }

	template<class Collection>
	inline ConstForwardIterator<Collection>::ConstForwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline ConstForwardIterator<Collection>::ConstForwardIterator(const ConstForwardIterator& Source) noexcept
		: _Current(Source._Current)
	{ }

	template <class Collection>
	inline ConstForwardIterator<Collection>::~ConstForwardIterator() noexcept
	{ }

	template <class Collection>
	const bool ConstForwardIterator<Collection>::operator==(const ConstForwardIterator& Other) const
	{
		return _Current == Other._Current;
	}

	template <class Collection>
	const bool ConstForwardIterator<Collection>::operator!=(const ConstForwardIterator& Other) const
	{
		return _Current != Other._Current;
	}

	template <class Collection>
	const bool ConstForwardIterator<Collection>::operator<(const ConstForwardIterator& Other) const
	{
		return _Current < Other._Current;
	}

	template <class Collection>
	const bool ConstForwardIterator<Collection>::operator>(const ConstForwardIterator& Other) const
	{
		return _Current > Other._Current;
	}

	template <class Collection>
	const bool ConstForwardIterator<Collection>::operator<=(const ConstForwardIterator& Other) const
	{
		return _Current <= Other._Current;
	}

	template <class Collection>
	const bool ConstForwardIterator<Collection>::operator>=(const ConstForwardIterator& Other) const
	{
		return _Current >= Other._Current;
	}

	template<class Collection>
	inline ConstForwardIterator<Collection>& ConstForwardIterator<Collection>::operator++()
	{
		_Current++;

		return *this;
	}

	template<class Collection>
	inline ConstForwardIterator<Collection>::ConstCollectionReference ConstForwardIterator<Collection>::operator*() const
	{
		return *_Current;
	}
}
#endif
