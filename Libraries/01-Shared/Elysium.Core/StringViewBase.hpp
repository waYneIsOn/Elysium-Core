/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_STRINGVIEWBASE
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_STRINGVIEWBASE

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_STRINGBASE
#include "StringBase.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class StringViewBase final
	{
	public:
		StringViewBase();
		StringViewBase(T* Input);
		StringViewBase(T* Input, size_t Length);
		StringViewBase(const StringBase<T>& Input);
		StringViewBase(const StringBase<T>& Input, size_t Length);
		StringViewBase(const StringBase<T>& Input, size_t Offset, size_t Length);
		StringViewBase(const StringViewBase& Source);
		StringViewBase(StringViewBase&& Right) noexcept;
		~StringViewBase();

		StringViewBase<T>& operator=(const StringViewBase<T>& Source);
		StringViewBase<T>& operator=(StringViewBase<T>&& Right) noexcept;

		T& operator[](size_t Index) const;

		operator StringBase<T>() const;

		bool operator==(const StringViewBase<T>& Other) const;
		bool operator!=(const StringViewBase<T>& Other) const;
		bool operator<(const StringViewBase<T>& Other) const;
		bool operator>(const StringViewBase<T>& Other) const;
		bool operator<=(const StringViewBase<T>& Other) const;
		bool operator>=(const StringViewBase<T>& Other) const;

		const size_t GetLength() const;

		size_t IndexOf(const T Value) const;
		size_t IndexOf(const T Value, const size_t StartIndex) const;
		size_t IndexOf(const T* Value) const;
		size_t IndexOf(const T* Value, const size_t StartIndex) const;
		size_t IndexOf(const StringBase<T>& Value, const size_t StartIndex) const;

		void Split(const T Delimiter, List<StringViewBase<T>>& Views) const;
		void Split(const T* Delimiter,List<StringViewBase<T>>& Views) const;
	private:
		size_t _Length;
		T* _Data;

		inline static T _NullTerminationChar = (T)0x00;
	};

	template<typename T>
	inline StringViewBase<T>::StringViewBase()
		: _Length(0), _Data(nullptr)
	{ }
	template<typename T>
	inline StringViewBase<T>::StringViewBase(T * Input)
		: _Length(std::char_traits<T>::length(Input)), _Data(Input)
	{ }
	template<typename T>
	inline StringViewBase<T>::StringViewBase(T * Input, size_t Length)
		: _Length(Length), _Data(Input)
	{ }
	template<typename T>
	inline StringViewBase<T>::StringViewBase(const StringBase<T> & Input)
		: _Length(Input.GetLength()), _Data(&Input[0])
	{ }
	template<typename T>
	inline StringViewBase<T>::StringViewBase(const StringBase<T> & Input, size_t Length)
		: _Length(Length), _Data(&Input[0])
	{ }
	template<typename T>
	inline StringViewBase<T>::StringViewBase(const StringBase<T> & Input, size_t Offset, size_t Length)
		: _Length(Length), _Data(&Input[Offset])
	{ }
	template<typename T>
	inline StringViewBase<T>::StringViewBase(const StringViewBase & Source)
		: _Length(Source._Length), _Data(Source._Data)
	{ }
	template<typename T>
	inline StringViewBase<T>::StringViewBase(StringViewBase && Right) noexcept
		: _Length(0), _Data(nullptr)
	{
		*this = std::move(Right);
	}
	template<typename T>
	inline StringViewBase<T>::~StringViewBase()
	{
	}

	template<typename T>
	inline StringViewBase<T> & StringViewBase<T>::operator=(const StringViewBase<T> & Source)
	{
		if (this != &Source)
		{
			_Length = Source._Length;
			_Data = Source._Data;
		}
		return *this;
	}
	template<typename T>
	inline StringViewBase<T> & StringViewBase<T>::operator=(StringViewBase<T> && Right) noexcept
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

	template<typename T>
	inline T & StringViewBase<T>::operator[](size_t Index) const
	{
		if (Index > _Length)
		{
			return _NullTerminationChar;
		}
		return _Data[Index];
	}

	template<typename T>
	inline StringViewBase<T>::operator StringBase<T>() const
	{
		return StringBase<T>(_Data, _Length);
	}

	template<typename T>
	inline bool StringViewBase<T>::operator==(const StringViewBase<T>& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		return _Data == Other._Data && _Length == Other._Length;
	}
	template<typename T>
	inline bool StringViewBase<T>::operator!=(const StringViewBase<T>& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		return _Data != Other._Data || _Length != Other._Length;
	}
	template<typename T>
	inline bool StringViewBase<T>::operator<(const StringViewBase<T>& Other) const
	{
		return _Data == Other._Data && _Length < Other._Length;
	}
	template<typename T>
	inline bool StringViewBase<T>::operator>(const StringViewBase<T>& Other) const
	{
		return _Data == Other._Data && _Length > Other._Length;
	}
	template<typename T>
	inline bool StringViewBase<T>::operator<=(const StringViewBase<T>& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		return _Data == Other._Data && _Length <= Other._Length;
	}
	template<typename T>
	inline bool StringViewBase<T>::operator>=(const StringViewBase<T>& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		return _Data == Other._Data && _Length >= Other._Length;
	}

	template<typename T>
	inline const size_t StringViewBase<T>::GetLength() const
	{
		return _Length;
	}

	template<typename T>
	inline size_t StringViewBase<T>::IndexOf(const T Value) const
	{
		const T* CharPointer = std::char_traits<T>::find(_Data, _Length, Value);
		return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - _Data;
	}
	template<typename T>
	inline size_t StringViewBase<T>::IndexOf(const T Value, const size_t StartIndex) const
	{
		const T* CharPointer = std::char_traits<T>::find(&_Data[StartIndex], _Length - StartIndex, Value);
		return CharPointer == nullptr ? static_cast<size_t>(-1) : CharPointer - &_Data[StartIndex];
	}
	template<typename T>
	inline size_t StringViewBase<T>::IndexOf(const T * Value) const
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
	inline size_t StringViewBase<T>::IndexOf(const T * Value, const size_t StartIndex) const
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
	inline size_t StringViewBase<T>::IndexOf(const StringBase<T>& Value, const size_t StartIndex) const
	{
		return IndexOf(Value[StartIndex]);
	}

	template<typename T>
	inline void StringViewBase<T>::Split(const T Delimiter, List<StringViewBase<T>>& Views) const
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
					Views.Add(StringViewBase<T>(&_Data[StartIndex], _Length - StartIndex));
				}
				break;
			}
			Views.Add(StringViewBase<T>(&_Data[StartIndex], Length));
			StartIndex += Length + 1;
		}
	}
	template<typename T>
	inline void StringViewBase<T>::Split(const T * Delimiter, List<StringViewBase<T>>& Views) const
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
					Views.Add(StringViewBase<T>(&_Data[StartIndex], _Length - StartIndex));
				}
				break;
			}
			Views.Add(StringViewBase<T>(&_Data[StartIndex], Length - StartIndex));
			StartIndex += (Length - StartIndex) + DelimiterLength;
		}
	}
}
#endif
