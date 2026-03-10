/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLISTNODE
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLISTNODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <Concepts::NonConstant T>
	class LinkedList;

	template <Concepts::NonConstant T>
	class LinkedListNode final
	{
		friend class LinkedList<T>;
	public:
		using ConstValue = const T;
		using Reference = T&;
		using ConstReference = const T&;
		using RValueReference = T&&;

		using NodePointer = LinkedListNode<T>*;
		using ConstNodePointer = const LinkedListNode<T>*;
	private:
		LinkedListNode(ConstReference Item, NodePointer Next);

		LinkedListNode(RValueReference Item, NodePointer Next) noexcept;
	public:
		LinkedListNode(const LinkedListNode& Source) = delete;

		LinkedListNode(LinkedListNode&& Right) noexcept = delete;

		~LinkedListNode();
	public:
		LinkedListNode<T>& operator=(const LinkedListNode& Source) = delete;

		LinkedListNode<T>& operator=(LinkedListNode&& Right) noexcept = delete;
	public:
		LinkedListNode<T>::Reference GetItem() noexcept;

		LinkedListNode<T>::ConstReference GetItem() const noexcept;

		LinkedListNode<T>::NodePointer GetNext() noexcept;

		LinkedListNode<T>::ConstNodePointer GetNext() const noexcept;
	private:
		T _Item;
		NodePointer _Next;
	};

	template<Concepts::NonConstant T>
	inline LinkedListNode<T>::LinkedListNode(ConstReference Item, NodePointer Next)
		: _Item(Item), _Next(Next)
	{ }

	template<Concepts::NonConstant T>
	inline LinkedListNode<T>::LinkedListNode(RValueReference Item, NodePointer Next) noexcept
		: _Item(Functional::Move(Item)), _Next(Next)
	{ }

	template<Concepts::NonConstant T>
	inline LinkedListNode<T>::~LinkedListNode()
	{
		if (_Next != nullptr)
		{
			delete _Next;
			_Next = nullptr;
		}
	}

	template<Concepts::NonConstant T>
	inline LinkedListNode<T>::Reference LinkedListNode<T>::GetItem() noexcept
	{
		return _Item;
	}

	template<Concepts::NonConstant T>
	inline LinkedListNode<T>::ConstReference LinkedListNode<T>::GetItem() const noexcept
	{
		return _Item;
	}

	template<Concepts::NonConstant T>
	inline LinkedListNode<T>::NodePointer LinkedListNode<T>::GetNext() noexcept
	{
		return _Next;
	}

	template<Concepts::NonConstant T>
	inline LinkedListNode<T>::ConstNodePointer LinkedListNode<T>::GetNext() const noexcept
	{
		return _Next;
	}
}
#endif
