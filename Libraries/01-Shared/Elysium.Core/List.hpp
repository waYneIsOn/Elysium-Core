/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST
#define ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST

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

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_OUTOFMEMORYEXCEPTION
#include "OutOfMemoryException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Collections
		{
			namespace Generic
			{
				template <typename T>
				class List : public IList<T>
				{
				public:
					List();
					List(size_t Capacity);
					List(std::initializer_list<T> InitializerList);
					List(const List<T>& Source);
					~List();

					// properties - getter
					const size_t GetCapacity() const;
					virtual const size_t GetCount() const override;
					virtual const bool GetIsReadOnly() const override;

					// properties - setter
					void SetCapacity(size_t Value);

					// operators
					virtual List<T>& operator=(const List<T>& Value);
					virtual T& operator[](size_t Index) const override;

					// methods
					virtual void Add(const T& Item) override;
					virtual void Add(const T* Item) override;
					virtual void AddRange(const IList<T>* Collection);
					virtual void AddRange(const T* Collection, size_t Offset, size_t Count);
					virtual void Clear() override;
					virtual bool Contains(const T& Item) override;
					virtual const size_t IndexOf(const T& Item) const override;
					virtual void Insert(size_t Index, const T& Item) override;
					virtual bool Remove(const T& Item) override;
					virtual void RemoveAt(size_t Index) override;
				private:
					size_t _Capacity;
					T* _Data;
					size_t _NumberOfElements;

					void Resize(size_t DesiredMinimumSize);
					void Resize(size_t DesiredMinimumSize, size_t InsertionIndex);
				};

				template<class T>
				inline List<T>::List()
					: _Capacity(0),
					_Data(nullptr),
					_NumberOfElements(0)
				{ }
				template<class T>
				inline List<T>::List(size_t Capacity)
					: _Capacity(Capacity <= INT_MAX ? Capacity : INT_MAX),
					_Data(_Capacity == 0 ? nullptr : new T[_Capacity]),
					_NumberOfElements(_Capacity)
				{ }
				template<class T>
				inline List<T>::List(std::initializer_list<T> InitializerList)
					: _Capacity(InitializerList.size()),
					_Data(_Capacity == 0 ? nullptr : new T[_Capacity]),
					_NumberOfElements(_Capacity)
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
					_NumberOfElements(Source._NumberOfElements)
				{
					for (size_t i = 0; i < _Capacity; i++)
					{
						_Data[i] = T(Source._Data[i]);
					}
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
					return _NumberOfElements;
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

				template<class T>
				inline List<T>& List<T>::operator=(const List<T>& Value)
				{
					if (this != &Value)
					{
						SetCapacity(Value._Capacity);
						_NumberOfElements = Value._NumberOfElements;
						for (size_t i = 0; i < _NumberOfElements; i++)
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
					if (Index >= _NumberOfElements)
					{
						throw IndexOutOfRangeException();
					}

					return _Data[Index];
				}

				template<class T>
				inline void List<T>::Add(const T & Item)
				{
					Add(&Item);
				}
				template<class T>
				inline void List<T>::Add(const T * Item)
				{
					// resize if required
					Resize(_NumberOfElements + 1);

					// use the copy constructor to clone the element and increment the internal element counter
					_Data[_NumberOfElements] = T(*Item);
					_NumberOfElements++;
				}
				template<class T>
				inline void List<T>::AddRange(const IList<T>* Collection)
				{
					// resize if required
					size_t CollectionCount = Collection->GetCount();
					Resize(_NumberOfElements + CollectionCount);

					// use the copy constructor to clone all elements and increment the internal element counter
					for (size_t i = 0; i < CollectionCount; i++)
					{
						_Data[_NumberOfElements] = T(Collection->operator[](i));
						_NumberOfElements++;
					}
				}
				template<class T>
				inline void List<T>::AddRange(const T * Collection, size_t Offset, size_t Count)
				{
					// resize if required
					Resize(_NumberOfElements + Count);

					// use the copy constructor to clone all elements and increment the internal element counter
					for (size_t i = 0; i < Count; i++)
					{
						_Data[_NumberOfElements] = T(Collection[Offset + i]);
						_NumberOfElements++;
					}
				}
				template<class T>
				inline void List<T>::Clear()
				{
					_NumberOfElements = 0;
				}
				template<class T>
				inline bool List<T>::Contains(const T & Item)
				{
					for (size_t i = 0; i < _NumberOfElements; i++)
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
					for (size_t i = 0; i < _NumberOfElements; i++)
					{
						if (_Data[i] == Item)
						{
							return i;
						}
					}
					// ToDo: throw ArgumentOutOfRangeException
#ifdef UNICODE
					throw Exception(L"ArgumentOutOfRangeException");
#else
					throw Exception("ArgumentOutOfRangeException");
#endif
				}
				template<class T>
				inline void List<T>::Insert(size_t Index, const T & Item)
				{
					if (Index > _NumberOfElements)
					{
						throw IndexOutOfRangeException();
					}

					// resize if required
					Resize(_NumberOfElements + 1, Index);

					// use the copy constructor to clone the element and increment the internal element counter
					_Data[Index] = T(Item);
					_NumberOfElements++;
				}
				template<class T>
				inline bool List<T>::Remove(const T & Item)
				{
					for (size_t i = 0; i < _NumberOfElements; i++)
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
					if (Index >= _NumberOfElements)
					{
						throw IndexOutOfRangeException();
					}

					// ToDo: I think, in this case we can actually use memcpy - if I'm wrong at some point, use the code below 
					memcpy(&_Data[Index], &_Data[Index + 1], sizeof(T) * (_NumberOfElements - Index));
					/*
					// copy all old elements right of InsertionIndex to _Data using the copy constructor
					for (size_t i = Index; i < _NumberOfElements; i++)
					{
						_Data[i] = T(_Data[i + 1]);
					}
					*/
					_NumberOfElements--;
				}

				template<class T>
				inline void List<T>::Resize(size_t DesiredMinimumSize)
				{
					if (DesiredMinimumSize < _NumberOfElements)
					{	// ToDo: throw a specific ArgumentOutOfRangeException
#ifdef UNICODE
						throw Exception(L"ArgumentOutOfRangeException");
#else
						throw Exception("ArgumentOutOfRangeException");
#endif
					}
					if (DesiredMinimumSize > INT_MAX)
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
						if (ActualCapacity > INT_MAX)
						{
							ActualCapacity = INT_MAX;
						}

						// store a pointer to old data before allocating new data
						T* OldData = _Data;
						_Data = new T[ActualCapacity];
						_Capacity = ActualCapacity;

						// copy all old elements to _Data using the copy constructor
						for (size_t i = 0; i < _NumberOfElements; i++)
						{
							_Data[i] = T(OldData[i]);
						}

						// delete old data
						delete[] OldData;
					}
				}
				template<class T>
				inline void List<T>::Resize(size_t DesiredMinimumSize, size_t InsertionIndex)
				{
					if (DesiredMinimumSize < _NumberOfElements)
					{	// ToDo: throw a specific ArgumentOutOfRangeException
#ifdef UNICODE
						throw Exception(L"ArgumentOutOfRangeException");
#else
						throw Exception("ArgumentOutOfRangeException");
#endif
					}
					if (DesiredMinimumSize > INT_MAX)
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
						if (ActualCapacity > INT_MAX)
						{
							ActualCapacity = INT_MAX;
						}

						// store a pointer to old data before allocating new data
						T* OldData = _Data;
						_Data = new T[ActualCapacity];
						_Capacity = ActualCapacity;

						// copy all old elements left of InsertionIndex to _Data using the copy constructor
						for (size_t i = 0; i < InsertionIndex; i++)
						{
							_Data[i] = T(OldData[i]);
						}

						// copy all old elements right of InsertionIndex to _Data using the copy constructor
						for (size_t i = _NumberOfElements - 1; i >= InsertionIndex; i--)
						{
							_Data[i + 1] = T(OldData[i]);
						}

						// delete old data
						delete[] OldData;
					}
					else
					{
						// ToDo: I think, in this case we can actually use memcpy - if I'm wrong at some point, use the code below 
						memcpy(&_Data[InsertionIndex + 1], &_Data[InsertionIndex], sizeof(T) * (_NumberOfElements - InsertionIndex));
						/*
						// copy all old elements right of InsertionIndex to _Data using the copy constructor
						for (size_t i = _NumberOfElements - 1; i >= InsertionIndex; i--)
						{
							_Data[i + 1] = T(_Data[i]);
						}
						*/
					}
				}
			}
		}
	}
}
#endif
