/*
===========================================================================
Copyright (c) waYne (CAM). All rights reserved.
===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LINKEDLISTNODE
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LINKEDLISTNODE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class LinkedList;

	template <typename T>
	class LinkedListNode final
	{
		friend class LinkedList<T>;
	public:
		LinkedListNode(const T& Value);
		LinkedListNode(const List<T>& Right) = delete;
		LinkedListNode(List<T>&& Right) noexcept = delete;
		~LinkedListNode();

		LinkedListNode<T>& operator=(const LinkedList<T>& Source) = delete;
		LinkedListNode<T>& operator=(LinkedList<T>&& Right) noexcept = delete;
	private:
		T _Value;
		LinkedListNode<T>* _Next;
		LinkedList<T>* _LinkedList;
	};

	template<typename T>
	inline LinkedListNode<T>::LinkedListNode(const T& Value)
		: _Value(Value), _Next(nullptr), _LinkedList(nullptr)
	{ }

	template<typename T>
	inline LinkedListNode<T>::~LinkedListNode()
	{ }
}
#endif
