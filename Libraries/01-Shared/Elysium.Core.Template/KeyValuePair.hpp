/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_KEYVALUEPAIR
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_KEYVALUEPAIR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASHABLE
#include "Hashable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	///
	/// </summary>
	/// <typeparam name="TKey"></typeparam>
	/// <typeparam name="TValue"></typeparam>
	template <Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	class KeyValuePair final
	{
	public:
		KeyValuePair(const TKey& Key, const TValue& Value);

		KeyValuePair(const KeyValuePair& Source);

		KeyValuePair(KeyValuePair&& Right) noexcept;

		~KeyValuePair();
	public:
		KeyValuePair<TKey, TValue>& operator=(const KeyValuePair& Source);

		KeyValuePair<TKey, TValue>& operator=(KeyValuePair&& Right) noexcept;
	public:
		const TKey& GetKey() const;

		TValue& GetValue();

		const TValue& GetValue() const;
	private:
		TKey _Key;
		TValue _Value;
	};

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(const TKey& Key, const TValue& Value)
		: _Key(Key), _Value(Value)
	{ }

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(const KeyValuePair & Source)
		: _Key(Source._Key), _Value(Source._Value)
	{ }

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(KeyValuePair&& Right) noexcept
		: _Key(), _Value()
	{
		*this = Functional::Move(Right);
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::~KeyValuePair()
	{ }

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	inline KeyValuePair<TKey, TValue>& KeyValuePair<TKey, TValue>::operator=(const KeyValuePair& Source)
	{
		if (this != &Source)
		{
			_Key = Source._Key;
			_Value = Source._Value;
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	inline KeyValuePair<TKey, TValue>& KeyValuePair<TKey, TValue>::operator=(KeyValuePair&& Right) noexcept
	{
		if (this != &Right)
		{
			_Key = Functional::Move(Right._Key);
			_Value = Functional::Move(Right._Value);
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	inline const TKey& KeyValuePair<TKey, TValue>::GetKey() const
	{
		return _Key;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	inline TValue& KeyValuePair<TKey, TValue>::GetValue()
	{
		return _Value;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue>
	inline const TValue& KeyValuePair<TKey, TValue>::GetValue() const
	{
		return _Value;
	}
}
#endif
