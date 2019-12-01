/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY

#ifndef ELYSIUM_CORE_COLLECTIONS_ILIST
#include "IList.hpp"
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Collections
		{
			namespace Template
			{
				/*
				//template <class T, int Size>
				template <class T>
				class Array : public IList<T>
				{
				public:
					Array(size_t Length);
					Array(std::initializer_list<T> InitializerList);
					Array(const Array<T>& Source);
					//Array(Array<T>&& Right);
					~Array();
				private:
					size_t _Length;
					T* _Data;
				};

				template<class T>
				inline Array<T>::Array(size_t Length)
					: _Length(Length <= INT_MAX ? Length : INT_MAX),
					_Data((T*)malloc(sizeof(T) * _Capacity))
				{
				}
				template<class T>
				inline Array<T>::Array(std::initializer_list<T> InitializerList)
				{
				}
				template<class T>
				inline Array<T>::Array(const Array<T>& Source)
					: _Length(Source._Length),
					_Data((T*)malloc(sizeof(T) * _Length)),
				{
					for (size_t i = 0; i < _Capacity; i++)
					{
						_Data[i] = T(Source._Data[i]);
					}
				}
				template<class T>
				inline Array<T>::~Array()
				{
					free(_Data);
				}
				*/
			}
		}
	}
}
#endif
