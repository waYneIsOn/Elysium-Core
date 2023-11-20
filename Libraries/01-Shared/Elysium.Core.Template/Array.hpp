/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INDEXOUTOFRANGEEXCEPTION
#include "IndexOutOfRangeException.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// 
	/// </summary>
	template <Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	class Array
	{
	public:
		using Value = T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;

		using IteratorPointer = T*;
		using IteratorReference = T&;
		using ConstIteratorReference = const T&;

		using FIterator = Iterator::ForwardIterator<Array<T, Length>>;
		using ConstIterator = Iterator::ConstForwardIterator<Array<T, Length>>;

		using ReverseIterator = Iterator::BackwardIterator<Array<T, Length>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<Array<T, Length>>;
	public:
		Array();

		Array(const InitializerList<T>& InitializerList);

		Array(const Array& Source);

		Array(Array&& Right) noexcept;

		~Array();
	public:
		Array<T, Length>& operator=(const Array& Source);

		Array<T, Length>& operator=(Array&& Right) noexcept;
	public:
		Array<T, Length>::Reference operator[](const System::size Index);

		Array<T, Length>::ConstReference operator[](const System::size Index) const;
	public:
		constexpr const Elysium::Core::Template::System::size GetLength() const noexcept;

		constexpr Reference GetAt(const Elysium::Core::Template::System::size Index);

		constexpr ConstReference GetAt(const Elysium::Core::Template::System::size Index) const;

		constexpr Reference GetFront();

		constexpr ConstReference GetFront() const;

		constexpr Reference GetBack();

		constexpr ConstReference GetBack() const;

		constexpr Pointer GetData() noexcept;

		constexpr ConstPointer GetData() const noexcept;
	public:
		FIterator GetBegin();

		ConstIterator GetBegin() const;

		FIterator GetEnd();

		ConstIterator GetEnd() const;

		ReverseIterator GetReverseBegin();

		ConstReverseIterator GetReverseBegin() const;

		ReverseIterator GetReverseEnd();

		ConstReverseIterator GetReverseEnd() const;
	private:
		T _Data[Length];
	};

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Elysium::Core::Template::Container::Array<T, Length>::Array()
		: _Data()
	{ }

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Elysium::Core::Template::Container::Array<T, Length>::Array(const InitializerList<T>& InitializerList)
		: _Data()
	{
		const Elysium::Core::Template::System::size CopyLength = Length < InitializerList.size() ? Length : InitializerList.size();
		for (Elysium::Core::Template::System::size i = 0; i < CopyLength; i++)
		{
			_Data[i] = InitializerList.begin()[i];
		}
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Elysium::Core::Template::Container::Array<T, Length>::Array(const Array& Source)
		: _Data()
	{
		for (Elysium::Core::Template::System::size i = 0; i < Length; i++)
		{
			_Data[i] = Source._Data[i];
		}
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Elysium::Core::Template::Container::Array<T, Length>::Array(Array&& Right) noexcept
		: _Data()
	{
		*this = Functional::Move(Right);
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Elysium::Core::Template::Container::Array<T, Length>::~Array()
	{ }

	template<Concepts::NonConstant T, const Elysium::Core::Template::System::size Length>
	inline Array<T, Length>& Array<T, Length>::operator=(const Array& Source)
	{
		if (this != &Source)
		{
			for (Elysium::Core::Template::System::size i = 0; i < Length; i++)
			{
				_Data[i] = Source._Data[i];
			}
		}
		return *this;
	}

	template<Concepts::NonConstant T, const Elysium::Core::Template::System::size Length>
	inline Array<T, Length>& Array<T, Length>::operator=(Array&& Right) noexcept
	{
		if (this != &Right)
		{
			for (Elysium::Core::Template::System::size i = 0; i < Length; i++)
			{
				_Data[i] = Functional::Move(Right._Data[i]);
			}
		}
		return *this;
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::Reference Array<T, Length>::operator[](const Elysium::Core::Template::System::size Index)
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::ConstReference Array<T, Length>::operator[](const Elysium::Core::Template::System::size Index) const
	{
		return _Data[Index];
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline constexpr const Elysium::Core::Template::System::size Array<T, Length>::GetLength() const noexcept
	{
		return Length;
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline constexpr Array<T, Length>::Reference Elysium::Core::Template::Container::Array<T, Length>::GetAt(const Elysium::Core::Template::System::size Index)
	{
		if (Index >= Length)
		{
			throw Elysium::Core::Template::Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline constexpr Array<T, Length>::ConstReference Elysium::Core::Template::Container::Array<T, Length>::GetAt(const Elysium::Core::Template::System::size Index) const
	{
		if (Index >= Length)
		{
			throw Elysium::Core::Template::Exceptions::IndexOutOfRangeException();
		}

		return _Data[Index];
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline constexpr Array<T, Length>::Reference Array<T, Length>::GetFront()
	{
		return _Data[0];
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline constexpr Array<T, Length>::ConstReference Array<T, Length>::GetFront() const
	{
		return _Data[0];
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline constexpr Array<T, Length>::Reference Array<T, Length>::GetBack()
	{
		return _Data[Length - 1];
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline constexpr Array<T, Length>::ConstReference Array<T, Length>::GetBack() const
	{
		return _Data[Length - 1];
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline constexpr Array<T, Length>::Pointer Array<T, Length>::GetData() noexcept
	{
		return &_Data;
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline constexpr Array<T, Length>::ConstPointer Elysium::Core::Template::Container::Array<T, Length>::GetData() const noexcept
	{
		return &_Data;
	}
	
	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::FIterator Elysium::Core::Template::Container::Array<T, Length>::GetBegin()
	{
		return FIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::ConstIterator Elysium::Core::Template::Container::Array<T, Length>::GetBegin() const
	{
		return ConstIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::FIterator Elysium::Core::Template::Container::Array<T, Length>::GetEnd()
	{
		return FIterator(&_Data[Length - 1]);
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::ConstIterator Elysium::Core::Template::Container::Array<T, Length>::GetEnd() const
	{
		return ConstIterator(&_Data[Length - 1]);
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::ReverseIterator Elysium::Core::Template::Container::Array<T, Length>::GetReverseBegin()
	{
		return ReverseIterator(&_Data[Length - 1]);
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::ConstReverseIterator Elysium::Core::Template::Container::Array<T, Length>::GetReverseBegin() const
	{
		return ConstReverseIterator(&_Data[Length - 1]);
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::ReverseIterator Elysium::Core::Template::Container::Array<T, Length>::GetReverseEnd()
	{
		return ReverseIterator(&_Data[0]);
	}

	template<Concepts::NonConstant T, Elysium::Core::Template::System::size Length>
	inline Array<T, Length>::ConstReverseIterator Elysium::Core::Template::Container::Array<T, Length>::GetReverseEnd() const
	{
		return ConstReverseIterator(&_Data[0]);
	}
	
	template <Elysium::Core::Template::System::size Length>
	class Array<bool, Length>
	{ };
}
#endif
