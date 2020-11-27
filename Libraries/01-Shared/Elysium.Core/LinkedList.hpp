/*
===========================================================================
Copyright (C) 2017 waYne (CAM)
===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LINKEDLIST
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LINKEDLIST

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class LinkedList final
	{
	public:
		LinkedList(const T& Value);
		LinkedList(const List<T>& Right) = delete;
		LinkedList(List<T>&& Right) noexcept = delete;
		~LinkedList();

		LinkedList<T>& operator=(const LinkedList<T>& Source) = delete;
		LinkedList<T>& operator=(LinkedList<T>&& Right) noexcept = delete;

		const T& GetValue() const;
		//const LinkedList<T>* GetNext() const;
	private:
		T _Value;
		LinkedList* _Next;
	};

	template<typename T>
	inline LinkedList<T>::LinkedList(const T & Value)
		: _Value(Value), _Next(nullptr)
	{ }

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{ }

	template<typename T>
	inline const T & LinkedList<T>::GetValue() const
	{
		return _Value;
	}
}
#endif
