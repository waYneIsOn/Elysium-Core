/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "../Elysium.Core.Template/InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS
#include "../Elysium.Core.Template/TypeTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REVERSE
#include "../Elysium.Core.Template/Reverse.hpp"
#endif

constexpr const Elysium::Core::size ARRAY_MAX = static_cast<Elysium::Core::size>(-1);

namespace Elysium::Core::Collections::Template
{
	template <class T>
	class Array final
	{
	public:
		Array(const Elysium::Core::size Length, const bool PerformMemoryClear = false);
		Array(const T* Begin, const Elysium::Core::size Length);
		Array(const Elysium::Core::Template::Container::InitializerList<T> InitializerList);
		Array(const Array<T>& Source);
		Array(Array<T>&& Right) noexcept;
		Array(const List<T>& Source);
		Array(List<T>&& Right) noexcept;
		~Array();

		Array<T>& operator=(const Array<T>& Source);
		Array<T>& operator=(Array<T>&& Right) noexcept;
		Array<T>& operator=(List<T>&& Right) noexcept;

		T& operator[](const Elysium::Core::size Index);
		const T& operator[](const Elysium::Core::size Index) const;

		const Elysium::Core::size GetLength() const;

		static void Clear(T* Array, const Elysium::Core::size Length);

		static void Copy(const T* Source, T* Destination, const Elysium::Core::size Length);

		static void Move(T* Source, T* Destination, const Elysium::Core::size Length);

		static void Reverse(Array<T>& Array);
	private:
		Elysium::Core::size _Length;
		T* _Data;
	};

	template<class T>
	inline Array<T>::Array(const Elysium::Core::size Length, const bool PerformMemoryClear)
		: _Length(Length <= ARRAY_MAX ? Length : ARRAY_MAX), _Data(_Length == 0 ? nullptr : new T[_Length])
	{
		if (PerformMemoryClear && _Data != nullptr)
		{
			memset(_Data, 0x00, _Length);
		}
	}
	template<class T>
	inline Array<T>::Array(const T* Begin, const Elysium::Core::size Length)
		: _Length(Length <= ARRAY_MAX ? Length : ARRAY_MAX), _Data(_Length == 0 ? nullptr : new T[_Length])
	{
		for (Elysium::Core::size i = 0; i < _Length; i++)
		{
			_Data[i] = Begin[i];
		}
	}
	template<class T>
	inline Array<T>::Array(const Elysium::Core::Template::Container::InitializerList<T> InitializerList)
		: _Length(InitializerList.size()), _Data(_Length == 0 ? nullptr : new T[_Length])
	{
		Elysium::Core::size Index = 0;
		const T* Iterator = InitializerList.begin();
		const T* LastElement = InitializerList.end();
		for (; Iterator != LastElement; ++Iterator)
		{
#pragma warning(disable : 6011)	// _Data won't be nullptr if InitializerList contains elements
			_Data[Index++] = *Iterator;
#pragma warning(default : 6011)
		}
	}
	template<class T>
	inline Array<T>::Array(const Array<T>& Source)
		: _Length(Source._Length), _Data(Source._Length == 0 ? nullptr : new T[_Length])
	{
		for (Elysium::Core::size i = 0; i < _Length; i++)
		{
			_Data[i] = Source._Data[i];
		}
	}
	template<class T>
	inline Array<T>::Array(Array<T>&& Right) noexcept
		: _Length(0), _Data(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	template<class T>
	inline Array<T>::Array(const List<T>& Source)
		: _Length(Source._Count), _Data(Source._Count == 0 ? nullptr : new T[_Length])
	{
		for (Elysium::Core::size i = 0; i < _Length; i++)
		{
			_Data[i] = Source._Data[i];
		}
	}
	template<class T>
	inline Array<T>::Array(List<T>&& Right) noexcept
		: _Length(0), _Data(nullptr)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
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
			if (_Data != nullptr)
			{
				delete[] _Data;
			}

			_Length = Source._Length;
			_Data = _Length == 0 ? nullptr : new T[_Length];
			for (Elysium::Core::size i = 0; i < _Length; i++)
			{
				_Data[i] = Source._Data[i];
			}
		}
		return *this;
	}

	template<class T>
	inline Array<T>& Array<T>::operator=(Array<T>&& Right) noexcept
	{
		if (this != &Right)
		{
			if (_Data != nullptr)
			{
				delete[] _Data;
			}

			_Length = Right._Length;
			_Data = Right._Data;

			Right._Length = 0;
			Right._Data = nullptr;
		}
		return *this;
	}

	template<class T>
	inline Array<T>& Array<T>::operator=(List<T>&& Right) noexcept
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
		}

		_Length = Right._Capacity;
		_Data = Right._Data;

		Right._Count = 0;
		Right._Capacity = 0;
		Right._Data = nullptr;
		
		return *this;
	}

	template<class T>
	inline T& Array<T>::operator[](const Elysium::Core::size Index)
	{
		if (Index >= _Length)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<class T>
	inline const T& Array<T>::operator[](const Elysium::Core::size Index) const
	{
		if (Index >= _Length)
		{
			throw IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<class T>
	inline const Elysium::Core::size Array<T>::GetLength() const
	{
		return _Length;
	}

	template<class T>
	inline void Array<T>::Clear(T* Array, const Elysium::Core::size Length)
	{
		memset(Array, 0, Length);
	}

	template<class T>
	inline void Array<T>::Copy(const T* Source, T* Destination, const Elysium::Core::size Length)
	{
		for (Elysium::Core::size i = 0; i < Length; i++)
		{
			Destination[i] = Source[i];
		}
	}
	template<class T>
	inline void Array<T>::Move(T* Source, T* Destination, const Elysium::Core::size Length)
	{
		for (Elysium::Core::size i = 0; i < Length; i++)
		{
			Destination[i] = Elysium::Core::Template::Functional::Move(Source[i]);
		}
	}

	template<class T>
	inline void Array<T>::Reverse(Array<T>& Array)
	{
		Elysium::Core::Template::Functional::Reverse(Array._Data, &Array._Data[Array.GetLength() - 1]);
	}
}
#endif
