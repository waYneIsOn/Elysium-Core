/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_QUEUE
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_QUEUE

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
//#include "InvalidOperationException.hpp"
#endif

constexpr const size_t QUEUE_MAX = static_cast<size_t>(-1);

namespace Elysium::Core::Collections::Template
{
	template <class T>
	class Queue final
	{
	public:
		Queue();
		Queue(const size_t Capacity);
		Queue(const Queue<T>& Source) = delete;
		Queue(Queue<T>&& Right) noexcept = delete;
		~Queue();

		Queue<T>& operator=(const Queue<T>& Source) = delete;
		Queue<T>& operator=(Queue<T>&& Right) noexcept = delete;

		const size_t GetCount() const;

		void Clear();
		void Enqueue(const T& Item);
		const T Peek() const;
		T Dequeue();
	private:
		size_t _Capacity;
		size_t _Count;
		size_t _HeadIndex;
		size_t _TailIndex;
		T* _Data;

		void Resize(size_t DesiredMinimumSize);
	};

	template<class T>
	inline Queue<T>::Queue()
		: _Capacity(32), _Count(0), _HeadIndex(0), _TailIndex(0), _Data(new T[_Capacity])
	{ }
	template<class T>
	inline Queue<T>::Queue(const size_t Capacity)
		: _Capacity(Capacity <= QUEUE_MAX ? Capacity : QUEUE_MAX), _Count(0), _HeadIndex(0), _TailIndex(0),
		_Data(_Capacity == 0 ? nullptr : new T[_Capacity])
	{ }
	template<class T>
	inline Queue<T>::~Queue()
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
			_Data = nullptr;
		}
	}

	template<class T>
	inline const size_t Queue<T>::GetCount() const
	{
		return _Count;
	}

	template<class T>
	inline void Queue<T>::Clear()
	{
		_Capacity = 0;
		_Count = 0;
		_HeadIndex = 0;
		_TailIndex = 0;
	}
	template<class T>
	inline void Queue<T>::Enqueue(const T & Item)
	{
		// resize if required
		Resize(_Count + 1);

		// use the copy constructor to clone the element and increment the internal element counter
		_Data[_Count] = T(Item);
		_TailIndex = (_TailIndex + 1) % _Count;
		_Count++;
	}
	template<class T>
	inline const T Queue<T>::Peek() const
	{
		if (_Count == 0)
		{
			//throw InvalidOperationException();
		}
		return _Data[_HeadIndex];
	}
	template<class T>
	inline T Queue<T>::Dequeue()
	{
		if (_Count == 0)
		{
			//throw InvalidOperationException();
		}

		T RemovedItem = _Data[_HeadIndex];
		_HeadIndex = (_HeadIndex + 1) % _Count;
		_Count--;
		return RemovedItem;
	}

	template<class T>
	inline void Queue<T>::Resize(size_t DesiredMinimumSize)
	{
		if (DesiredMinimumSize < _Count)
		{
			//throw ArgumentOutOfRangeException();
		}
		if (DesiredMinimumSize > QUEUE_MAX)
		{
			//throw OutOfMemoryException();
		}

		if (DesiredMinimumSize > _Capacity)
		{
			// define actual capacity
			size_t ActualCapacity = _Capacity * 2 + 1;
			while (ActualCapacity < DesiredMinimumSize)
			{
				ActualCapacity = ActualCapacity * 2 + 1;
			}
			if (ActualCapacity > QUEUE_MAX)
			{
				ActualCapacity = QUEUE_MAX;
			}

			// store a pointer to old data before allocating new data
			T* OldData = _Data;
			_Data = new T[ActualCapacity];
			_Capacity = ActualCapacity;

			// move all old elements to _Data
			for (size_t i = 0; i < _Count; i++)
			{
				_Data[i] = std::move(OldData[i]);
			}

			// delete old data
			delete[] OldData;
		}
	}
}
#endif
