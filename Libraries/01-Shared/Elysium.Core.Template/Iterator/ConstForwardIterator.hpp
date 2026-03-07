/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTFORWARDITERATOR
#define ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTFORWARDITERATOR

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Iterator
{
	template <class Collection>
	class ConstForwardIterator final
	{
	public:
		using CollectionPointer = typename Collection::IteratorPointer;
		using ConstCollectionReference = typename Collection::ConstIteratorReference;
	public:
		constexpr ConstForwardIterator() = delete;

		constexpr ConstForwardIterator(CollectionPointer Current) noexcept;

		constexpr ConstForwardIterator(const ConstForwardIterator& Source) = delete;

		constexpr ConstForwardIterator(ConstForwardIterator&& Right) noexcept = delete;

		constexpr ~ConstForwardIterator() noexcept;
	public:
		constexpr ConstForwardIterator<Collection>& operator=(const ConstForwardIterator& Source) noexcept = delete;

		constexpr ConstForwardIterator<Collection>& operator=(ConstForwardIterator&& Right) noexcept = delete;
	public:
		constexpr const bool operator!=(const ConstForwardIterator& Other) const;

		constexpr ConstForwardIterator<Collection>& operator++();

		constexpr ConstCollectionReference operator*() const;
	private:
		CollectionPointer _Current;
	};

	template<class Collection>
	inline constexpr ConstForwardIterator<Collection>::ConstForwardIterator(CollectionPointer Current) noexcept
		: _Current(Current)
	{ }

	template <class Collection>
	inline constexpr ConstForwardIterator<Collection>::~ConstForwardIterator() noexcept
	{ }

	template <class Collection>
	inline constexpr const bool ConstForwardIterator<Collection>::operator!=(const ConstForwardIterator& Other) const
	{
		return _Current <= Other._Current;
	}

	template<class Collection>
	inline constexpr ConstForwardIterator<Collection>& ConstForwardIterator<Collection>::operator++()
	{
		_Current++;

		return *this;
	}

	template<class Collection>
	inline constexpr typename ConstForwardIterator<Collection>::ConstCollectionReference ConstForwardIterator<Collection>::operator*() const
	{
		return *_Current;
	}
}
#endif
