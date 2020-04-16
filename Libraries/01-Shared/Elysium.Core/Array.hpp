/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
//#include "IndexOutOfRangeException.hpp"
#endif

constexpr const size_t ARRAY_MAX = static_cast<size_t>(-1);

namespace Elysium::Core::Collections::Template
{
	template <class T>
	class Array final
	{
	public:
		Array(const size_t Length);
		Array(std::initializer_list<T> InitializerList);
		Array(const Array<T>& Source);
		Array(Array<T>&& Right);
		~Array();

		Array<T>& operator=(const Array<T>& Source);
		Array<T>& operator=(Array<T>&& Right) noexcept;
		T& operator[](size_t Index) const;

		const size_t GetLength() const;

		static void Clear(T* Array, const size_t Length);

		static void Copy(const T* Source, T* Destination, const size_t Length);

		static void Move(const T* Source, T* Destination, const size_t Length);
	private:
		size_t _Length;
		T* _Data;
	};

	template<class T>
	inline Array<T>::Array(const size_t Length)
		: _Length(Length <= ARRAY_MAX ? Length : ARRAY_MAX), _Data(_Length == 0 ? nullptr : new T[_Length])
	{ }
	template<class T>
	inline Array<T>::Array(std::initializer_list<T> InitializerList)
		: _Length(InitializerList.size()), _Data(_Length == 0 ? nullptr : new T[_Length])
	{
	}
	template<class T>
	inline Array<T>::Array(const Array<T>& Source)
		: _Length(Source._Length), _Data(Source._Length == 0 ? nullptr : new T[_Length])
	{
		for (size_t i = 0; i < _Length; i++)
		{
			_Data[i] = T(Source._Data[i]);
		}
	}
	template<class T>
	inline Array<T>::Array(Array<T>&& Right)
		: _Length(0), _Data(nullptr)
	{
		*this = std::move(Right);
	}
	template<class T>
	inline Array<T>::~Array()
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
			_Data = nullptr;
		}
	}

	template<class T>
	inline Array<T>& Array<T>::operator=(const Array<T>& Source)
	{
		if (this != &Source)
		{
			_Length = Source._Length;
			_Data = _Length == 0 ? nullptr : new T[_Length];
			for (size_t i = 0; i < _Length; i++)
			{
				_Data[i] = T(Source._Data[i]);
			}
		}
		return *this;
	}
	template<class T>
	inline Array<T>& Array<T>::operator=(Array<T>&& Right) noexcept
	{
		if (this != &Right)
		{
			_Length = Right._Length;
			_Data = Right._Data;

			Right._Length = 0;
			Right._Data = nullptr;
		}
		return *this;
	}
	template<class T>
	inline T & Array<T>::operator[](size_t Index) const
	{
		if (Index >= _Length)
		{
			//throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}
	template<class T>
	inline const size_t Array<T>::GetLength() const
	{
		return _Length;
	}

	template<class T>
	inline void Array<T>::Clear(T * Array, const size_t Length)
	{
		std::memset(Array, 0, Length);
	}

	template<class T>
	inline void Array<T>::Copy(const T* Source, T* Destination, const size_t Length)
	{
		for (size_t i = 0; i < Length; i++)
		{
			Destination[i] = T(Source[i]);
		}
	}
	template<class T>
	inline void Array<T>::Move(const T * Source, T * Destination, const size_t Length)
	{
		for (size_t i = 0; i < Length; i++)
		{
			Destination[i] = std::move(Source[i]);
		}
	}
}
#endif
