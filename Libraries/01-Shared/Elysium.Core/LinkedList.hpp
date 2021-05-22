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

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class LinkedList final
	{
	public:
		LinkedList();
		LinkedList(const List<T>& Right) = delete;
		LinkedList(List<T>&& Right) noexcept = delete;
		~LinkedList();

		LinkedList<T>& operator=(const LinkedList<T>& Source) = delete;
		LinkedList<T>& operator=(LinkedList<T>&& Right) noexcept = delete;
		/*
		const Elysium::Core::int64_t GetCount() const;
		
		const LinkedListNode<T>* GetFirst() const;

		const LinkedListNode<T>* GetLast() const;
		*/
	private:
		LinkedListNode<T>* _First;
	};

	template<typename T>
	inline LinkedList<T>::LinkedList()
		: _First(nullptr)
	{ }

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{ }
	/*
	template<typename T>
	inline const Elysium::Core::int64_t LinkedList<T>::GetCount() const
	{
		Elysium::Core::int64_t Result = 0;
		LinkedListNode<T>* Next =
		while ()
		{

		}

		return Result;
	}
	*/
}
#endif
