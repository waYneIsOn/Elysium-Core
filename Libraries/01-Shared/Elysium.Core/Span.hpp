/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SPAN
#define ELYSIUM_CORE_SPAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "Array.hpp"
#endif

namespace Elysium::Core
{
	template <typename T>
	class Span final
	{
	public:
		Span(const T& StartElement, const Elysium::Core::uint64_t Length);
		Span(const Span& Source) = delete;
		Span(Span&& Right) noexcept = delete;
		~Span();

		Span& operator=(const Span& Source) = delete;
		Span& operator=(Span&& Right) noexcept = delete;

		T& operator[](const Elysium::Core::uint64_t Index);
		const T& operator[](const Elysium::Core::uint64_t Index) const;

		const Elysium::Core::uint64_t GetLength() const;

		const bool GetIsEmpty() const;

		T& GetPinnableReference();

		const T& GetPinnableReference() const;

		Span<T> Slice(const Elysium::Core::uint64_t Start, const Elysium::Core::uint64_t Length);

		Elysium::Core::Collections::Template::Array<T> ToArray();
	private:
		Elysium::Core::uint64_t _Length;
		T* _Data;
	};

	template<typename T>
	inline Span<T>::Span(const T& StartElement, const Elysium::Core::uint64_t Length)
		: _Length(Length), _Data((T*)&StartElement)
	{ }

	template<typename T>
	inline Span<T>::~Span()
	{ }

	template<typename T>
	inline T& Span<T>::operator[](const Elysium::Core::uint64_t Index)
	{
		if (Index >= _Length)
		{
			throw IndexOutOfRangeException();
		}
		return _Data[Index];
	}

	template<typename T>
	inline const T& Span<T>::operator[](const Elysium::Core::uint64_t Index) const
	{
		if (Index >= _Length)
		{
			throw IndexOutOfRangeException();
		}
		return _Data[Index];
	}

	template<typename T>
	inline const Elysium::Core::uint64_t Span<T>::GetLength() const
	{
		return _Length;
	}

	template<typename T>
	inline const bool Span<T>::GetIsEmpty() const
	{
		return _Length == 0;
	}

	template<typename T>
	inline T& Span<T>::GetPinnableReference()
	{
		return operator[](0);
	}

	template<typename T>
	inline const T& Span<T>::GetPinnableReference() const
	{
		return operator[](0);
	}

	template<typename T>
	inline Span<T> Span<T>::Slice(const Elysium::Core::uint64_t Start, const Elysium::Core::uint64_t Length)
	{
		if (Start >= _Length)
		{
			throw IndexOutOfRangeException();
		}
		// ToDo: start & length

		return Span<T>(&_Data[Start], Length);
	}

	template<typename T>
	inline Elysium::Core::Collections::Template::Array<T> Span<T>::ToArray()
	{	// ToDo:
		throw 1;
	}
}
#endif
