/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
/*
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ORDEREDMAP
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_ORDEREDMAP

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_REDBLACKTREE
#include "RedBlackTree.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_TUPLE
#include "Tuple.hpp"
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
	/// <typeparam name="KeyCompare"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	template <class TKey, class TValue, class KeyCompare = Operators::Less<TKey>, class Allocator = Memory::DefaultAllocator<Tuple<const TKey, TValue>>>
	class Map final
	{
	public:
		using KeyValuePair = Tuple<const TKey, TValue>;

		using FIterator = Iterator::ForwardIterator<Map<TKey, TValue, KeyCompare, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<Map<TKey, TValue, KeyCompare, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<Map<TKey, TValue, KeyCompare, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<Map<TKey, TValue, KeyCompare, Allocator>>;
	public:
		/// <summary>
		/// 
		/// </summary>
		Map();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Capacity"></param>
		Map(const Elysium::Core::Template::System::size Capacity);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		Map(const Map& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		Map(Map&& Right) noexcept;

		/// <summary>
		/// Destroys this instance.
		/// </summary>
		~Map();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Source"></param>
		/// <returns></returns>
		Map<TKey, TValue, KeyCompare, Allocator>& operator=(const Map& Source);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Right"></param>
		/// <returns></returns>
		Map<TKey, TValue, KeyCompare, Allocator>& operator=(Map&& Right) noexcept;
		
		/// <summary>
		/// Returns a forward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		FIterator GetBegin();

		/// <summary>
		/// Returns a const forward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		ConstIterator GetBegin() const;

		/// <summary>
		/// Returns a forward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		FIterator GetEnd();

		/// <summary>
		/// Returns a const forward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		ConstIterator GetEnd() const;

		/// <summary>
		/// Returns a backward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		ReverseIterator GetReverseBegin();

		/// <summary>
		/// Returns a const backward-iterator pointing towards the last element.
		/// </summary>
		/// <returns></returns>
		ConstReverseIterator GetReverseBegin() const;

		/// <summary>
		/// Returns a backward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		ReverseIterator GetReverseEnd();

		/// <summary>
		/// Returns a const backward-iterator pointing towards the first element.
		/// </summary>
		/// <returns></returns>
		ConstReverseIterator GetReverseEnd() const;
	private:
		inline static Allocator _Allocator = Allocator();
	private:
		Elysium::Core::Template::System::size _Capacity;
		Elysium::Core::Template::System::size _Size;
		KeyValuePair* _Data;
	};
	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::Map()
		: _Capacity(0), _Size(0), _Data(nullptr)
	{ }

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::Map(const Elysium::Core::Template::System::size Capacity)
		: _Capacity(Capacity), _Size(0), _Data(_Allocator.Allocate(_Capacity))
	{ }

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::Map(const Map& Source)
		: _Capacity(Source._Capacity), _Size(Source._Size), _Data(_Allocator.Allocate(_Capacity))
	{
		Array<KeyValuePair>::Copy(Source._Data, _Data, _Size);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::Map(Map&& Right) noexcept
		: _Capacity(0), _Size(0), _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::~Map()
	{
		_Allocator.Deallocate(_Data, _Size);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>& Map<TKey, TValue, KeyCompare, Allocator>::operator=(const Map& Source)
	{
		if (this != &Source)
		{
			if (Source._Capacity > _Capacity)
			{
				_Allocator.Deallocate(_Data, _Size);

				_Capacity = Source._Capacity;
				_Data = _Allocator.Allocate(Source._Capacity);
			}

			_Size = Source._Size;
			Array<KeyValuePair>::Copy(Source._Data, _Data, _Size);
		}
		return *this;
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>& Map<TKey, TValue, KeyCompare, Allocator>::operator=(Map&& Right) noexcept
	{
		if (this != &Right)
		{
			_Allocator.Deallocate(_Data, _Size);

			_Capacity = Functional::Move(Right._Capacity);
			_Size = Functional::Move(Right._Size);
			_Data = Functional::Move(Right._Data);

			Right._Capacity = 0;
			Right._Size = 0;
			Right._Data = nullptr;
		}
		return *this;
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::FIterator Map<TKey, TValue, KeyCompare, Allocator>::GetBegin()
	{
		return FIterator(&_Data[0]);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::ConstIterator Map<TKey, TValue, KeyCompare, Allocator>::GetBegin() const
	{
		return ConstIterator(&_Data[0]);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::FIterator Map<TKey, TValue, KeyCompare, Allocator>::GetEnd()
	{
		return FIterator(&_Data[_Size]);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::ConstIterator Map<TKey, TValue, KeyCompare, Allocator>::GetEnd() const
	{
		return ConstIterator(&_Data[_Size]);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::ReverseIterator Map<TKey, TValue, KeyCompare, Allocator>::GetReverseBegin()
	{
		return ReverseIterator(&_Data[_Size - 1]);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::ConstReverseIterator Map<TKey, TValue, KeyCompare, Allocator>::GetReverseBegin() const
	{
		return ConstReverseIterator(&_Data[_Size - 1]);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::ReverseIterator Map<TKey, TValue, KeyCompare, Allocator>::GetReverseEnd()
	{
		return ReverseIterator(&_Data[-1]);
	}

	template<class TKey, class TValue, class KeyCompare, class Allocator>
	inline Map<TKey, TValue, KeyCompare, Allocator>::ConstReverseIterator Map<TKey, TValue, KeyCompare, Allocator>::GetReverseEnd() const
	{
		return ConstReverseIterator(&_Data[-1]);
	}
}
#endif
*/