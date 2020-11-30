/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_QUEUE
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_QUEUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "InvalidOperationException.hpp"
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
		Queue(const size_t Capacity, const float GrowFactor);
		Queue(const Queue<T>& Source) = delete;
		Queue(Queue<T>&& Right) noexcept = delete;
		~Queue();

		Queue<T>& operator=(const Queue<T>& Source) = delete;
		Queue<T>& operator=(Queue<T>&& Right) noexcept = delete;

		const size_t GetCount() const;

		void Clear();
		void TrimToSize();

		void Enqueue(const T& Item);
		const T Peek() const;
		T Dequeue();
	private:
		size_t _Count;
		size_t _Capacity;
		size_t _GrowFactor;
		size_t _HeadIndex;
		size_t _TailIndex;
		T* _Data;

		static const size_t _MinimumGrow = 4;
		static const size_t _ShrinkThreshold = 32;

		void SetCapacity(size_t DesiredCapacity);
	};

	template<class T>
	inline Queue<T>::Queue()
		: Queue(32, 2.0f)
	{ }
	template<class T>
	inline Queue<T>::Queue(const size_t Capacity)
		: Queue(Capacity, 2.0f)
	{ }
	template<class T>
	inline Queue<T>::Queue(const size_t Capacity, const float GrowFactor)
		: _Count(0),
		_Capacity(Capacity <= QUEUE_MAX ? Capacity : QUEUE_MAX), 
		_GrowFactor(static_cast<size_t>(static_cast<double>(GrowFactor) * 100)), 
		_HeadIndex(0), _TailIndex(0), _Data(_Capacity == 0 ? nullptr : new T[_Capacity])
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
		_Count = 0;
		_Capacity = 0;
		_HeadIndex = 0;
		_TailIndex = 0;
	}
	template<class T>
	inline void Queue<T>::TrimToSize()
	{
		SetCapacity(_Count);
	}

	template<class T>
	inline void Queue<T>::Enqueue(const T & Item)
	{
		if (_Count == _Capacity)
		{
			size_t DesiredCapacity = _Capacity * _GrowFactor / 100;
			if (DesiredCapacity < _Capacity + _MinimumGrow)
			{
				DesiredCapacity = _Capacity + _MinimumGrow;
			}
			SetCapacity(DesiredCapacity);
		}

		_Data[_TailIndex] = T(Item);
		_TailIndex = (_TailIndex + 1) % _Capacity;
		_Count++;
	}
	template<class T>
	inline const T Queue<T>::Peek() const
	{
		if (_Count == 0)
		{
			throw InvalidOperationException(u8"The Queue is empty");
		}
		return _Data[_HeadIndex];
	}
	template<class T>
	inline T Queue<T>::Dequeue()
	{
		if (_Count == 0)
		{
			throw InvalidOperationException(u8"The Queue is empty");
		}

		T& RemovedItem = _Data[_HeadIndex];
		_HeadIndex = (_HeadIndex + 1) % _Capacity;
		_Count--;

		return RemovedItem;
	}

	template<class T>
	inline void Queue<T>::SetCapacity(size_t DesiredCapacity)
	{
		T* OldData = _Data;
		_Data = new T[DesiredCapacity];
		if (_Capacity > 0)
		{
			if (_HeadIndex < _TailIndex)
			{
				for (size_t i = 0; i < _Capacity; i++)
				{
					_Data[i] = OldData[_HeadIndex + i];
					//_Data[i] = std::move(OldData[_HeadIndex + i]);
				}
			}
			else
			{
				for (size_t i = 0; i < _Count - _HeadIndex; i++)
				{
					_Data[i] = OldData[_HeadIndex + i];
					//_Data[i] = std::move(OldData[_HeadIndex + i]);
				}
				for (size_t i = 0; i < _TailIndex; i++)
				{
					_Data[_Count - _HeadIndex + i] = OldData[i];
					//_Data[_Count - _HeadIndex + i] = std::move(OldData[i]);
				}
			}
		}

		_HeadIndex = 0;
		_TailIndex = (_Capacity == DesiredCapacity) ? 0 : _Capacity;
		_Capacity = DesiredCapacity;
	}
}
#endif
