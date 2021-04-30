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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "Array.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <class TKey, class TValue>
	class Dictionary
	{
	private:
		struct Entry
		{
			Elysium::Core::int32_t HashCode;
			Elysium::Core::int32_t Next;
			TKey& Key;
			TValue& Value;
		};
	public:
		Dictionary();
		Dictionary(const Dictionary<TKey, TValue>& Source) = delete;
		Dictionary(Dictionary<TKey, TValue>&& Right) noexcept = delete;
		~Dictionary();

		Dictionary<TKey, TValue>& operator=(const Dictionary<TKey, TValue>& Source) = delete;
		Dictionary<TKey, TValue>& operator=(Dictionary<TKey, TValue>&& Right) noexcept = delete;
	private:
		//Elysium::Core::Collections::Template::Array<Elysium::Core::int32_t> _Buckets;
		//Elysium::Core::Collections::Template::Array<Elysium::Core::Collections::Template::Dictionary::Entry> _Entries;
	};

	template<class TKey, class TValue>
	inline Dictionary<TKey, TValue>::Dictionary()
	{ }
	template<class TKey, class TValue>
	inline Dictionary<TKey, TValue>::~Dictionary()
	{ }
}
#endif
