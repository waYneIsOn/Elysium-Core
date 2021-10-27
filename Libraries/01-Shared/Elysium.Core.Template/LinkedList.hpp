/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLIST
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLIST

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLISTNODE
#include "LinkedListNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTLINKEDLISTFORWARDITERATOR
#include "ConstLinkedListForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_HASHTABLEFORWARDITERATOR
#include "HashTableForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_LINKEDLISTFORWARDITERATOR
#include "LinkedListForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	template <Concepts::NonConstant T>
	class LinkedList final
	{
		friend class Iterator::LinkedListForwardIterator<LinkedList<T>>;
		friend class Iterator::HashTableForwardIterator<LinkedList<T>>;
	public:
		using ConstReference = const T&;
		using RValueReference = T&&;

		using NodePointer = LinkedListNode<T>*;
		using ConstNodePointer = const LinkedListNode<T>*;
		using NodeReference = LinkedListNode<T>&;

		using IteratorPointer = LinkedListNode<T>*;
		using IteratorReference = LinkedListNode<T>&;
		using ConstIteratorReference = const LinkedListNode<T>&;

		using FIterator = Iterator::LinkedListForwardIterator<LinkedList<T>>;
		using ConstIterator = Iterator::ConstLinkedListForwardIterator<LinkedList<T>>;
	public:
		LinkedList();

		LinkedList(const LinkedList& Source) = delete;

		LinkedList(LinkedList&& Right) noexcept = delete;

		~LinkedList();
	public:
		LinkedList<T>& operator=(const LinkedList& Source) = delete;

		LinkedList<T>& operator=(LinkedList&& Right) noexcept = delete;
	public:
		LinkedList<T>::FIterator GetBegin();

		LinkedList<T>::ConstIterator GetBegin() const;

		LinkedList<T>::FIterator GetEnd();

		LinkedList<T>::ConstIterator GetEnd() const;
	public:
		LinkedList<T>::NodePointer GetHead() noexcept;

		LinkedList<T>::ConstNodePointer GetHead() const noexcept;

		LinkedList<T>::NodePointer GetTail() noexcept;

		LinkedList<T>::ConstNodePointer GetTail() const noexcept;
	public:
		/// <summary>
		/// Inserts an item at the start of the list.
		/// </summary>
		/// <param name="Item"></param>
		void PushFront(ConstReference Item);

		/// <summary>
		/// Moves an item to the start of the list.
		/// </summary>
		/// <param name="Item"></param>
		void PushFront(RValueReference Item);

		/// <summary>
		/// Inserts an item behind given node.
		/// </summary>
		/// <param name="Item"></param>
		/// <param name="PreviousNode"></param>
		void PushAfter(ConstReference Item, NodeReference PreviousNode);

		/// <summary>
		/// Moves an item behind given nove.
		/// </summary>
		/// <param name="Item"></param>
		/// <param name="PreviousNode"></param>
		void PushAfter(RValueReference Item, NodeReference PreviousNode);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Item"></param>
		void PushBack(ConstReference Item);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Item"></param>
		void PushBack(RValueReference Item);

		/// <summary>
		/// 
		/// </summary>
		void RemoveHead();

		/// <summary>
		/// Clears the linked-list deleting all items.
		/// </summary>
		void Clear();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="Item"></param>
		/// <returns></returns>
		constexpr const bool Contains(ConstReference Item) const;
	private:
		NodePointer _Head;
		NodePointer _Tail;
	};

	template<Concepts::NonConstant T>
	inline LinkedList<T>::LinkedList()
		: _Head(nullptr), _Tail(nullptr)
	{ }

	template<Concepts::NonConstant T>
	inline LinkedList<T>::~LinkedList()
	{
		Clear();
	}

	template<Concepts::NonConstant T>
	inline LinkedList<T>::FIterator LinkedList<T>::GetBegin()
	{
		return LinkedList<T>::FIterator(_Head);
	}

	template<Concepts::NonConstant T>
	inline LinkedList<T>::ConstIterator LinkedList<T>::GetBegin() const
	{
		return LinkedList<T>::ConstIterator(_Head);
	}

	template<Concepts::NonConstant T>
	inline LinkedList<T>::FIterator LinkedList<T>::GetEnd()
	{
		return LinkedList<T>::FIterator(_Tail);
	}

	template<Concepts::NonConstant T>
	inline LinkedList<T>::ConstIterator LinkedList<T>::GetEnd() const
	{
		return LinkedList<T>::ConstIterator(_Tail);
	}

	template<Concepts::NonConstant T>
	inline LinkedList<T>::NodePointer LinkedList<T>::GetHead() noexcept
	{
		return _Head;
	}

	template<Concepts::NonConstant T>
	inline LinkedList<T>::ConstNodePointer LinkedList<T>::GetHead() const noexcept
	{
		return _Head;
	}

	template<Concepts::NonConstant T>
	inline LinkedList<T>::NodePointer LinkedList<T>::GetTail() noexcept
	{
		return _Tail;
	}

	template<Concepts::NonConstant T>
	inline LinkedList<T>::ConstNodePointer LinkedList<T>::GetTail() const noexcept
	{
		return _Tail;
	}

	template<Concepts::NonConstant T>
	inline void LinkedList<T>::PushFront(ConstReference Item)
	{
		_Head = new LinkedListNode<T>(Item, _Head);
		if (_Tail == nullptr)
		{
			_Tail = _Head;
		}
	}

	template<Concepts::NonConstant T>
	inline void LinkedList<T>::PushFront(RValueReference Item)
	{
		_Head = new LinkedListNode<T>(Functional::Move(Item), _Head);
		if (_Tail == nullptr)
		{
			_Tail = _Head;
		}
	}

	template<Concepts::NonConstant T>
	inline void LinkedList<T>::PushAfter(ConstReference Item, NodeReference PreviousNode)
	{
		NodePointer ItemNode = new LinkedListNode<T>(Item, PreviousNode._Next);
		PreviousNode._Next = ItemNode;
		if (&PreviousNode == _Tail)
		{
			_Tail = ItemNode;
		}
	}

	template<Concepts::NonConstant T>
	inline void LinkedList<T>::PushAfter(RValueReference Item, NodeReference PreviousNode)
	{
		NodePointer ItemNode = new LinkedListNode<T>(Functional::Move(Item), PreviousNode._Next);
		PreviousNode._Next = ItemNode;
		if (&PreviousNode == _Tail)
		{
			_Tail = ItemNode;
		}
	}

	template<Concepts::NonConstant T>
	inline void LinkedList<T>::PushBack(ConstReference Item)
	{
		NodePointer ItemNode = new LinkedListNode<T>(Functional::Move(Item), nullptr);
		if (_Head == nullptr)
		{	// first item
			_Head = ItemNode;
			_Tail = ItemNode;
		}
		else
		{
			_Tail->_Next = ItemNode;
			_Tail = ItemNode;
		}
	}

	template<Concepts::NonConstant T>
	inline void LinkedList<T>::PushBack(RValueReference Item)
	{
		NodePointer ItemNode = new LinkedListNode<T>(Functional::Move(Item), nullptr);
		if (_Head == nullptr)
		{	// first item
			_Head = ItemNode;
			_Tail = ItemNode;
		}
		else
		{
			_Tail->_Next = ItemNode;
			_Tail = ItemNode;
		}
	}

	template<Concepts::NonConstant T>
	inline void LinkedList<T>::RemoveHead()
	{
		if (_Head == nullptr)
		{
			return;
		}

		NodePointer Head = _Head;
		if (_Head->_Next == nullptr)
		{	// _Head equals _Tail as there is only one item contained within this linked-list
			_Tail = nullptr;
		}
		else
		{
			_Head = _Head->_Next;
		}

		Head->_Next = nullptr;
		delete Head;
	}

	template<Concepts::NonConstant T>
	inline void LinkedList<T>::Clear()
	{
		if (_Head != nullptr)
		{
			delete _Head;
			_Head = nullptr;
		}

		_Tail = nullptr;
	}

	template<Concepts::NonConstant T>
	inline constexpr const bool LinkedList<T>::Contains(ConstReference Item) const
	{
		NodePointer CurrentNode = _Head;
		while (CurrentNode != nullptr)
		{
			if (CurrentNode->_Item == Item)
			{
				return true;
			}
			CurrentNode = CurrentNode->_Next;
		}

		return false;
	}
}
#endif
