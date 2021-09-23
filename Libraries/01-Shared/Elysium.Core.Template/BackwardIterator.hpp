/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_BACKWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_BACKWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <class Collection>
	class BackwardIterator final
	{
	public:
		using CollectionPointer = typename Collection::Pointer;
		using CollectionReference = typename Collection::Reference;
	public:
		BackwardIterator() noexcept;
		BackwardIterator(CollectionPointer Current) noexcept;
		BackwardIterator(const BackwardIterator& Source) noexcept;
		BackwardIterator(BackwardIterator&& Right) noexcept = delete;
		~BackwardIterator() noexcept;

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
}
#endif
