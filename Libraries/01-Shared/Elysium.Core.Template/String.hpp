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

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGTRAITS
#include "StringTraits.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C, class Allocator = Memory::DefaultAllocator<C>>
	class StringBase
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
		inline static constexpr const Elysium::Core::uint8_t MaximumByteSizeOnStack = sizeof(HeapString) - 1;
		inline static constexpr const Elysium::Core::uint8_t MaximumCharSizeOnStack = MaximumByteSizeOnStack / sizeof(C);

		inline static constexpr const Elysium::Core::size MaximumByteSizeOnHeap = -1_ui64 / 2;
		inline static constexpr const Elysium::Core::size MaximumCharSizeOnHeap = MaximumByteSizeOnHeap / sizeof(C);
	public:
		StringBase() noexcept;

		StringBase(ConstCharPointer Value) noexcept;

		StringBase(ConstCharPointer Value, const Elysium::Core::size Size) noexcept;

		StringBase(const Elysium::Core::size Size) noexcept;

		StringBase(const StringBase& Source);

		StringBase(StringBase&& Right) noexcept;

		~StringBase();
	public:
		StringBase<C, Allocator>& operator=(const StringBase& Source);

		StringBase<C, Allocator>& operator=(StringBase&& Right) noexcept = delete;

		StringBase<C, Allocator>& operator=(ConstCharPointer Value) = delete;
	public:
		//static const bool IsEmpty(const StringBase& Value);
	public:
		const Elysium::Core::size GetSize() const;

		const Elysium::Core::size GetCapacity() const;
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
	private:
		void CopyHeapString(ConstCharPointer Value, const Elysium::Core::size ByteSize);

		void CopyStackString(ConstCharPointer Value, const Elysium::Core::size ByteSize);

		const bool IsHeapAllocated() const;

		void DeleteHeapString();
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
		// most right bit of last byte (0000 0000 - ... - 0000 000x) is stack/heap-flag
		_CapacityAndFlag = 0x01_ui64 << _HeapStackFlagShift |	// make sure stack-flag is set to one
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
		: StringBase<C, Allocator>(Value, StringTraits<C>::GetLength(Value))
	{ }

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::StringBase(ConstCharPointer Value, const Elysium::Core::size Size) noexcept
		: _InternalString{ 0x00 }
	{
		const Elysium::Core::size ValueByteSize = Size * sizeof(C);
		if (ValueByteSize > MaximumByteSizeOnStack)
		{
			CopyHeapString(Value, ValueByteSize);
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
		const Elysium::Core::size ByteSize = Size * sizeof(C);
		if (ByteSize > MaximumByteSizeOnStack)
		{
			const Elysium::Core::size ByteSizeIncludingNullTerminationCharacter = ByteSize + sizeof(C);
			_InternalString._Heap._Data = _Allocator.Allocate(ByteSizeIncludingNullTerminationCharacter);
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
			const Elysium::Core::size ValueByteSize = Source.GetSize() * sizeof(C);
			CopyHeapString(Source._InternalString._Heap._Data, ValueByteSize);
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
		if (!Right.IsHeapAllocated())
		{
			Right._InternalString._Stack.SetSize(0);
		}
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::~StringBase()
	{
		DeleteHeapString();
	}

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
				const Elysium::Core::size SourceCharSizeIncludingNullTerminationCharacter = SourceCharSize + sizeof(C);
				const Elysium::Core::size SourceByteSize = SourceCharSize * sizeof(C);
				if (SourceCharSizeIncludingNullTerminationCharacter > GetCapacity())
				{	// source doesn't fit into this string
					DeleteHeapString();
					CopyHeapString(Source._InternalString._Heap._Data, SourceByteSize);
				}
				else
				{	// source fits into this string
					const Elysium::Core::size SourceByteSizeIncludingNullTerminationCharacter = SourceByteSize + sizeof(C);					
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
				const Elysium::Core::size ValueByteLength = Source.GetSize() * sizeof(C);
				CopyHeapString(Source._InternalString._Heap._Data, ValueByteLength);
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
	inline void StringBase<C, Allocator>::CopyHeapString(ConstCharPointer Value, const Elysium::Core::size ByteSize)
	{
		const Elysium::Core::size ByteSizeIncludingNullTerminationCharacter = ByteSize + sizeof(C);

		_InternalString._Heap._Data = _Allocator.Allocate(ByteSizeIncludingNullTerminationCharacter);
		memcpy(&_InternalString._Heap._Data[0], Value, ByteSizeIncludingNullTerminationCharacter);

		const Elysium::Core::size Size = ByteSize / sizeof(C);
		_InternalString._Heap._Size = Size;
		_InternalString._Heap.SetCapacity(Size);
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
