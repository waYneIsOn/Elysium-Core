/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_UNORDEREDMAP
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_UNORDEREDMAP

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASHABLE
#include "Hashable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_OBJECT
#include "Object.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "InitializerList.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_UNORDEREDMAPFORWARDITERATOR
#include "UnorderedMapForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_NUMERICTRAITS
#include "NumericTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_LESS
#include "Less.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// @ToDo:
	/// https://bannalia.blogspot.com/2022/11/inside-boostunorderedflatmap.html
	/// </summary>
	/// <typeparam name="TKey"></typeparam>
	/// <typeparam name="TValue"></typeparam>
	/// <typeparam name="KeyCompare"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	template <Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare = Operators::Less<TKey>,
		class Allocator = Memory::DefaultAllocator<LinkedList<KeyValuePair<TKey, TValue>>>>
	class UnorderedMap final
	{
		friend class Iterator::UnorderedMapForwardIterator<UnorderedMap<TKey, TValue, KeyCompare, Allocator>>;
	public:
		using Entry = KeyValuePair<TKey, TValue>;
		using Bucket = LinkedList<Entry>;

		using BucketPointer = Bucket*;
		using BucketReference = Bucket&;
		using ConstBucketReference = const Bucket&;
		using BucketNodePointer = LinkedListNode<Entry>*;

		using FIterator = Iterator::UnorderedMapForwardIterator<UnorderedMap<TKey, TValue, KeyCompare, Allocator>>;
		//using ConstIterator = Iterator::ConstForwardIterator<HashTable<TKey, TValue, KeyCompare, Allocator>>;
		/*
		using ReverseIterator = Iterator::BackwardIterator<HashTable<TKey, TValue, KeyCompare, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<HashTable<TKey, TValue, KeyCompare, Allocator>>;
		*/
	public:
		UnorderedMap();

		UnorderedMap(const InitializerList<Entry>& List);

		UnorderedMap(const System::size Length);

		UnorderedMap(const UnorderedMap& Source);

		UnorderedMap(UnorderedMap&& Right) noexcept;

		~UnorderedMap();
	public:
		UnorderedMap<TKey, TValue, KeyCompare, Allocator>& operator=(const UnorderedMap& Source);

		UnorderedMap<TKey, TValue, KeyCompare, Allocator>& operator=(UnorderedMap&& Right) noexcept;

		TValue& operator[](const TKey& Key);

		const TValue& operator[](const TKey& Key) const;
	public:
		void Set(const TKey& Key, const TValue& Value);

		void Add(const TKey& Key, const TValue& Value);

		void Remove(const TKey& Key);

		void Remove(const TKey& Key, TValue& Value);

		void Clear();
	public:
		UnorderedMap<TKey, TValue, KeyCompare, Allocator>::FIterator GetBegin();

		UnorderedMap<TKey, TValue, KeyCompare, Allocator>::FIterator GetEnd();
		/*
		ConstIterator GetBegin() const;

		ConstIterator GetEnd() const;

		ReverseIterator GetReverseBegin();

		ConstReverseIterator GetReverseBegin() const;

		ReverseIterator GetReverseEnd();

		ConstReverseIterator GetReverseEnd() const;
		*/
	private:
		inline static Allocator _Allocator = Allocator();
		static const System::size CollisionThreshold = 10;
	private:
		System::size _Length;
		System::size _CollisionCount;
		Bucket* _Buckets;

		/// <summary>
		/// Calculates the next prime number larger or equal desired length.
		/// Prime numbers are being used to cause as little collision as possible when using modulo which happens when items get added.
		/// </summary>
		/// <param name="DesiredLength"></param>
		/// <returns></returns>
		const System::size CalculateLength(const System::size DesiredLength);

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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Bucket"></param>
		/// <returns></returns>
		UnorderedMap<TKey, TValue, KeyCompare, Allocator>::Entry* FindEntry(LinkedListNode<Entry>* CurrentNode, const TKey& Key) const;
	};

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>::UnorderedMap()
		: _Length(3), _CollisionCount(0), _Buckets(_Allocator.Allocate(_Length))
	{ }

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>::UnorderedMap(const InitializerList<Entry>& List)
		: _Length(List.size() < 3 ? 3 : CalculateLength(List.size())), _CollisionCount(0), _Buckets(_Allocator.Allocate(_Length))
	{
		for (const Entry* Iterator = List.begin(); Iterator != List.end(); ++Iterator)
		{
			Insert(Iterator->GetKey(), Iterator->GetValue(), false);
		}
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>::UnorderedMap(const Elysium::Core::Template::System::size Length)
		: _Length(CalculateLength(Length)), _CollisionCount(0), _Buckets(_Allocator.Allocate(_Length))
	{ }

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>::UnorderedMap(const UnorderedMap& Source)
		: _Length(Source._Length), _CollisionCount(Source._CollisionCount), _Buckets(_Allocator.Allocate(_Length))
	{
		Array<HashTableEntry<TKey, TValue>>::Copy(Source._Buckets, _Buckets, _Length);
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>::UnorderedMap(UnorderedMap&& Right) noexcept
		: _Length(0), _CollisionCount(0), _Buckets(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>::~UnorderedMap()
	{
		_Allocator.Deallocate(_Buckets, _Length);
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>& UnorderedMap<TKey, TValue, KeyCompare, Allocator>::operator=(const UnorderedMap& Source)
	{
		if (this != &Source)
		{	// ToDo:
			throw 1;
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>& UnorderedMap<TKey, TValue, KeyCompare, Allocator>::operator=(UnorderedMap&& Right) noexcept
	{
		if (this != &Right)
		{	// ToDo:
			throw 1;
		}
		return *this;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline TValue& UnorderedMap<TKey, TValue, KeyCompare, Allocator>::operator[](const TKey& Key)
	{
		const Elysium::Core::Template::System::size HashCode = Object::GetHashCode(Key);
		const Elysium::Core::Template::System::size TargetBucketIndex = HashCode % _Length;
		const BucketReference TargetBucket = _Buckets[TargetBucketIndex];

		LinkedListNode<Entry>* Node = TargetBucket.GetHead();
		Entry* ExistingItem = FindEntry(Node, Key);
		if (ExistingItem == nullptr)
		{
			// ToDo: throw Elysium::Core::KeyNotFoundException
			throw 1;
		}

		return ExistingItem->GetValue();
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline const TValue& UnorderedMap<TKey, TValue, KeyCompare, Allocator>::operator[](const TKey& Key) const
	{
		const Elysium::Core::Template::System::size HashCode = Object::GetHashCode(Key);
		const Elysium::Core::Template::System::size TargetBucketIndex = HashCode % _Length;
		const BucketReference TargetBucket = _Buckets[TargetBucketIndex];

		LinkedListNode<Entry>* Node = TargetBucket.GetHead();
		Entry* ExistingItem = FindEntry(Node, Key);
		if (ExistingItem == nullptr)
		{
			// ToDo: throw Elysium::Core::KeyNotFoundException
			throw 1;
		}

		return ExistingItem->GetValue();
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline void UnorderedMap<TKey, TValue, KeyCompare, Allocator>::Set(const TKey& Key, const TValue& Value)
	{
		Insert(Key, Value, false);
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline void UnorderedMap<TKey, TValue, KeyCompare, Allocator>::Add(const TKey& Key, const TValue& Value)
	{
		Insert(Key, Value, true);
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline void UnorderedMap<TKey, TValue, KeyCompare, Allocator>::Remove(const TKey& Key)
	{
		throw 1;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline void UnorderedMap<TKey, TValue, KeyCompare, Allocator>::Remove(const TKey& Key, TValue& Value)
	{
		throw 1;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline void UnorderedMap<TKey, TValue, KeyCompare, Allocator>::Clear()
	{
		for (Elysium::Core::Template::System::size i = 0; i < _Length; i++)
		{
			_Buckets[i].Clear();
		}
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>::FIterator UnorderedMap<TKey, TValue, KeyCompare, Allocator>::GetBegin()
	{
		BucketPointer FirstPopulatedBucket = nullptr;
		for (Elysium::Core::Template::System::size i = 0; i < _Length; i++)
		{
			if (_Buckets[i].GetHead() != nullptr)
			{
				FirstPopulatedBucket = &_Buckets[i];
				break;
			}
		}
		BucketNodePointer FirstPopulatedBucketHead = FirstPopulatedBucket == nullptr ? nullptr : FirstPopulatedBucket->GetHead();

		return FIterator(FirstPopulatedBucket, FirstPopulatedBucketHead);
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>::FIterator UnorderedMap<TKey, TValue, KeyCompare, Allocator>::GetEnd()
	{
		BucketPointer OutOfBoundsBucket = &_Buckets[_Length];
		BucketPointer FirstPopulatedBucket = nullptr;
		for (Elysium::Core::Template::System::size i = 0; i < _Length; i++)
		{
			if (_Buckets[i].GetHead() != nullptr)
			{
				FirstPopulatedBucket = &_Buckets[i];
				break;
			}
		}
		BucketPointer EndBucket = FirstPopulatedBucket == nullptr ? nullptr : OutOfBoundsBucket;
		BucketNodePointer EndBucketHead = EndBucket == nullptr ? nullptr : OutOfBoundsBucket->GetHead();

		return FIterator(EndBucket, EndBucketHead);
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline const Elysium::Core::Template::System::size UnorderedMap<TKey, TValue, KeyCompare, Allocator>::CalculateLength(const Elysium::Core::Template::System::size DesiredLength)
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
		static const Elysium::Core::Template::System::size LookupTableLength = 11;
		static const Elysium::Core::Template::System::size LookupTablePrimeNumbers[LookupTableLength] =
		{ 
			3, 7, 17, 37, 79, 163, 331, 673, 1361, 2729, 5471
		};
		
		for (Elysium::Core::Template::System::size i = 0; i < LookupTableLength; i++)
		{
			if (LookupTablePrimeNumbers[i] >= DesiredLength)
			{
				return LookupTablePrimeNumbers[i];
			}
		}
		
		// if no prime number has been found inside the lookup-table, we need to calculate the next prime number the hard way
		for (Elysium::Core::Template::System::size i = DesiredLength; i < Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::size>::Maximum; i++)
		{
			if (Elysium::Core::Template::Numeric::NumericTraits<Elysium::Core::Template::System::size>::IsPrimeNumber(i))
			{
				return i;
			}
		}
		
		// well...
		return DesiredLength;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline void UnorderedMap<TKey, TValue, KeyCompare, Allocator>::Insert(const TKey& Key, const TValue& Value, const bool Add)
	{
		const Elysium::Core::Template::System::size HashCode = Object::GetHashCode(Key);
		const Elysium::Core::Template::System::size TargetBucketIndex = HashCode % _Length;
		BucketReference TargetBucket = _Buckets[TargetBucketIndex];

		LinkedListNode<Entry>* Node = TargetBucket.GetHead();
		if (Node == nullptr)
		{
			Entry Item = Entry(Key, Value);
			TargetBucket.PushBack(Functional::Move(Item));
		}
		else
		{
			if (Add)
			{
				throw Elysium::Core::ArgumentException(u8"An element with the same key already exists.");
			}

			Entry* ExistingItem = FindEntry(Node, Key);
			if (ExistingItem == nullptr)
			{
				TargetBucket.PushBack(Functional::Move(Entry(Key, Value)));

				_CollisionCount++;
				if (_CollisionCount > CollisionThreshold)
				{	// ToDo: implement resize!
					//throw Elysium::Core::ArgumentException(u8"Resize is required.");
				}
			}
			else
			{
				ExistingItem->GetValue() = Value;
			}
		}
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class Allocator, class KeyCompare>
	inline void UnorderedMap<TKey, TValue, Allocator, KeyCompare>::Resize()
	{
		const Elysium::Core::Template::System::size NewLength = CalculateLength(_Length * 2);


		bool bla = false;
	}

	template<Elysium::Core::Template::Concepts::Hashable TKey, class TValue, class KeyCompare, class Allocator>
	inline UnorderedMap<TKey, TValue, KeyCompare, Allocator>::Entry* UnorderedMap<TKey, TValue, KeyCompare, Allocator>::FindEntry(LinkedListNode<Entry>* CurrentNode, const TKey& Key) const
	{
		while (CurrentNode != nullptr)
		{
			UnorderedMap<TKey, TValue, KeyCompare, Allocator>::Entry& Entry = CurrentNode->GetItem();
			if (Entry.GetKey() == Key)
			{
				return &Entry;
			}
			CurrentNode = CurrentNode->GetNext();
		}
		
		return nullptr;
	}
}
#endif
