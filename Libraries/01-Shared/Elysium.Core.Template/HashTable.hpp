/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_HASHTABLE
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_HASHTABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_KEYVALUEPAIR
#include "KeyValuePair.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLIST
#include "LinkedList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_BACKWARDITERATOR
#include "BackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTBACKWARDITERATOR
#include "ConstBackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTFORWARDITERATOR
#include "ConstForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_FORWARDITERATOR
#include "ForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICLIMITS
#include "NumericLimits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_LESS
#include "Less.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TKey"></typeparam>
	/// <typeparam name="TValue"></typeparam>
	template <class TKey, class TValue>
	struct HashTableEntry final
	{
		Elysium::Core::size HashCode = 0;
		TKey Key;
		TValue Value;
	};

	template <class TKey, class TValue, class KeyCompare = Operators::Less<TKey>, 
		class Allocator = Memory::DefaultAllocator<LinkedList<HashTableEntry<TKey, TValue>>>>
	class HashTable final
	{
	public:
		using Entry = HashTableEntry<TKey, TValue>;
		using Bucket = LinkedList<Entry>;
		/*
		using FIterator = Iterator::ForwardIterator<HashTable<TKey, TValue, KeyCompare, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<HashTable<TKey, TValue, KeyCompare, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<HashTable<TKey, TValue, KeyCompare, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<HashTable<TKey, TValue, KeyCompare, Allocator>>;
		*/
	public:
		HashTable();

		HashTable(const Elysium::Core::size Length);

		HashTable(const HashTable& Source);

		HashTable(HashTable&& Right) noexcept;

		~HashTable();
	public:
		HashTable<TKey, TValue, KeyCompare, Allocator>& operator=(const HashTable& Source);

		HashTable<TKey, TValue, KeyCompare, Allocator>& operator=(HashTable&& Right) noexcept;

		//ConstReference operator[](const Elysium::Core::size Index) const;
	public:
		/*
		FIterator GetBegin();

		ConstIterator GetBegin() const;

		FIterator GetEnd();

		ConstIterator GetEnd() const;

		ReverseIterator GetReverseBegin();

		ConstReverseIterator GetReverseBegin() const;

		ReverseIterator GetReverseEnd();

		ConstReverseIterator GetReverseEnd() const;
		*/
	public:
		void Add(const TKey& Key, const TValue& Value);
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		Elysium::Core::size _Length;
		Bucket* _Buckets;

		/// <summary>
		/// Calculates the next prime number larger or equal desired length.
		/// Prime numbers are being used to cause as little collision as possible when using modulo which happens when items get added.
		/// </summary>
		/// <param name="DesiredLength"></param>
		/// <returns></returns>
		const Elysium::Core::size CalculateLength(const Elysium::Core::size DesiredLength);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Key"></param>
		/// <param name="Value"></param>
		/// <param name="Add"></param>
		void Insert(const TKey& Key, const TValue& Value, const bool Add);

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="TKey"></typeparam>
		/// <typeparam name="TValue"></typeparam>
		/// <typeparam name="KeyCompare"></typeparam>
		/// <typeparam name="Allocator"></typeparam>
		void Resize();
	};

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline HashTable<TKey, TValue, KeyCompare, Allocator>::HashTable()
		: _Length(3), _Buckets(_Allocator.Allocate(_Length))
	{ }

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline HashTable<TKey, TValue, KeyCompare, Allocator>::HashTable(const Elysium::Core::size Length)
		: _Length(CalculateLength(Length)), _Buckets(_Allocator.Allocate(_Length))
	{ }

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline HashTable<TKey, TValue, KeyCompare, Allocator>::HashTable(const HashTable& Source)
		: _Length(Source._Length), _Buckets(_Allocator.Allocate(_Length))
	{
		Array<HashTableEntry<TKey, TValue>>::Copy(Source._Buckets, _Buckets, _Length);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline HashTable<TKey, TValue, KeyCompare, Allocator>::HashTable(HashTable&& Right) noexcept
		: _Length(0), _Buckets(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline HashTable<TKey, TValue, KeyCompare, Allocator>::~HashTable()
	{
		_Allocator.Deallocate(_Buckets, _Length);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline HashTable<TKey, TValue, KeyCompare, Allocator>& HashTable<TKey, TValue, KeyCompare, Allocator>::operator=(const HashTable& Source)
	{
		if (this != &Source)
		{	// ToDo:
			throw 1;
		}
		return *this;
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline HashTable<TKey, TValue, KeyCompare, Allocator>& HashTable<TKey, TValue, KeyCompare, Allocator>::operator=(HashTable&& Right) noexcept
	{
		if (this != &Right)
		{	// ToDo:
			throw 1;
		}
		return *this;
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline void HashTable<TKey, TValue, KeyCompare, Allocator>::Add(const TKey& Key, const TValue& Value)
	{
		Insert(Key, Value, true);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline const Elysium::Core::size HashTable<TKey, TValue, KeyCompare, Allocator>::CalculateLength(const Elysium::Core::size DesiredLength)
	{
		// prime number calculation can be expensive so use a lookup-table
		// certain prime numbers are exempt because resizing uses a growth factor of two which would skip certain prime numbers anways.
		// here's a few examples:
		//	current length is 3. times two is 6 -> no need for 5 -> result: 7
		//	current length is 7. times two is 14 -> no need for 11 nor 13 -> result: 17
		//	current length is 17. times two is 34 -> no need for 19, 23, 29 nor 31 -> result: 37
		//	current length is 37. times two is 74 -> no need for 41, 43, 47, 53, 59, 61, 67, 71 nor 73 -> result: 79
		//	current length is 79. times two is 158 -> no need for 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 149, 151 nor 157 -> result: 163
		//		and so on...
		// also 2 is exempt as .NET does not appear to be using it.
		// ToDo: I still might want to add a few more prime numbers into the lookup-table as .NET dictionaries do not appear to grow that quickly!
		// ToDo: what is the maximum prime number in .NET's lookup-table? (last one below int32 maximum?)
		static const Elysium::Core::size LookupTableLength = 11;
		static const Elysium::Core::size LookupTablePrimeNumbers[LookupTableLength] =
		{ 
			3, 7, 17, 37, 79, 163, 331, 673, 1361, 2729, 5471
		};
		
		for (Elysium::Core::size i = 0; i < LookupTableLength; i++)
		{
			if (LookupTablePrimeNumbers[i] >= DesiredLength)
			{
				return LookupTablePrimeNumbers[i];
			}
		}
		
		// if no prime number has been found inside the lookup-table, we need to calculate the next prime number the hard way
		for (Elysium::Core::size i = DesiredLength; i < Elysium::Core::Template::Numeric::NumericLimits<Elysium::Core::size>::Maximum; i++)
		{
			if (Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::size>::IsPrimeNumber(i))
			{
				return i;
			}
		}
		
		// well...
		return DesiredLength;
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline void HashTable<TKey, TValue, KeyCompare, Allocator>::Insert(const TKey& Key, const TValue& Value, const bool Add)
	{
		Elysium::Core::size HashCode = Key.GetHashCode();
		Elysium::Core::size TargetBucketIndex = HashCode % _Length;
		Bucket& TargetBucket = _Buckets[TargetBucketIndex];

		LinkedListNode<Entry>* Node = TargetBucket.GetHead();
		if (Add && Node != nullptr)
		{
			throw Elysium::Core::ArgumentException(u8"An element with the same key already exists.");
		}

		Entry Item = Entry();
		Item.HashCode = HashCode;
		Item.Key = Key;
		Item.Value = Value;

		TargetBucket.PushBack(Functional::Move(Item));
	}

	template<class TKey, class TValue, class Allocator, class KeyCompare>
	inline void HashTable<TKey, TValue, Allocator, KeyCompare>::Resize()
	{
		const Elysium::Core::size NewLength = CalculateLength(_Length * 2);


		bool bla = false;
	}
}
#endif
