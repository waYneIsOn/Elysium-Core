/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_STRINGBASE
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_STRINGBASE

#ifndef ELYSIUM_CORE_COLLECTIONS_IENUMERABLE
#include "IEnumerable.hpp"
#endif

#ifndef __midl
#include <vcruntime_string.h>
#endif

#ifndef _IOSFWD_
#include <iosfwd>
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class StringBase final
	{
	public:
		StringBase();
		StringBase(const size_t Length);
		StringBase(const T* Value);
		StringBase(const T* Value, const size_t Length);
		StringBase(const StringBase<T>& Source);
		StringBase(StringBase<T>&& Right) noexcept;
		~StringBase();

		StringBase<T>& operator=(const T* Value);
		StringBase<T>& operator=(const StringBase<T>& Source);
		StringBase<T>& operator=(StringBase<T>&& Right) noexcept;

		T& operator[](size_t Index) const;

		bool operator==(const StringBase<T>& Other) const;
		bool operator!=(const StringBase<T>& Other) const;
		bool operator<(const StringBase<T>& Other) const;
		bool operator>(const StringBase<T>& Other) const;
		bool operator<=(const StringBase<T>& Other) const;
		bool operator>=(const StringBase<T>& Other) const;

		const size_t GetLength() const;
		const T* GetCharArray() const;

		size_t IndexOf(const T Value) const;
		size_t IndexOf(const T Value, const size_t StartIndex) const;
		size_t IndexOf(const T* Value) const;
		size_t IndexOf(const T* Value, const size_t StartIndex) const;
		size_t IndexOf(const StringBase<T>& Value, const size_t StartIndex) const;

		void Split(const T Delimiter, List<StringBase<T>>& Target) const;
		void Split(const T* Delimiter, List<StringBase<T>>& Target) const;

		bool StartsWith(const T* Value) const;

		void Substring(size_t StartIndex, StringBase<T>& Result) const;
		void Substring(size_t StartIndex, size_t Length, StringBase<T>& Result) const;

		//void ToLower(StringBase<T>& Result);
		//void ToUpper(StringBase<T>& Result);

		static bool IsNull(const StringBase<T>& Value);
		static bool IsEmpty(const StringBase<T>& Value);
		static bool IsNullOrEmtpy(const StringBase<T>& Value);
	private:
		size_t _Length;
		T* _Data;

		inline static T _NullTerminationChar = (T)0x00;
	};

	template<class T>
	inline StringBase<T>::StringBase()
		: _Length(0), _Data(nullptr)
	{ }
	template<class T>
	inline StringBase<T>::StringBase(const size_t Length)
		: _Length(Length), _Data(new T[_Length + 1])
	{
		_Data[_Length] = _NullTerminationChar;
	}
	template<class T>
	inline StringBase<T>::StringBase(const T * Value)
		: _Length(Value == nullptr ? 0 : std::char_traits<T>::length(Value)),
		_Data(_Length == 0 ? nullptr : new T[_Length + 1])
	{
		if (_Data != nullptr)
		{
			memcpy(_Data, Value, (_Length + 1) * sizeof(T));
		}
	}
	template<class T>
	inline StringBase<T>::StringBase(const T * Value, const size_t Length)
		: _Length(Value == nullptr ? 0 : Length),
		_Data(_Length == 0 ? nullptr : new T[_Length + 1])
	{
		if (_Data != nullptr)
		{
			memcpy(_Data, Value, _Length * sizeof(T));
			_Data[_Length] = _NullTerminationChar;
		}
	}
	template<class T>
	inline StringBase<T>::StringBase(const StringBase<T>& Source)
		: _Length(Source._Length),
		_Data(_Length == 0 ? nullptr : new T[_Length + 1])
	{
		if (_Data != nullptr)
		{
			memcpy(_Data, Source._Data, (_Length + 1) * sizeof(T));
		}
	}
	template<class T>
	inline StringBase<T>::StringBase(StringBase<T>&& Right) noexcept
		: _Length(0), _Data(nullptr)
	{
		*this = std::move(Right);
	}
	template<class T>
	inline StringBase<T>::~StringBase()
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
			_Data = nullptr;
		}
	}

	template<typename T>
	inline StringBase<T> & StringBase<T>::operator=(const T * Value)
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
		}

		_Length = Value == nullptr ? 0 : std::char_traits<T>::length(Value);
		_Data = _Length == 0 ? nullptr : new T[_Length + 1];
		if (_Data != nullptr)
		{
			memcpy(_Data, Value, (_Length + 1) * sizeof(T));
		}
		return *this;
	}
	template<class T>
	inline StringBase<T> & StringBase<T>::operator=(const StringBase<T> & Source)
	{
		if (this != &Source)
		{
			if (_Data != nullptr)
			{
				delete[] _Data;
			}

			_Length = Source._Length;
			_Data = _Length == 0 ? nullptr : new T[_Length + 1];
			if (_Data != nullptr)
			{
				memcpy(_Data, Source._Data, (_Length + 1) * sizeof(T));
			}
		}
		return *this;
	}
	template<typename T>
	inline StringBase<T> & StringBase<T>::operator=(StringBase<T> && Right) noexcept
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

	template<typename T>
	inline T & StringBase<T>::operator[](size_t Index) const
	{
		if (Index > _Length)
		{
			return _NullTerminationChar;
		}
		return _Data[Index];
	}

	template<typename T>
	inline bool StringBase<T>::operator==(const StringBase<T>& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		if (_Length != Other._Length)
		{
			return false;
		}
		return std::char_traits<T>::compare(_Data, Other._Data, Other._Length) == 0;
	}
	template<typename T>
	inline bool StringBase<T>::operator!=(const StringBase<T>& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		return std::char_traits<T>::compare(_Data, Other._Data, Other._Length) != 0;
	}
	template<typename T>
	inline bool StringBase<T>::operator<(const StringBase<T>& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		return std::char_traits<T>::compare(_Data, Other._Data, Other._Length) < 0;
	}
	template<typename T>
	inline bool StringBase<T>::operator>(const StringBase<T>& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		return std::char_traits<T>::compare(_Data, Other._Data, Other._Length) > 0;
	}
	template<typename T>
	inline bool StringBase<T>::operator<=(const StringBase<T>& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		return std::char_traits<T>::compare(_Data, Other._Data, Other._Length) <= 0;
	}
	template<typename T>
	inline bool StringBase<T>::operator>=(const StringBase<T>& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		return std::char_traits<T>::compare(_Data, Other._Data, Other._Length) >= 0;
	}

	template<typename T>
	inline const size_t StringBase<T>::GetLength() const
	{
		return _Length;
	}
	template<typename T>
	inline const T * StringBase<T>::GetCharArray() const
	{
		return _Data;
	}

	template<typename T>
	inline size_t StringBase<T>::IndexOf(const T Value) const
	{
		const T* CharPointer = std::char_traits<T>::find(_Data, _Length, Value);
		return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - _Data;
	}
	template<typename T>
	inline size_t StringBase<T>::IndexOf(const T Value, const size_t StartIndex) const
	{
		const T* CharPointer = std::char_traits<T>::find(&_Data[StartIndex], _Length - StartIndex, Value);
		return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - &_Data[StartIndex];
	}
	template<typename T>
	inline size_t StringBase<T>::IndexOf(const T * Value) const
	{
		size_t Index = 0;
		size_t SizeOfValue = std::char_traits<T>::length(Value);
		while (true)
		{
			size_t CurrentIndex = IndexOf(Value[0], Index);
			if (CurrentIndex == static_cast<size_t>(-1))
			{
				return CurrentIndex;
			}

			Index += CurrentIndex;
			if (Index + SizeOfValue > _Length)
			{
				return static_cast<size_t>(-1);
			}

			bool Found = true;
			for (int i = 1; i < SizeOfValue; i++)
			{
				if (_Data[Index + i] != Value[i])
				{
					Found = false;
					break;
				}
			}

			if (Found)
			{
				return Index;
			}
			Index++;
		}
	}
	template<typename T>
	inline size_t StringBase<T>::IndexOf(const T * Value, const size_t StartIndex) const
	{
		size_t Index = StartIndex;
		size_t SizeOfValue = std::char_traits<T>::length(Value);
		while (true)
		{
			size_t CurrentIndex = IndexOf(Value[0], Index);
			if (CurrentIndex == static_cast<size_t>(-1))
			{
				return CurrentIndex;
			}

			Index += CurrentIndex;
			if (Index + SizeOfValue > _Length)
			{
				return static_cast<size_t>(-1);
			}

			bool Found = true;
			for (int i = 1; i < SizeOfValue; i++)
			{
				if (_Data[Index + i] != Value[i])
				{
					Found = false;
					break;
				}
			}

			if (Found)
			{
				return Index;
			}
			Index++;
		}
	}
	template<typename T>
	inline size_t StringBase<T>::IndexOf(const StringBase<T>& Value, const size_t StartIndex) const
	{
		return IndexOf(Value._Data[StartIndex]);
	}
	
	template<typename T>
	inline void StringBase<T>::Split(const T Delimiter, List<StringBase<T>>& Target) const
	{
		size_t StartIndex = 0;
		size_t Length = 0;

		while (true)
		{
			Length = IndexOf(Delimiter, StartIndex);
			if (Length == static_cast<size_t>(-1))
			{
				if (_Length - StartIndex > 0)
				{
					Target.Add(StringBase<T>(&_Data[StartIndex], _Length - StartIndex));
				}
				break;
			}
			Target.Add(StringBase<T>(&_Data[StartIndex], Length));
			StartIndex += Length + 1;
		}
	}
	template<typename T>
	inline void StringBase<T>::Split(const T * Delimiter, List<StringBase<T>>& Target) const
	{
		size_t DelimiterLength = std::char_traits<T>::length(Delimiter);
		size_t StartIndex = 0;
		size_t Length = 0;

		while (true)
		{
			Length = IndexOf(Delimiter, StartIndex);
			if (Length == static_cast<size_t>(-1))
			{
				if (_Length - StartIndex > 0)
				{
					Target.Add(StringBase<T>(&_Data[StartIndex], _Length - StartIndex));
				}
				break;
			}
			Target.Add(StringBase<T>(&_Data[StartIndex], Length - StartIndex));
			StartIndex += (Length - StartIndex) + DelimiterLength;
		}
	}
	
	template<typename T>
	inline bool StringBase<T>::StartsWith(const T * Value) const
	{
		size_t ValueLength = std::char_traits<T>::length(Value);
		for (size_t i = 0; i < ValueLength; i++)
		{
			if (_Data[i] != Value[i])
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline void StringBase<T>::Substring(size_t StartIndex, StringBase<T>& Result) const
	{
		StringBase<T>::Substring(StartIndex, _Length - StartIndex, Result);
	}
	template<typename T>
	inline void StringBase<T>::Substring(size_t StartIndex, size_t Length, StringBase<T>& Result) const
	{
		if (Result._Data != nullptr)
		{
			delete[] Result._Data;
		}
		Result._Length = Length;
		Result._Data = new T[Result._Length * sizeof(T)];
		memcpy(Result._Data, &_Data[StartIndex], Length * sizeof(T));
		Result._Data[Result._Length] = u'\0';
	}

	template<typename T>
	inline bool StringBase<T>::IsNull(const StringBase<T>& Value)
	{
		return Value._Data == nullptr;
	}
	template<typename T>
	inline bool StringBase<T>::IsEmpty(const StringBase<T>& Value)
	{
		return Value._Data != nullptr && Value._Length == 1;
	}
	template<typename T>
	inline bool StringBase<T>::IsNullOrEmtpy(const StringBase<T>& Value)
	{
		return Value._Data == nullptr || (Value._Data != nullptr && Value._Length == 1);
	}
}
#endif
