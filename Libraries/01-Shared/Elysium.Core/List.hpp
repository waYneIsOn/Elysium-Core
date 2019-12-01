/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST

#ifndef ELYSIUM_CORE_COLLECTIONS_ILIST
#include "IList.hpp"
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef __midl
#include <cstring>
#endif

#ifndef _INC_LIMITS
#include <limits>
#endif

#ifndef _XUTILITY_
#include <xutility>
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#include "OutOfMemoryException.hpp"
#endif

#if defined (_WIN64)
#define LIST_MAX LLONG_MAX
#elif defined(_WIN32) || defined(__WIN32__)
#define LIST_MAX INT_MAX
#else
#error Unsupported OS
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Collections
		{
			namespace Template
			{
				template <typename T>
				class List : public IList<T>
				{
				public:
					List();
					List(size_t Capacity);
					List(const std::initializer_list<T>& InitializerList);
					List(const List<T>& Source);
					List(List<T>&& Right) noexcept;
					~List();

					// properties - getter
					const size_t GetCapacity() const;
					virtual const size_t GetCount() const override;
					virtual const bool GetIsReadOnly() const override;

					// properties - setter
					void SetCapacity(size_t Value);

					// operators
					List<T>& operator=(List<T>&& Right) noexcept;
					virtual List<T>& operator=(const List<T>& Value);
					virtual T& operator[](size_t Index) const override;

					// methods
					virtual void Add(const T& Item) override;
					void AddRange(const IList<T>& Collection);
					void AddRange(const T* Collection, size_t Count);
					virtual void Clear() override;
					virtual bool Contains(const T& Item) const override;
					virtual const size_t IndexOf(const T& Item) const override;
					const size_t IndexOf(const T& Item, size_t Index) const;
					virtual void Insert(size_t Index, const T& Item) override;
					const size_t LastIndexOf(const T& Item) const;
					const size_t LastIndexOf(const T& Item, size_t Index) const;
					bool Remove(const T& Item) override;
					void RemoveAt(size_t Index) override;
					void RemoveRange(size_t Index, size_t Count);
					void Reverse();
				private:
					size_t _Capacity;
					T* _Data;
					size_t _Count;

					void Resize(size_t DesiredMinimumSize);
					void Resize(size_t DesiredMinimumSize, size_t InsertionIndex);
				};

				template<class T>
				inline List<T>::List()
					: _Capacity(0),
					_Data(nullptr),
					_Count(0)
				{ }
				template<class T>
				inline List<T>::List(size_t Capacity)
					: _Capacity(Capacity <= LIST_MAX ? Capacity : LIST_MAX),
					_Data(_Capacity == 0 ? nullptr : new T[_Capacity]),
					_Count(_Capacity)
				{ }
				template<class T>
				inline List<T>::List(const std::initializer_list<T> & InitializerList)
					: _Capacity(InitializerList.size()),
					_Data(_Capacity == 0 ? nullptr : new T[_Capacity]),
					_Count(_Capacity)
				{
					size_t i = 0;
					typename std::initializer_list<T>::iterator Iterator;
					for (Iterator = InitializerList.begin(); Iterator < InitializerList.end(); ++Iterator)
					{
						_Data[i++] = T(*Iterator);
					}
				}
				template<class T>
				inline List<T>::List(const List<T>& Source)
					: _Capacity(Source._Capacity),
					_Data(_Capacity == 0 ? nullptr : new T[_Capacity]),
					_Count(Source._Count)
				{
					for (size_t i = 0; i < _Capacity; i++)
					{
						_Data[i] = T(Source._Data[i]);
					}
				}
				template<typename T>
				inline List<T>::List(List<T>&& Right) noexcept
					: _Capacity(0), _Data(nullptr), _Count(0)
				{
					*this = std::move(Right);
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
				inline const size_t List<T>::GetCapacity() const
				{
					return _Capacity;
				}
				template<class T>
				inline const size_t List<T>::GetCount() const
				{
					return _Count;
				}
				template<class T>
				inline const bool List<T>::GetIsReadOnly() const
				{
					return false;
				}

				template<class T>
				inline void List<T>::SetCapacity(size_t Value)
				{
					Resize(Value);
				}

				template<typename T>
				inline List<T>& List<T>::operator=(List<T>&& Right) noexcept
				{
					if (this != &Right)
					{
						// release currently held objects
						if (_Data != nullptr)
						{
							delete _Data;
						}

						// grab Right's objects
						_Data = Right._Data;
						_Capacity = Right._Capacity;
						_Count = Right._Count;

						// release Right's objects
						Right._Data = nullptr;
						Right._Count = 0;
						Right._Capacity = 0;
					}

					return *this;
				}
				template<class T>
				inline List<T>& List<T>::operator=(const List<T>& Value)
				{
					if (this != &Value)
					{
						SetCapacity(Value._Capacity);
						_Count = Value._Count;
						for (size_t i = 0; i < _Count; i++)
						{
							_Data[i] = T(Value._Data[i]);
							i++;
						}
					}

					return *this;
				}
				template<class T>
				inline T & List<T>::operator[](size_t Index) const
				{
					if (Index >= _Count)
					{
						throw IndexOutOfRangeException();
					}

					return _Data[Index];
				}
				
				template<class T>
				inline void List<T>::Add(const T & Item)
				{
					// resize if required
					Resize(_Count + 1);

					// use the copy constructor to clone the element and increment the internal element counter
					_Data[_Count] = T(Item);
					_Count++;
				}
				template<class T>
				inline void List<T>::AddRange(const IList<T>& Collection)
				{
					// resize if required
					size_t CollectionCount = Collection->GetCount();
					Resize(_Count + CollectionCount);

					// use the copy operator to copy all elements and increment the internal element counter
					for (size_t i = 0; i < CollectionCount; i++)
					{
						_Data[_Count] = T(Collection(i));
						_Count++;
					}
				}
				template<class T>
				inline void List<T>::AddRange(const T * Collection, size_t Count)
				{
					// resize if required
					Resize(_Count + Count);

					// use the copy operator to copy all elements and increment the internal element counter
					for (size_t i = 0; i < Count; i++)
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
				inline bool List<T>::Contains(const T & Item) const
				{
					for (size_t i = 0; i < _Count; i++)
					{
						if (_Data[i] == Item)
						{
							return true;
						}
					}
					return false;
				}
				template<class T>
				inline const size_t List<T>::IndexOf(const T & Item) const
				{
					for (size_t i = 0; i < _Count; i++)
					{
						if (_Data[i] == Item)
						{
							return i;
						}
					}
					return -1;
				}
				template<typename T>
				inline const size_t List<T>::IndexOf(const T & Item, size_t Index) const
				{
					for (size_t i = Index; i < _Count; i++)
					{
						if (_Data[i] == Item)
						{
							return i;
						}
					}
					return -1;
				}
				template<class T>
				inline void List<T>::Insert(size_t Index, const T & Item)
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
				inline const size_t List<T>::LastIndexOf(const T & Item) const
				{
					for (size_t i = _Count; i > 0; i--)
					{
						if (_Data[i - 1] == Item)
						{
							return i;
						}
					}
					return -1;
				}
				template<typename T>
				inline const size_t List<T>::LastIndexOf(const T & Item, size_t Index) const
				{
					for (size_t i = _Count; i > Index; i--)
					{
						if (_Data[i - 1] == Item)
						{
							return i;
						}
					}
					return -1;
				}
				template<class T>
				inline bool List<T>::Remove(const T & Item)
				{
					for (size_t i = 0; i < _Count; i++)
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
				inline void List<T>::RemoveAt(size_t Index)
				{
					if (Index >= _Count)
					{
						throw IndexOutOfRangeException();
					}

					// ToDo: I think, in this case we can actually use memcpy - if I'm wrong at some point, use the code below 
					memcpy(&_Data[Index], &_Data[Index + 1], sizeof(T) * (_Count - Index));
					/*
					// move all old elements right of InsertionIndex to _Data using the copy constructor
					for (size_t i = Index; i < _Count; i++)
					{
						_Data[i] = std::move(_Data[i + 1]);
					}
					*/
					_Count--;
				}
				template<typename T>
				inline void List<T>::RemoveRange(size_t Index, size_t Count)
				{
					if (_Count < Index || Index + Count > _Count)
					{
						throw IndexOutOfRangeException();
					}

					// ToDo: I think, in this case we can actually use memcpy
					memcpy(&_Data[Index], &_Data[Index + Count], sizeof(T) * (_Count - Index));
					/*
					for (size_t i = Index; i < Index + Count; i++)
					{
						_Data[i] = std::move(_Data[i + 1]);
					}
					*/
					_Count -= Count;
				}
				template<typename T>
				inline void List<T>::Reverse()
				{
					std::reverse(&_Data[0], &_Data[_Count]);
				}

				template<class T>
				inline void List<T>::Resize(size_t DesiredMinimumSize)
				{
					if (DesiredMinimumSize < _Count)
					{	// ToDo: throw a specific ArgumentOutOfRangeException
						throw Exception(u"ArgumentOutOfRangeException");
					}
					if (DesiredMinimumSize > LIST_MAX)
					{
						throw OutOfMemoryException();
					}

					if (DesiredMinimumSize > _Capacity)
					{
						// define actual capacity
						size_t ActualCapacity = _Capacity * 2 + 1;
						while (ActualCapacity < DesiredMinimumSize)
						{
							ActualCapacity = ActualCapacity * 2 + 1;
						}
						if (ActualCapacity > LIST_MAX)
						{
							ActualCapacity = LIST_MAX;
						}

						// store a pointer to old data before allocating new data
						T* OldData = _Data;
						_Data = new T[ActualCapacity];
						_Capacity = ActualCapacity;

						// copy all old elements to _Data using the move operator
						for (size_t i = 0; i < _Count; i++)
						{
							_Data[i] = std::move(OldData[i]);
						}

						// delete old data
						delete[] OldData;
					}
				}
				template<class T>
				inline void List<T>::Resize(size_t DesiredMinimumSize, size_t InsertionIndex)
				{
					if (DesiredMinimumSize < _Count)
					{	// ToDo: throw a specific ArgumentOutOfRangeException
						throw Exception(u"ArgumentOutOfRangeException");
					}
					if (DesiredMinimumSize > LIST_MAX)
					{
						throw OutOfMemoryException();
					}

					if (DesiredMinimumSize > _Capacity)
					{
						// define actual capacity
						size_t ActualCapacity = _Capacity * 2 + 1;
						while (ActualCapacity < DesiredMinimumSize)
						{
							ActualCapacity = ActualCapacity * 2 + 1;
						}
						if (ActualCapacity > LIST_MAX)
						{
							ActualCapacity = LIST_MAX;
						}

						// store a pointer to old data before allocating new data
						T* OldData = _Data;
						_Data = new T[ActualCapacity];
						_Capacity = ActualCapacity;

						// move all old elements left of InsertionIndex to _Data using the move operator
						for (size_t i = 0; i < InsertionIndex; i++)
						{
							_Data[i] = std::move(OldData[i]);
						}

						// move all old elements right of InsertionIndex to _Data using the move oeprator
						for (size_t i = _Count - 1; i >= InsertionIndex; i--)
						{
							_Data[i + 1] = std::move(OldData[i]);
						}

						// delete old data
						delete[] OldData;
					}
					else
					{
						// ToDo: I think, in this case we can actually use memcpy - if I'm wrong at some point, use the code below 
						memcpy(&_Data[InsertionIndex + 1], &_Data[InsertionIndex], sizeof(T) * (_Count - InsertionIndex));
						/*
						// copy all old elements right of InsertionIndex to _Data using the copy constructor
						for (size_t i = _Count - 1; i >= InsertionIndex; i--)
						{
							_Data[i + 1] = std::move(_Data[i]);
						}
						*/
					}
				}
			}
		}
	}
}
#endif
