/*
===========================================================================
Copyright (c) waYne (CAM). All rights reserved.
===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LINKEDLIST
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LINKEDLIST

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LINKEDLISTNODE
#include "LinkedListNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS
#include "../Elysium.Core.Template/TypeTraits.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class LinkedList final
	{
		using ParameterType = typename Elysium::Core::Template::Conditional<Elysium::Core::Template::IsFundamental<T>::Value || Elysium::Core::Template::IsPointer<T>::Value, T, T&>::Type;
	public:
		LinkedList();
		LinkedList(const List<T>& Right) = delete;
		LinkedList(List<T>&& Right) noexcept = delete;
		~LinkedList();

		LinkedList<T>& operator=(const LinkedList<T>& Source) = delete;
		LinkedList<T>& operator=(LinkedList<T>&& Right) noexcept = delete;
		
		const Elysium::Core::uint64_t GetCount() const;
		
		const LinkedListNode<T>* GetFirst() const;

		const LinkedListNode<T>* GetLast() const;
		
		//void AddAfter(const T Value);
		//void AddBefore(const T Value);
		//void AddFirst(const T Value);
		
		void AddLast(const ParameterType Value);

		void Clear();

		//const bool Contains(const LinkedListNode<T>* Value) const;
		//const bool Contains(const ParameterType Value) const;

		const LinkedListNode<T>* FindLast() const;

		//void Remove(const LinkedListNode<T>* Value);
		//void Remove(const ParameterType Value);

		void RemoveFirst();

		//void RemoveLast();
	private:
		LinkedListNode<T>* _First;
		LinkedListNode<T>* _Last;

		//LinkedListNode<T>* FindSecondToLast();
	};

	template<typename T>
	inline LinkedList<T>::LinkedList()
		: _First(nullptr), _Last(nullptr)
	{ }

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{
		Clear();
	}
	
	template<typename T>
	inline const Elysium::Core::uint64_t LinkedList<T>::GetCount() const
	{
		Elysium::Core::uint64_t Result = 0;
		LinkedListNode<T>* Current = _First;
		while (Current != nullptr)
		{
			Result++;
			Current = Current->_Next;
		};
		
		return Result;
	}

	template<typename T>
	inline const LinkedListNode<T>* LinkedList<T>::GetFirst() const
	{
		return _First;
	}

	template<typename T>
	inline const LinkedListNode<T>* LinkedList<T>::GetLast() const
	{
		return _Last;
	}

	template<typename T>
	inline void LinkedList<T>::AddLast(const ParameterType Value)
	{
		LinkedListNode<T>* New = new LinkedListNode<T>(Value);
		if (_Last == nullptr)
		{
			_First = New;
		}
		else
		{
			_Last->_Next = New;
		}
		_Last = New;
	}

	template<typename T>
	inline void LinkedList<T>::Clear()
	{
		LinkedListNode<T>* Previous = _First;
		LinkedListNode<T>* Current = _First;
		while (Previous != nullptr)
		{
			Current = Current->_Next;

			delete Previous;
			Previous = Current;
		};

		_First = nullptr;
		_Last = nullptr;
	}

	template<typename T>
	inline const LinkedListNode<T>* LinkedList<T>::FindLast() const
	{
		LinkedListNode<T>* Current = _First;
		while (Current != nullptr)
		{
			if (Current->_Next == nullptr)
			{
				break;
			}
			Current = Current->_Next;
		};

		return Current;
	}

	template<typename T>
	inline void LinkedList<T>::RemoveFirst()
	{
		if (_First == nullptr)
		{
			return;
		}

		LinkedListNode<T>* Next = _First->_Next;
		delete _First;
		_First = Next;
	}
}
#endif
