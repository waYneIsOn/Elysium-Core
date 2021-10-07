/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_KEYVALUEPAIR
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_KEYVALUEPAIR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <class TKey, class TValue>
	class KeyValuePair final
	{
	public:
		KeyValuePair(const TKey& Key, const TValue& Value);
		KeyValuePair(const KeyValuePair<TKey, TValue>& Source) = delete;
		KeyValuePair(KeyValuePair<TKey, TValue>&& Right) noexcept = delete;
		~KeyValuePair();

		KeyValuePair<TKey, TValue>& operator=(const KeyValuePair<TKey, TValue>& Source) = delete;
		KeyValuePair<TKey, TValue>& operator=(KeyValuePair<TKey, TValue>&& Right) noexcept = delete;

		const TKey& GetKey() const;
		const TValue& GetValue() const;
	private:
		const TKey& _Key;
		const TValue& _Value;
	};

	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(const TKey& Key, const TValue& Value)
		: _Key(Key), _Value(Value)
	{ }
	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::~KeyValuePair()
	{ }

	template<class TKey, class TValue>
	inline const TKey& KeyValuePair<TKey, TValue>::GetKey() const
	{
		return _Key;
	}
	template<class TKey, class TValue>
	inline const TValue& KeyValuePair<TKey, TValue>::GetValue() const
	{
		return _Value;
	}
}
#endif
