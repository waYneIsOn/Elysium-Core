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

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS
#include "../Elysium.Core.Template/TypeTraits.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class LinkedList;

	template <typename T>
	class LinkedListNode final
	{
		using ParameterType = typename Elysium::Core::Template::Conditional<Elysium::Core::Template::IsFundamental<T>::Value || Elysium::Core::Template::IsPointer<T>::Value, T, T&>::Type;
		friend class LinkedList<T>;
	public:
		LinkedListNode(const ParameterType Value);
		LinkedListNode(const LinkedListNode<T>& Right) = delete;
		LinkedListNode(LinkedListNode<T>&& Right) noexcept = delete;
		~LinkedListNode();

		LinkedListNode<T>& operator=(const LinkedList<T>& Source) = delete;
		LinkedListNode<T>& operator=(LinkedList<T>&& Right) noexcept = delete;

		const T GetValue() const;
	private:
		const ParameterType _Value;
		LinkedListNode<T>* _Next;
	};

	template<typename T>
	inline LinkedListNode<T>::LinkedListNode(const ParameterType Value)
		: _Value(Value), _Next(nullptr)
	{ }

	template<typename T>
	inline LinkedListNode<T>::~LinkedListNode()
	{ }

	template<typename T>
	inline const T LinkedListNode<T>::GetValue() const
	{
		return _Value;
	}
}
#endif
