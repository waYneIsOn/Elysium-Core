/*
===========================================================================
Copyright (c) waYne (CAM). All rights reserved.
===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "ArgumentOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#include "OutOfMemoryException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "../Elysium.Core.Template/InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REVERSE
#include "../Elysium.Core.Template/Reverse.hpp"
#endif

#ifndef _INC_STDIO
#include <cstring>	// memcpy
#endif

constexpr const Elysium::Core::size LIST_MAX = static_cast<Elysium::Core::size>(-1);

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class Array;

	template <typename T>
	class List final
	{
		friend class Array<T>;
	public:
		List();
		List(const Elysium::Core::size Capacity);
		List(const Elysium::Core::Template::Container::InitializerList<T>& InitializerList);
		List(const List<T>& Source);
		List(List<T>&& Right) noexcept;
		~List();

		List<T>& operator=(const List<T>& Source);
		List<T>& operator=(List<T>&& Right) noexcept;

		T& operator[](const Elysium::Core::size Index);
		const T& operator[](const Elysium::Core::size Index) const;

		const Elysium::Core::size GetCapacity() const;
		const Elysium::Core::size GetCount() const;
		const bool GetIsReadOnly() const;

		void SetCapacity(const Elysium::Core::size Value);

		void Add(const T& Item);
		void Add(T&& Item);
		void AddRange(const List<T>& Collection);
		void AddRange(const T* Collection, Elysium::Core::size Count);
		void Clear();
		bool Contains(const T& Item) const;
		const Elysium::Core::size IndexOf(const T& Item) const;
		const Elysium::Core::size IndexOf(const T& Item, const Elysium::Core::size Index) const;
		void Insert(const Elysium::Core::size Index, const T& Item);
		const Elysium::Core::size LastIndexOf(const T& Item) const;
		const Elysium::Core::size LastIndexOf(const T& Item, const Elysium::Core::size Index) const;
		bool Remove(const T& Item);
		void RemoveAt(const Elysium::Core::size Index);
		void RemoveRange(const Elysium::Core::size Index, const Elysium::Core::size Count);
		void Reverse();
	private:
		Elysium::Core::size _Capacity;
		Elysium::Core::size _Count;
		T* _Data;

		void Resize(const Elysium::Core::size DesiredMinimumSize);
		void Resize(const Elysium::Core::size DesiredMinimumSize, const Elysium::Core::size InsertionIndex);
	};

	template<class T>
	inline List<T>::List()
		: _Capacity(0), _Count(0), _Data(nullptr)
	{ }
	template<class T>
	inline List<T>::List(const Elysium::Core::size Capacity)
		: _Capacity(Capacity <= LIST_MAX ? Capacity : LIST_MAX), _Count(_Capacity), _Data(_Capacity == 0 ? nullptr : new T[_Capacity])
	{ }
	template<class T>
	inline List<T>::List(const Elysium::Core::Template::Container::InitializerList<T>& InitializerList)
		: _Capacity(InitializerList.size()), _Count(_Capacity), _Data(_Capacity == 0 ? nullptr : new T[_Capacity])
	{
		Elysium::Core::size Index = 0;
		const T* Iterator = InitializerList.begin();
		const T* LastElement = InitializerList.end();
		for (;  Iterator != nullptr && Iterator != LastElement; ++Iterator)
		{
#pragma warning(disable : 6011)	// _Data won't be nullptr if InitializerList contains elements
			_Data[Index++] = *Iterator;
#pragma warning(default : 6011)
		}
	}
	template<class T>
	inline List<T>::List(const List<T>& Source)
		: _Capacity(Source._Capacity), _Count(Source._Count), _Data(_Capacity == 0 ? nullptr : new T[_Capacity])
	{
		for (Elysium::Core::size i = 0; i < _Count; i++)
		{
#pragma warning(disable : 6011)	// _Data won't be nullptr if Source contains elements
			_Data[i] = Source._Data[i];
#pragma warning(default : 6011)
		}
	}
	template<typename T>
	inline List<T>::List(List<T>&& Right) noexcept
		: _Capacity(0), _Count(0), _Data(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	template<class T>
	inline List<T>::~List()
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
			_Data = nullptr;
		}
	}

	template<class T>
	inline List<T>& List<T>::operator=(const List<T>& Source)
	{
		if (this != &Source)
		{
			SetCapacity(Source._Capacity);
			_Count = Source._Count;
			for (Elysium::Core::size i = 0; i < _Count; i++)
			{
				_Data[i] = T(Source._Data[i]);
			}
		}
		return *this;
	}
	template<typename T>
	inline List<T>& List<T>::operator=(List<T>&& Right) noexcept
	{
		if (this != &Right)
		{
			if (_Data != nullptr)
			{
				delete[] _Data;
			}

			_Data = Right._Data;
			_Capacity = Right._Capacity;
			_Count = Right._Count;

			Right._Data = nullptr;
			Right._Count = 0;
			Right._Capacity = 0;
		}
		return *this;
	}
	template<class T>
	inline T& List<T>::operator[](const Elysium::Core::size Index)
	{
		if (Index >= _Count)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<typename T>
	inline const T& List<T>::operator[](const Elysium::Core::size Index) const
	{
		if (Index >= _Count)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<class T>
	inline const Elysium::Core::size List<T>::GetCapacity() const
	{
		return _Capacity;
	}
	template<class T>
	inline const Elysium::Core::size List<T>::GetCount() const
	{
		return _Count;
	}
	template<class T>
	inline const bool List<T>::GetIsReadOnly() const
	{
		return false;
	}

	template<class T>
	inline void List<T>::SetCapacity(const Elysium::Core::size Value)
	{
		Resize(Value);
	}

	template<class T>
	inline void List<T>::Add(const T& Item)
	{
		// resize if required
		Resize(_Count + 1);

		// copy the element and increment the internal element counter
		_Data[_Count] = T(Item);
		_Count++;
	}
	template<typename T>
	inline void List<T>::Add(T&& Item)
	{
		// resize if required
		Resize(_Count + 1);

		// move the element and increment the internal element counter
		_Data[_Count] = Elysium::Core::Template::Functional::Move(Item);
		_Count++;
	}
	template<class T>
	inline void List<T>::AddRange(const List<T>& Collection)
	{
		// resize if required
		Elysium::Core::size CollectionCount = Collection.GetCount();
		Resize(_Count + CollectionCount);

		// use the copy operator to copy all elements and increment the internal element counter
		for (Elysium::Core::size i = 0; i < CollectionCount; i++)
		{
			_Data[_Count] = Collection[i];
			_Count++;
		}
	}
	template<class T>
	inline void List<T>::AddRange(const T* Collection, Elysium::Core::size Count)
	{
		// resize if required
		Resize(_Count + Count);

		// use the copy operator to copy all elements and increment the internal element counter
		for (Elysium::Core::size i = 0; i < Count; i++)
		{
			_Data[_Count] = T(Collection[i]);
			_Count++;
		}
	}
	template<class T>
	inline void List<T>::Clear()
	{
		_Count = 0;
	}
	template<class T>
	inline bool List<T>::Contains(const T& Item) const
	{
		for (Elysium::Core::size i = 0; i < _Count; i++)
		{
			if (_Data[i] == Item)
			{
				return true;
			}
		}
		return false;
	}
	template<class T>
	inline const Elysium::Core::size List<T>::IndexOf(const T& Item) const
	{
		for (Elysium::Core::size i = 0; i < _Count; i++)
		{
			if (_Data[i] == Item)
			{
				return i;
			}
		}
		return -1;
	}
	template<typename T>
	inline const Elysium::Core::size List<T>::IndexOf(const T& Item, const Elysium::Core::size Index) const
	{
		for (Elysium::Core::size i = Index; i < _Count; i++)
		{
			if (_Data[i] == Item)
			{
				return i;
			}
		}
		return -1;
	}
	template<class T>
	inline void List<T>::Insert(const Elysium::Core::size Index, const T& Item)
	{
		if (Index > _Count)
		{
			throw IndexOutOfRangeException();
		}

		// resize if required
		Resize(_Count + 1, Index);

		// use the copy constructor to clone the element and increment the internal element counter
		_Data[Index] = T(Item);
		_Count++;
	}
	template<typename T>
	inline const Elysium::Core::size List<T>::LastIndexOf(const T& Item) const
	{
		for (Elysium::Core::size i = _Count; i > 0; i--)
		{
			if (_Data[i - 1] == Item)
			{
				return i;
			}
		}
		return -1;
	}
	template<typename T>
	inline const Elysium::Core::size List<T>::LastIndexOf(const T& Item, Elysium::Core::size Index) const
	{
		for (Elysium::Core::size i = _Count; i > Index; i--)
		{
			if (_Data[i - 1] == Item)
			{
				return i;
			}
		}
		return -1;
	}
	template<class T>
	inline bool List<T>::Remove(const T& Item)
	{
		for (Elysium::Core::size i = 0; i < _Count; i++)
		{
			if (_Data[i] == Item)
			{
				RemoveAt(i);
				return true;
			}
		}
		return false;
	}
	template<class T>
	inline void List<T>::RemoveAt(const Elysium::Core::size Index)
	{
		if (Index >= _Count)
		{
			throw IndexOutOfRangeException();
		}

		// ToDo: I think, in this case we can actually use memcpy - if I'm wrong at some point, use the code below 
		memcpy(&_Data[Index], &_Data[Index + 1], sizeof(T) * (_Count - Index));
		/*
		// move all old elements right of InsertionIndex to _Data using the copy constructor
		for (Elysium::Core::size i = Index; i < _Count; i++)
		{
			_Data[i] = Elysium::Core::Template::Functional::Move(_Data[i + 1]);
		}
		*/
		_Count--;
	}
	template<typename T>
	inline void List<T>::RemoveRange(const Elysium::Core::size Index, const Elysium::Core::size Count)
	{
		if (_Count < Index || Index + Count > _Count)
		{
			throw IndexOutOfRangeException();
		}

		// ToDo: I think, in this case we can actually use memcpy
		memcpy(&_Data[Index], &_Data[Index + Count], sizeof(T) * (_Count - Index));
		/*
		for (Elysium::Core::size i = Index; i < Index + Count; i++)
		{
			_Data[i] = Elysium::Core::Template::Functional::Move(_Data[i + 1]);
		}
		*/
		_Count -= Count;
	}
	template<typename T>
	inline void List<T>::Reverse()
	{
		Elysium::Core::Template::Functional::Reverse(&_Data[0], &_Data[_Count]);
	}

	template<class T>
	inline void List<T>::Resize(const Elysium::Core::size DesiredMinimumSize)
	{
		if (DesiredMinimumSize < _Count)
		{
			throw ArgumentOutOfRangeException();
		}
		if (DesiredMinimumSize > LIST_MAX)
		{
			throw OutOfMemoryException();
		}

		if (DesiredMinimumSize > _Capacity)
		{
			Elysium::Core::size ActualCapacity = _Capacity * 2;
			if (ActualCapacity == 0)
			{
				ActualCapacity = 1;
			}
			while (ActualCapacity < DesiredMinimumSize)
			{
				ActualCapacity *= 2;
			}
			if (ActualCapacity > LIST_MAX)
			{
				ActualCapacity = LIST_MAX;
			}

			// store a pointer to old data before allocating new data
			T* OldData = _Data;
			_Data = new T[ActualCapacity];
			_Capacity = ActualCapacity;

			// move all old elements to _Data
			for (Elysium::Core::size i = 0; i < _Count; i++)
			{
				_Data[i] = Elysium::Core::Template::Functional::Move(OldData[i]);
			}

			// delete old data
			delete[] OldData;
		}
	}
	template<class T>
	inline void List<T>::Resize(const Elysium::Core::size DesiredMinimumSize, const Elysium::Core::size InsertionIndex)
	{
		if (DesiredMinimumSize < _Count)
		{
			throw ArgumentOutOfRangeException();
		}
		if (DesiredMinimumSize > LIST_MAX)
		{
			throw OutOfMemoryException();
		}

		if (DesiredMinimumSize > _Capacity)
		{
			Elysium::Core::size ActualCapacity = _Capacity * 2;
			if (ActualCapacity == 0)
			{
				ActualCapacity = 1;
			}
			while (ActualCapacity < DesiredMinimumSize)
			{
				ActualCapacity *= 2;
			}
			if (ActualCapacity > LIST_MAX)
			{
				ActualCapacity = LIST_MAX;
			}

			// store a pointer to old data before allocating new data
			T* OldData = _Data;
			_Data = new T[ActualCapacity];
			_Capacity = ActualCapacity;

			// move all old elements left of InsertionIndex to _Data
			for (Elysium::Core::size i = 0; i < InsertionIndex; i++)
			{
				_Data[i] = Elysium::Core::Template::Functional::Move(OldData[i]);
			}

			// move all old elements right of InsertionIndex to _Data
			for (Elysium::Core::size i = _Count - 1; i >= InsertionIndex; i--)
			{
				_Data[i + 1] = Elysium::Core::Template::Functional::Move(OldData[i]);
			}

			// delete old data
			delete[] OldData;
		}
		else
		{
			// ToDo: I think, in this case we can actually use memcpy - if I'm wrong at some point, use the code below 
			memcpy(&_Data[InsertionIndex + 1], &_Data[InsertionIndex], sizeof(T) * (_Count - InsertionIndex));
			/*
			// move all old elements right of InsertionIndex to _Data
			for (Elysium::Core::size i = _Count - 1; i >= InsertionIndex; i--)
			{
				_Data[i + 1] = Elysium::Core::Template::Functional::Move(_Data[i]);
			}
			*/
		}
	}
}
#endif