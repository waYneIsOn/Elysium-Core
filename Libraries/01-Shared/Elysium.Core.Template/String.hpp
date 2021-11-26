/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#define ELYSIUM_CORE_TEMPLATE_TEXT_STRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C, class Allocator = Memory::DefaultAllocator<C>>
	class StringBase final
	{
	public:
		using ConstCharacter = const C;
		using CharPointer = C*;
		using ConstCharPointer = const C*;
	private:
		struct HeapString final
		{
			CharPointer _Data; // 4/8 bytes
			Elysium::Core::size _Size; // 4/8 bytes
			Elysium::Core::size _CapacityAndFlag; // 4/8 bytes -> 1 bit flag (stack/heap allocated) + 31/63 bit capacity

			Elysium::Core::size GetCapacity() const noexcept;

			void SetCapacity(const Elysium::Core::size Value) noexcept;
		};	// 12/24 bytes

		struct StackString final
		{
			Elysium::Core::byte _Data[sizeof(HeapString) - sizeof(Elysium::Core::byte)]; // 11/23 bytes
			Elysium::Core::byte _RemainingBytesAndFlag;	// 1 byte -> 1 bit flag (stack/heap allocated) + 7 bit remaining size

			Elysium::Core::size GetSize() const noexcept;

			void SetSize(const Elysium::Core::size Value) noexcept;
		};	// 12/24 bytes
	public:
		StringBase() noexcept;

		StringBase(ConstCharPointer Value) noexcept;

		StringBase(ConstCharPointer Value, const Elysium::Core::size Size) noexcept;

		StringBase(const Elysium::Core::size Size) noexcept;

		StringBase(const StringBase& Source);

		StringBase(StringBase&& Right) noexcept;

		~StringBase();
	public:
		StringBase<C, Allocator>& operator=(ConstCharPointer Value) = delete;

		StringBase<C, Allocator>& operator=(const StringBase& Source);

		StringBase<C, Allocator>& operator=(StringBase&& Right) noexcept;
	public:
		static constexpr const bool IsEmpty(const StringBase& Value);
	public:
		const Elysium::Core::size GetSize() const;

		const Elysium::Core::size GetCapacity() const;
	public:
		//const Elysium::Core::size GetHashCode() const;

		StringBase<C, Allocator>::CharPointer ToCharArray();

		StringBase<C, Allocator>::ConstCharPointer ToCharArray() const;
	private:
		void CopyHeapString(ConstCharPointer Value, const Elysium::Core::size CharSize);

		void CopyStackString(ConstCharPointer Value, const Elysium::Core::size ByteSize);

		const bool IsHeapAllocated() const;

		void DeleteHeapString();
	public:
		inline static constexpr const Elysium::Core::uint8_t MaximumByteSizeOnStack = sizeof(HeapString) - 1;
		inline static constexpr const Elysium::Core::uint8_t MaximumCharSizeOnStack = MaximumByteSizeOnStack / sizeof(C);
		 
		inline static constexpr const Elysium::Core::size MaximumByteSizeOnHeap = static_cast<Elysium::Core::size>(-1) / 2;
		inline static constexpr const Elysium::Core::size MaximumCharSizeOnHeap = MaximumByteSizeOnHeap / sizeof(C);
	private:
		inline static Allocator _Allocator = Allocator();

		inline static constexpr const Elysium::Core::size _HeapStackFlagShift = (sizeof(Elysium::Core::size) - 1) * 8;
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		inline static constexpr const Elysium::Core::size _HeapStackFlagMask = 0x01;
		inline static constexpr const Elysium::Core::size _CapacityExtractMask = ~(Elysium::Core::size(_HeapStackFlagMask) << _HeapStackFlagShift);
#else
		// ...
#endif
	private:
		union
		{
			HeapString _Heap;
			StackString _Stack;
		} _InternalString;
	};

	template<Concepts::Character C, class Allocator>
	inline Elysium::Core::size StringBase<C, Allocator>::HeapString::GetCapacity() const noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return _CapacityAndFlag & _CapacityExtractMask;
#else
		throw 1;
#endif
	}

	template<Concepts::Character C, class Allocator>
	inline void StringBase<C, Allocator>::HeapString::SetCapacity(const Elysium::Core::size Value) noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		// most right bit of first byte (0000 000x) is stack/heap-flag
		_CapacityAndFlag = _HeapStackFlagMask << _HeapStackFlagShift |	// make sure stack-flag is set to one
			Value;
#else
		throw 1;
#endif
	}

	template<Concepts::Character C, class Allocator>
	inline Elysium::Core::size StringBase<C, Allocator>::StackString::GetSize() const noexcept
	{	// most right bit (0000 000x) is stack/heap-flag, all other bits represent the remaining bytes
		return sizeof(HeapString) - 1 - (_RemainingBytesAndFlag >> 1);
	}

	template<Concepts::Character C, class Allocator>
	inline void StringBase<C, Allocator>::StackString::SetSize(const Elysium::Core::size Value) noexcept
	{	// seven most left bits represent the remaining bytes, most right bit represents stack-bitflag (0000 000F)
		_RemainingBytesAndFlag = 0x00 |	// make sure stack-flag is set to zero
			static_cast<Elysium::Core::byte>(((sizeof(HeapString) - 1 - Value) << 1));
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::StringBase() noexcept
		: StringBase<C, Allocator>(nullptr, 0)
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::StringBase(ConstCharPointer Value) noexcept
		: StringBase<C, Allocator>(Value, CharacterTraits<C>::GetLength(Value))
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::StringBase(ConstCharPointer Value, const Elysium::Core::size Size) noexcept
		: _InternalString{ 0x00 }
	{
		const Elysium::Core::size ValueByteSize = Size * sizeof(C);
		const Elysium::Core::size ValueByteSizeIncludingNullTerminator = ValueByteSize + sizeof(C);
		if (ValueByteSizeIncludingNullTerminator > MaximumByteSizeOnHeap)
		{
			// what to do? does this even occurre? linked list?
		}
		else if (ValueByteSizeIncludingNullTerminator > MaximumByteSizeOnStack)
		{
			CopyHeapString(Value, Size);
		}
		else
		{
			CopyStackString(Value, ValueByteSize);
		}
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::StringBase(const Elysium::Core::size Size) noexcept
		: _InternalString{ 0x00 }
	{
		const Elysium::Core::size ByteSizeIncludingNullTerminator = Size * sizeof(C) + sizeof(C);
		if (ByteSizeIncludingNullTerminator > MaximumByteSizeOnHeap)
		{
			// what to do? does this even occurre? linked list?
		}
		else if (ByteSizeIncludingNullTerminator > MaximumByteSizeOnStack)
		{
			_InternalString._Heap._Data = _Allocator.Allocate(Size + 1);
			_InternalString._Heap._Size = 0;
			_InternalString._Heap.SetCapacity(Size);
		}
		else
		{
			_InternalString._Stack.SetSize(0);
		}
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::StringBase(const StringBase& Source)
		: _InternalString{ 0x00 }
	{
		if (Source.IsHeapAllocated())
		{
			CopyHeapString(Source._InternalString._Heap._Data, Source.GetSize());
		}
		else
		{
#pragma warning (disable: 6385 6386)	// I want to copy 12/24 bytes
			memcpy(&_InternalString._Stack._Data[0], &Source._InternalString._Stack._Data[0], sizeof(StackString));
#pragma warning (default: 6385 6386)
		}
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::StringBase(StringBase&& Right) noexcept
		: _InternalString{ 0x00 }
	{
#pragma warning (disable: 6385 6386)	// I want to copy and set 12/24 bytes
		memcpy(&_InternalString._Stack._Data[0], &Right._InternalString._Stack._Data[0], sizeof(StackString));
		memset(&Right._InternalString._Stack._Data[0], 0x00, sizeof(StackString));
#pragma warning (default: 6385 6386)
		Right._InternalString._Stack.SetSize(0);
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::~StringBase()
	{
		DeleteHeapString();
	}
	/*
	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>& StringBase<C, Allocator>::operator=(ConstCharPointer Value)
	{
		const Elysium::Core::size ValueSize = StringTraits<C>::GetLength(Value);
		const Elysium::Core::size ValueByteSize = ValueSize * sizeof(C);
		const Elysium::Core::size ByteSizeIncludingNullTerminator = ValueByteSize + sizeof(C);
		if (ByteSizeIncludingNullTerminator > MaximumByteSizeOnHeap)
		{
			// what to do? does this even occurre? linked list?
		}
		else if (ByteSizeIncludingNullTerminator > MaximumByteSizeOnStack)
		{

		}
		else
		{

		}

		return *this;
	}
	*/
	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>& StringBase<C, Allocator>::operator=(const StringBase& Source)
	{
		if (this != &Source)
		{
			const bool IsThisHeapAllocated = IsHeapAllocated();
			const bool IsSourceHeapAllocated = Source.IsHeapAllocated();

			if (IsThisHeapAllocated && IsSourceHeapAllocated)
			{	// heap to heap
				const Elysium::Core::size SourceCharSize = Source.GetSize();
				const Elysium::Core::size SourceCharSizeIncludingNullTerminationCharacter = SourceCharSize + 1;
				if (SourceCharSizeIncludingNullTerminationCharacter > GetCapacity())
				{	// source doesn't fit into this string
					DeleteHeapString();
					CopyHeapString(Source._InternalString._Heap._Data, SourceCharSize);
				}
				else
				{	// source fits into this string
					const Elysium::Core::size SourceByteSizeIncludingNullTerminationCharacter = SourceCharSize * sizeof(C) + sizeof(C);
					memcpy(&_InternalString._Heap._Data[0], &Source._InternalString._Heap._Data[0], SourceByteSizeIncludingNullTerminationCharacter);
					_InternalString._Heap._Size = SourceCharSize;
				}
			}
			else if (!IsThisHeapAllocated && !IsSourceHeapAllocated)
			{	// stack to stack
#pragma warning (disable: 6385 6386)	// I want to copy 12/24 bytes
				memcpy(&_InternalString._Stack._Data[0], &Source._InternalString._Stack._Data[0], sizeof(StackString));
#pragma warning (default: 6385 6386)
			}
			else if (!IsThisHeapAllocated && IsSourceHeapAllocated)
			{	// heap to stack
				CopyHeapString(Source._InternalString._Heap._Data, Source.GetSize());
			}
			else
			{	// stack to heap
				DeleteHeapString();
#pragma warning (disable: 6385 6386)	// I want to copy 12/24 bytes
				memcpy(&_InternalString._Stack._Data[0], &Source._InternalString._Stack._Data[0], sizeof(StackString));
#pragma warning (default: 6385 6386)
			}
		}
		return *this;
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>& StringBase<C, Allocator>::operator=(StringBase&& Right) noexcept
	{
		if (this != &Right)
		{
			if (IsHeapAllocated())
			{
				DeleteHeapString();
			}

#pragma warning (disable: 6385 6386)	// I want to copy and set 12/24 bytes
			memcpy(&_InternalString._Stack._Data[0], &Right._InternalString._Stack._Data[0], sizeof(StackString));
			memset(&Right._InternalString._Stack._Data[0], 0x00, sizeof(StackString));
#pragma warning (default: 6385 6386)
			Right._InternalString._Stack.SetSize(0);
		}
		return *this;
	}

	template<Concepts::Character C, class Allocator>
	inline constexpr const bool StringBase<C, Allocator>::IsEmpty(const StringBase& Value)
	{
		return CharacterTraits<C>::IsEmpty(Value.ToCharArray());
	}

	template<Concepts::Character C, class Allocator>
	inline const Elysium::Core::size StringBase<C, Allocator>::GetSize() const
	{
		return IsHeapAllocated() ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
	}

	template<Concepts::Character C, class Allocator>
	inline const Elysium::Core::size StringBase<C, Allocator>::GetCapacity() const
	{
		return IsHeapAllocated() ? _InternalString._Heap.GetCapacity() : MaximumByteSizeOnStack / sizeof(C);
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::CharPointer StringBase<C, Allocator>::ToCharArray()
	{
		if (IsHeapAllocated())
		{
			return _InternalString._Heap._Data;
		}
		else
		{
			return (ConstCharPointer)&_InternalString._Stack._Data;
		}
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::ConstCharPointer StringBase<C, Allocator>::ToCharArray() const
	{
		if (IsHeapAllocated())
		{
			return _InternalString._Heap._Data;
		}
		else
		{
			return (ConstCharPointer)&_InternalString._Stack._Data;
		}
	}

	template<Concepts::Character C, class Allocator>
	inline void StringBase<C, Allocator>::CopyHeapString(ConstCharPointer Value, const Elysium::Core::size CharSize)
	{
		const Elysium::Core::size SizeIncludingNullTerminationCharacter = CharSize + 1;

		_InternalString._Heap._Data = _Allocator.Allocate(SizeIncludingNullTerminationCharacter);
		memcpy(&_InternalString._Heap._Data[0], Value, SizeIncludingNullTerminationCharacter);

		_InternalString._Heap._Size = CharSize;
		_InternalString._Heap.SetCapacity(CharSize);
	}

	template<Concepts::Character C, class Allocator>
	inline void StringBase<C, Allocator>::CopyStackString(ConstCharPointer Value, const Elysium::Core::size ByteSize)
	{
		memcpy(&_InternalString._Stack._Data[0], Value, ByteSize);
		_InternalString._Stack.SetSize(ByteSize);
	}

	template<Concepts::Character C, class Allocator>
	inline const bool StringBase<C, Allocator>::IsHeapAllocated() const
	{	// most right bit (0000 000x)
		return (_InternalString._Stack._RemainingBytesAndFlag & _HeapStackFlagMask) == _HeapStackFlagMask;
	}

	template<Concepts::Character C, class Allocator>
	inline void StringBase<C, Allocator>::DeleteHeapString()
	{
		if (IsHeapAllocated())
		{
			if (_InternalString._Heap._Data != nullptr)
			{
				_Allocator.Deallocate(_InternalString._Heap._Data, 0);
				_InternalString._Heap._Data = nullptr;
			}
		}
	}

	using String = StringBase<char>;
	using WideString = StringBase<wchar_t>;
	using Utf8String = StringBase<char8_t>;
	using Utf16String = StringBase<char16_t>;
	using Utf32String = StringBase<char32_t>;
}
#endif
