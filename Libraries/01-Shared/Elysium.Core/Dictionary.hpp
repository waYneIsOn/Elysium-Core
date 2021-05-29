/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_DICTIONARY
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_DICTIONARY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <class TKey, class TValue>
	class Dictionary final
	{
	/*
	public:
		class KeyCollection final
		{ };

		class ValueCollection final
		{ };
	*/
	private:
		struct Entry final
		{
			Elysium::Core::int32_t HashCode = -1;
			Elysium::Core::int32_t Next = -1;
			TKey Key;
			TValue Value;
		};
	public:
		Dictionary();
		Dictionary(const Elysium::Core::uint64_t Capacity);
		Dictionary(const Dictionary<TKey, TValue>& Source) = delete;
		Dictionary(Dictionary<TKey, TValue>&& Right) noexcept = delete;
		~Dictionary();

		Dictionary<TKey, TValue>& operator=(const Dictionary<TKey, TValue>& Source) = delete;
		Dictionary<TKey, TValue>& operator=(Dictionary<TKey, TValue>&& Right) noexcept = delete;

		TValue& operator[](const TKey Index);
		//const TValue& operator[](const TKey Index) const;

		//const Elysium::Core::int32_t GetCount() const;

		void Add(const TKey Key, const TValue Value);
	private:
		Elysium::Core::uint64_t _Capacity;
		Elysium::Core::int32_t* _Buckets;
		Elysium::Core::Collections::Template::Dictionary<TKey, TValue>::Entry* _Entries;

		//Initialize(const Elysium::core::uint32_t RequiredMinimumCapacity);

		void Insert(const TKey Key, const TValue Value, const bool Add);

		void Resize(const size_t DesiredMinimumSize);
	};

	template<class TKey, class TValue>
	inline Dictionary<TKey, TValue>::Dictionary()
		: Dictionary<TKey, TValue>::Dictionary(0_ui64)
	{ }
	template<class TKey, class TValue>
	inline Dictionary<TKey, TValue>::Dictionary(const Elysium::Core::uint64_t Capacity)
		: _Capacity(Capacity),
		_Buckets(_Capacity == 0 ? nullptr : new Elysium::Core::int32_t[_Capacity]),
		_Entries(_Capacity == 0 ? nullptr : new Elysium::Core::Collections::Template::Dictionary<TKey, TValue>::Entry[_Capacity])
	{ }
	template<class TKey, class TValue>
	inline Dictionary<TKey, TValue>::~Dictionary()
	{
		if (_Buckets != nullptr)
		{
			delete[] _Buckets;
			delete[] _Entries;
		}
	}

	template<class TKey, class TValue>
	inline TValue& Dictionary<TKey, TValue>::operator[](const TKey Index)
	{
		throw 1;
	}

	template<class TKey, class TValue>
	inline void Dictionary<TKey, TValue>::Add(const TKey Key, const TValue Value)
	{
		Insert(Key, Value, true);
	}

	template<class TKey, class TValue>
	inline void Dictionary<TKey, TValue>::Insert(const TKey Key, const TValue Value, const bool Add)
	{
	}

	template<class TKey, class TValue>
	inline void Dictionary<TKey, TValue>::Resize(const size_t DesiredMinimumSize)
	{
	}
}
#endif
