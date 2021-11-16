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
		StringBase() noexcept;

		StringBase(ConstCharPointer Value) noexcept;

		StringBase(ConstCharPointer Value, const Elysium::Core::size Length) noexcept;

		StringBase(const StringBase& Source) = delete;

		StringBase(StringBase&& Right) noexcept = delete;

		~StringBase();
	public:
		StringBase<C, Allocator>& operator=(const StringBase& Source) = delete;

		StringBase<C, Allocator>& operator=(StringBase&& Right) noexcept = delete;

		StringBase<C, Allocator>& operator=(ConstCharPointer Value) = delete;
	public:
		//static const bool IsEmpty(const StringBase& Value);
	public:
		const Elysium::Core::size GetSize() const;

		const Elysium::Core::size GetCapacity() const;
	private:
		inline static Allocator _Allocator = Allocator();
		inline static constexpr const Elysium::Core::byte _MaximumByteSizeOnStack = sizeof(HeapString) - 1;
		inline static constexpr const size_t _HeapStackFlagShift = (sizeof(Elysium::Core::size) - 1) * 8;
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
		void CopyHeapString(ConstCharPointer Value, const Elysium::Core::size ByteLength);

		void CopyStackString(ConstCharPointer Value, const Elysium::Core::size ByteLength);

		const bool IsHeapAllocated() const;
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
	inline StringBase<C, Allocator>::StringBase(ConstCharPointer Value, const Elysium::Core::size Length) noexcept
		: _InternalString{ 0x00 }
	{
		const Elysium::Core::size ValueByteLength = Length * sizeof(C);
		if (ValueByteLength > _MaximumByteSizeOnStack)
		{
			CopyHeapString(Value, ValueByteLength);
		}
		else
		{
			CopyStackString(Value, ValueByteLength);
		}
	}

	template<Concepts::Character C, class Allocator>
	inline StringBase<C, Allocator>::~StringBase()
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

	template<Concepts::Character C, class Allocator>
	inline const Elysium::Core::size StringBase<C, Allocator>::GetSize() const
	{
		return IsHeapAllocated() ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
	}

	template<Concepts::Character C, class Allocator>
	inline const Elysium::Core::size StringBase<C, Allocator>::GetCapacity() const
	{
		return IsHeapAllocated() ? _InternalString._Heap.GetCapacity() : _MaximumByteSizeOnStack / sizeof(C);
	}

	template<Concepts::Character C, class Allocator>
	inline void StringBase<C, Allocator>::CopyHeapString(ConstCharPointer Value, const Elysium::Core::size ByteLength)
	{
		const Elysium::Core::size ByteLengthIncludingNullTerminationCharacter = ByteLength + 1;

		_InternalString._Heap._Data = _Allocator.Allocate(ByteLengthIncludingNullTerminationCharacter);
		memcpy(&_InternalString._Heap._Data[0], Value, ByteLengthIncludingNullTerminationCharacter * sizeof(C));

		const Elysium::Core::size Length = ByteLength / sizeof(C);
		_InternalString._Heap._Size = Length;
		_InternalString._Heap.SetCapacity(Length);
	}

	template<Concepts::Character C, class Allocator>
	inline void StringBase<C, Allocator>::CopyStackString(ConstCharPointer Value, const Elysium::Core::size ByteLength)
	{
		memcpy(&_InternalString._Stack._Data[0], Value, ByteLength);
		_InternalString._Stack.SetSize(ByteLength);
	}

	template<Concepts::Character C, class Allocator>
	inline const bool StringBase<C, Allocator>::IsHeapAllocated() const
	{	// most right bit (0000 000x)
		return (_InternalString._Stack._RemainingBytesAndFlag & _HeapStackFlagMask) == _HeapStackFlagMask;
	}

	using String = StringBase<char>;
	using WideString = StringBase<wchar_t>;
	using Utf8String = StringBase<char8_t>;
	using Utf16String = StringBase<char16_t>;
	using Utf32String = StringBase<char32_t>;
}
#endif
