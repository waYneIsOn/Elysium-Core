/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_STACKARRAY
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_STACKARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "../Elysium.Core/IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_BACKWARDITERATOR
#include "BackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTBACKWARDITERATOR
#include "ConstBackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTFORWARDITERATOR
#include "ConstForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_FORWARDITERATOR
#include "ForwardIterator.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Size"></typeparam>
	template <Concepts::NonConstant T, const Elysium::Core::size Size>
	class StackArray final
	{
		static_assert(Size > 0, "Size must be a positive number.");
	public:
		using ConstPointer = const T*;

		using Reference = T&;
		using ConstReference = const T&;

		using IteratorPointer = T*;
		using IteratorReference = T&;
		using ConstIteratorReference = const T&;

		using FIterator = Iterator::ForwardIterator<StackArray<T, Size>>;
		using ConstIterator = Iterator::ConstForwardIterator<StackArray<T, Size>>;

		using ReverseIterator = Iterator::BackwardIterator<StackArray<T, Size>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<StackArray<T, Size>>;
	public:
		StackArray() noexcept;

		StackArray(const StackArray& Source);

		StackArray(StackArray&& Right) noexcept;

		~StackArray();
	public:
		StackArray<T, Size>& operator=(const StackArray& Source);

		StackArray<T, Size>& operator=(StackArray&& Right) noexcept;

		StackArray<T, Size>::Reference operator[](const Elysium::Core::size Index);

		StackArray<T, Size>::ConstReference operator[](const Elysium::Core::size Index) const;
	public:
		constexpr const Elysium::Core::size GetSize() const noexcept;

		constexpr StackArray<T, Size>::ConstPointer GetData() const noexcept;

		constexpr StackArray<T, Size>::ConstReference GetAt(const Elysium::Core::size Index) const;

		constexpr const bool Contains(ConstReference Item) const;

		constexpr const Elysium::Core::size IndexOf(ConstReference Item) const;

		constexpr const Elysium::Core::size LastIndexOf(ConstReference Item) const;
	public:
		StackArray<T, Size>::FIterator GetBegin();

		StackArray<T, Size>::ConstIterator GetBegin() const;

		StackArray<T, Size>::FIterator GetEnd();

		StackArray<T, Size>::ConstIterator GetEnd() const;

		StackArray<T, Size>::ReverseIterator GetReverseBegin();

		StackArray<T, Size>::ConstReverseIterator GetReverseBegin() const;

		StackArray<T, Size>::ReverseIterator GetReverseEnd();

		StackArray<T, Size>::ConstReverseIterator GetReverseEnd() const;
	private:
		T _Data[Size] = {};
	};

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::StackArray() noexcept
	{ }

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::StackArray(const StackArray& Source)
	{
		Array<T>::Copy(Source._Data, _Data, Size);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::StackArray(StackArray&& Right) noexcept
	{
		*this = Functional::Move(Right);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::~StackArray()
	{ }

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>& StackArray<T, Size>::operator=(const StackArray& Source)
	{
		if (this != &Source)
		{
			Array<T>::Copy(Source._Data, _Data, Size);
		}
		return *this;
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>& StackArray<T, Size>::operator=(StackArray&& Right) noexcept
	{
		if (this != &Right)
		{
			Array<T>::Move(Right._Data, _Data, Size);
		}
		return *this;
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::Reference StackArray<T, Size>::operator[](const Elysium::Core::size Index)
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::ConstReference StackArray<T, Size>::operator[](const Elysium::Core::size Index) const
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline constexpr const Elysium::Core::size StackArray<T, Size>::GetSize() const noexcept
	{
		return Size;
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline constexpr StackArray<T, Size>::ConstPointer StackArray<T, Size>::GetData() const noexcept
	{
		return &_Data[0];
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline constexpr StackArray<T, Size>::ConstReference StackArray<T, Size>::GetAt(const Elysium::Core::size Index) const
	{
		if (Index >= Size)
		{
			throw Elysium::Core::IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline constexpr const bool StackArray<T, Size>::Contains(ConstReference Item) const
	{
		for (Elysium::Core::size i = 0; i < Size; i++)
		{
			if (_Data[i] == Item)
			{
				return true;
			}
		}
		return false;
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline constexpr const Elysium::Core::size StackArray<T, Size>::IndexOf(ConstReference Item) const
	{
		for (Elysium::Core::size i = 0; i < Size; i++)
		{
			if (_Data[i] == Item)
			{
				return i;
			}
		}

		return static_cast<Elysium::Core::size>(-1);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline constexpr const Elysium::Core::size StackArray<T, Size>::LastIndexOf(ConstReference Item) const
	{
		for (Elysium::Core::size i = Size - 1; i >= 0; i--)
		{
			if (_Data[i] == Item)
			{
				return i;
			}
		}

		return static_cast<Elysium::Core::size>(-1);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::FIterator StackArray<T, Size>::GetBegin()
	{
		return StackArray<T, Size>::FIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::ConstIterator StackArray<T, Size>::GetBegin() const
	{
		return StackArray<T, Size>::ConstIterator((IteratorPointer)&_Data[0]);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::FIterator StackArray<T, Size>::GetEnd()
	{
		return StackArray<T, Size>::FIterator(&_Data[Size - 1]);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::ConstIterator StackArray<T, Size>::GetEnd() const
	{
		return StackArray<T, Size>::ConstIterator((IteratorPointer)&_Data[Size - 1]);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::ReverseIterator StackArray<T, Size>::GetReverseBegin()
	{
		return StackArray<T, Size>::ReverseIterator(&_Data[Size - 1]);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::ConstReverseIterator StackArray<T, Size>::GetReverseBegin() const
	{
		return StackArray<T, Size>::ConstReverseIterator((IteratorPointer)&_Data[Size - 1]);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::ReverseIterator StackArray<T, Size>::GetReverseEnd()
	{
		return StackArray<T, Size>::ReverseIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, Elysium::Core::size Size>
	inline StackArray<T, Size>::ConstReverseIterator StackArray<T, Size>::GetReverseEnd() const
	{
		return StackArray<T, Size>::ConstReverseIterator((IteratorPointer)&_Data[0]);
	}
}
#endif
