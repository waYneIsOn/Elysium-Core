/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DYNAMICSIZEARRAY
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_DYNAMICSIZEARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INDEXOUTOFRANGEEXCEPTION
#include "../Elysium.Core/IndexOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "InitializerList.hpp"
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

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// Represents a fixed-size array with it's size known at runtime.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	template <Concepts::NonConstant T, class Allocator = Memory::DefaultAllocator<T>>
	class DynamicSizeArray final
	{
	public:
		using Value = T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;

		using FIterator = Iterator::ForwardIterator<DynamicSizeArray<T, Allocator>>;
		using ConstIterator = Iterator::ConstForwardIterator<DynamicSizeArray<T, Allocator>>;

		using ReverseIterator = Iterator::BackwardIterator<DynamicSizeArray<T, Allocator>>;
		using ConstReverseIterator = Iterator::ConstBackwardIterator<DynamicSizeArray<T, Allocator>>;
	public:
		DynamicSizeArray(const System::size Length);

		DynamicSizeArray(const InitializerList<T>& InitializerList);

		DynamicSizeArray(const DynamicSizeArray& Source);

		DynamicSizeArray(DynamicSizeArray&& Right) noexcept;

		~DynamicSizeArray();
	public:
		DynamicSizeArray<T, Allocator>& operator=(const DynamicSizeArray& Source);

		DynamicSizeArray<T, Allocator>& operator=(DynamicSizeArray&& Right) noexcept;
	public:
		Reference operator[](const System::size Index);

		ConstReference operator[](const System::size Index) const;
	public:
		static constexpr const System::size GetMaximumLength();

		constexpr const System::size GetLength() const noexcept;

		constexpr ConstPointer GetData() const noexcept;

		Reference GetAt(const System::size Index);

		ConstReference GetAt(const System::size Index) const;
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
		inline static Allocator _Allocator = Allocator();
	private:
		System::size _Length;
		Pointer _Data;
	};

	template<Concepts::NonConstant T, class Allocator>
	inline DynamicSizeArray<T, Allocator>::DynamicSizeArray(const Elysium::Core::Template::System::size Length)
		: _Length(Length), _Data(_Allocator.Allocate(Length))
	{ }

	template<Concepts::NonConstant T, class Allocator>
	inline DynamicSizeArray<T, Allocator>::DynamicSizeArray(const InitializerList<T>& InitializerList)
		: _Length(InitializerList.size()), _Data(_Allocator.Allocate(_Length))
	{
		Array<T>::Copy(InitializerList.begin(), _Data, _Length);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline DynamicSizeArray<T, Allocator>::DynamicSizeArray(const DynamicSizeArray& Source)
		: _Length(Source._Length), _Data(_Allocator.Allocate(_Length))
	{
		Array<T>::Copy(Source._Data, _Data, _Length);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline DynamicSizeArray<T, Allocator>::DynamicSizeArray(DynamicSizeArray&& Right) noexcept
		: _Length(0), _Data(nullptr)
	{
		*this = Functional::Move(Right);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline DynamicSizeArray<T, Allocator>::~DynamicSizeArray()
	{
		_Allocator.Deallocate(_Data, _Length);
	}

	template<Concepts::NonConstant T, class Allocator>
	inline DynamicSizeArray<T, Allocator>& DynamicSizeArray<T, Allocator>::operator=(const DynamicSizeArray& Source)
	{
		if (this != &Source)
		{
			if (Source._Length > _Length)
			{
				_Allocator.Deallocate(_Data, _Length);
				_Length = Source._Length;
				_Data = _Allocator.Allocate(_Length);
			}
			
			//Array<T>::Copy(Source._Data, _Data, Source.Length);
			// memclear?
		}
		return *this;
	}

	template<Concepts::NonConstant T, class Allocator>
	inline DynamicSizeArray<T, Allocator>& DynamicSizeArray<T, Allocator>::operator=(DynamicSizeArray&& Right) noexcept
	{
		if (this != &Right)
		{

		}
		return *this;
	}
}
#endif
