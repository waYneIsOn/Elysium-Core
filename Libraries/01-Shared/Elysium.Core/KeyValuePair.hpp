/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_KEYVALUEPAIR
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_KEYVALUEPAIR

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

namespace Elysium::Core::Collections::Template
{
	template <class TKey, class TValue>
	class KeyValuePair final
	{
	public:
		KeyValuePair(TKey Key, TValue Value);
		KeyValuePair(const KeyValuePair<TKey, TValue>& Source);
		KeyValuePair(KeyValuePair<TKey, TValue>&& Right);
		~KeyValuePair();

		KeyValuePair<TKey, TValue>& operator=(const KeyValuePair<TKey, TValue>& Source);
		KeyValuePair<TKey, TValue>& operator=(KeyValuePair<TKey, TValue>&& Right) noexcept;

		const TKey GetKey() const;
		TValue GetValue() const;
	private:
		TKey _Key;
		TValue _Value;
	};

	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(TKey Key, TValue Value)
		: _Key(Key), _Value(Value)
	{ }
	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(const KeyValuePair<TKey, TValue>& Source)
		: _Key(Source._Key), _Value(Source._Value)
	{ }
	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(KeyValuePair<TKey, TValue>&& Right)
		: _Key(TKey()), _Value(TValue())
	{
		*this = std::move(Right);
	}
	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::~KeyValuePair()
	{ }

	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>& KeyValuePair<TKey, TValue>::operator=(const KeyValuePair<TKey, TValue>& Source)
	{
		if (this != &Source)
		{
			_Key = Source._Key;
			_Value = Source._Value;
		}
		return *this;
	}
	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>& KeyValuePair<TKey, TValue>::operator=(KeyValuePair<TKey, TValue>&& Right) noexcept
	{
		if (this != &Right)
		{
			_Key = std::move(Right._Key);
			_Value = std::move(Right._Value);
		}
		return *this;
	}

	template<class TKey, class TValue>
	inline const TKey KeyValuePair<TKey, TValue>::GetKey() const
	{
		return _Key;
	}
	template<class TKey, class TValue>
	inline TValue KeyValuePair<TKey, TValue>::GetValue() const
	{
		return _Value;
	}
}
#endif
