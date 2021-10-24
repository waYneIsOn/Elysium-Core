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
	template <class TKey, class TValue>
	class KeyValuePair final
	{
	public:
		/// <summary>
		///
		/// </summary>
		KeyValuePair(TKey& Key, TValue& Value);

		/// <summary>
		///
		/// </summary>
		/// <param name="Source"></param>
		KeyValuePair(const KeyValuePair& Source);

		/// <summary>
		///
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		KeyValuePair(KeyValuePair&& Right) noexcept;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		~KeyValuePair();

		/// <summary>
		///
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		KeyValuePair<TKey, TValue>& operator=(const KeyValuePair& Source);

		/// <summary>
		///
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		KeyValuePair<TKey, TValue>& operator=(KeyValuePair&& Right) noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const TKey& GetKey() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const TValue& GetValue() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		TValue& GetValue();
	private:
		TKey& _Key;
		TValue& _Value;
	};

	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(TKey& Key, TValue& Value)
		: _Key(Key), _Value(Value)
	{ }

	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(const KeyValuePair & Source)
		: _Key(Source._Key), _Value(Source._Value)
	{ }

	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::KeyValuePair(KeyValuePair&& Right) noexcept
		: _Key(), _Value()
	{
		*this = Functional::Move(Right);
	}

	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>::~KeyValuePair()
	{ }

	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>& KeyValuePair<TKey, TValue>::operator=(const KeyValuePair& Source)
	{
		if (this != &Source)
		{
			_Key = Source._Key;
			_Value = Source._Value;
		}
		return *this;
	}

	template<class TKey, class TValue>
	inline KeyValuePair<TKey, TValue>& KeyValuePair<TKey, TValue>::operator=(KeyValuePair&& Right) noexcept
	{
		if (this != &Right)
		{
			_Key = Functional::Move(Right._Key);
			_Value = Functional::Move(Right._Value);
		}
		return *this;
	}

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

	template<class TKey, class TValue>
	inline TValue& KeyValuePair<TKey, TValue>::GetValue()
	{
		return _Value;
	}
}
#endif
