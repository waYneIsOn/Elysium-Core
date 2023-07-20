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

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "CharacterTraits.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C, class Traits = CharacterTraits<C>, class Allocator = Memory::DefaultAllocator<C>>
	class String final
	{
	public:
		using ConstCharacter = const C;
		using CharacterPointer = C*;
		using ConstCharacterPointer = const C*;
		using CharacterReference = C&;
		using ConstCharacterReference = const C&;

		using CharacterTraits = Traits;
	private:
		struct HeapString final
		{
			CharacterPointer _Data; // 4/8 bytes
			System::size _Size; // 4/8 bytes (stores the number of bytes the string requires)
			System::size _CapacityAndFlag; // 4/8 bytes (stores 1 bit flag (stack/heap allocated) + 31/63 bit capacity)

			System::size GetCapacity() const noexcept;

			constexpr void SetCapacity(const System::size Value) noexcept;
		};	// 12/24 bytes

		struct StackString final
		{
			System::byte _Data[sizeof(HeapString) - sizeof(System::byte)]; // 11/23 bytes
			System::byte _RemainingBytesAndFlag;	// 1 byte -> 1 bit flag (indicating stack/heap allocation) + 7 bit remaining size

			constexpr const System::size GetSize() const noexcept;

			constexpr void SetSize(const System::size Value) noexcept;
		};	// 12/24 bytes
	public:
		constexpr String() noexcept;

		constexpr String(ConstCharacterPointer Value) noexcept;

		constexpr String(ConstCharacterPointer Value, const System::size Length) noexcept;

		constexpr String(ConstCharacter Value, const System::size Count) noexcept;

		constexpr String(const System::size Length) noexcept;

		constexpr String(const String& Source);

		constexpr String(String&& Right) noexcept;

		constexpr ~String();
	public:
		String<C, Traits, Allocator>& operator=(ConstCharacterPointer Value);

		String<C, Traits, Allocator>& operator=(const String& Source);

		String<C, Traits, Allocator>& operator=(String&& Right) noexcept;
	public:
		String<C, Traits, Allocator>::CharacterReference operator[](const System::size Index) noexcept;

		String<C, Traits, Allocator>::ConstCharacterReference operator[](const System::size Index) const noexcept;
	public:
		const bool operator==(ConstCharacterPointer Other) const;

		const bool operator!=(ConstCharacterPointer Other) const;

		const bool operator<(ConstCharacterPointer Other) const;

		const bool operator>(ConstCharacterPointer Other) const;

		const bool operator<=(ConstCharacterPointer Other) const;

		const bool operator>=(ConstCharacterPointer Other) const;

		const bool operator==(const String& Other) const;

		const bool operator!=(const String& Other) const;

		const bool operator<(const String& Other) const;

		const bool operator>(const String& Other) const;

		const bool operator<=(const String& Other) const;

		const bool operator>=(const String& Other) const;
	public:
		static constexpr const bool IsEmpty(const String& Value);
	public:
		static const String<C, Traits, Allocator> Empty;
	public:
		constexpr const System::size GetLength() const;

		constexpr const System::size GetCapacity() const;
	public:
		String<C, Traits, Allocator>::CharacterReference At(const System::size Index);

		String<C, Traits, Allocator>::ConstCharacterReference At(const System::size Index) const;
	public:
		void Resize(System::size Index);
	public:
		constexpr const bool StartsWith(ConstCharacterPointer Value) const;

		constexpr const bool EndsWith(ConstCharacterPointer Value) const;

		constexpr System::size GetHashCode() const;
		
		const System::size IndexOf(ConstCharacter Value) const;
		
		const System::size IndexOf(ConstCharacter Value, const System::size StartIndex) const;

		const System::size IndexOf(ConstCharacterPointer Sequence) const;

		const System::size IndexOf(ConstCharacterPointer Sequence, const System::size StartIndex) const;

		const System::size IndexOf(const String<C, Traits, Allocator>& Sequence, const System::size StartIndex) const;

		const System::size IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength) const noexcept;

		const System::size IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength, const System::size StartIndex) const noexcept;
		
		const System::size LastIndexOf(ConstCharacter Value) const;

		const System::size LastIndexOf(ConstCharacter Value, const System::size StartIndex) const;

		const System::size LastIndexOf(ConstCharacterPointer Sequence) const;

		const System::size LastIndexOf(ConstCharacterPointer Sequence, const System::size StartIndex) const;

		const System::size LastIndexOf(const String<C, Traits, Allocator>& Sequence, const System::size StartIndex) const;
		
		String<C, Traits, Allocator> Substring(const System::size StartIndex) const;

		String<C, Traits, Allocator> Substring(const System::size StartIndex, const System::size Length) const;

		//String<C, Allocator>::CharPointer ToCharArray();

		//String<C, Allocator>::ConstCharPointer ToCharArray() const;
	private:
		void constexpr InitializeHeapString(ConstCharacterPointer Value, const System::size Size);

		void constexpr InitializeStackString(ConstCharacterPointer Value, const System::size Size);
		
		void CopyHeapString(ConstCharacterPointer Value, const System::size CharSize);

		void CopyStackString(ConstCharacterPointer Value, const System::size ByteSize);

		void DeleteHeapString();

		const bool IsHeapAllocated() const;
	public:
		inline static constexpr const System::uint8_t MaximumSizeOnStack = sizeof(HeapString) - 1;
		inline static constexpr const System::uint8_t MaximumLengthOnStack = MaximumSizeOnStack / Traits::MinimumByteLength;
		 
		inline static constexpr const System::size MaximumSizeOnHeap = static_cast<Elysium::Core::Template::System::size>(-1) / 2;
		inline static constexpr const System::size MaximumLengthOnHeap = MaximumSizeOnHeap / Traits::MinimumByteLength;
	private:
		inline static Allocator _Allocator = Allocator();

		inline static constexpr const System::size _HeapStackFlagShift = (sizeof(Elysium::Core::Template::System::size) - 1) * 8;
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		inline static constexpr const System::size _HeapStackFlagMask = 0x01;
		inline static constexpr const System::size _CapacityExtractMask = ~(System::size(_HeapStackFlagMask) << _HeapStackFlagShift);
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

	template<Concepts::Character C, class Traits, class Allocator>
	inline Elysium::Core::Template::System::size String<C, Traits, Allocator>::HeapString::GetCapacity() const noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return _CapacityAndFlag & _CapacityExtractMask;
#else
		throw 1;
#endif
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr void String<C, Traits, Allocator>::HeapString::SetCapacity(const Elysium::Core::Template::System::size Value) noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		// most right bit of first byte (0000 000x) is stack/heap-flag
		_CapacityAndFlag = _HeapStackFlagMask << _HeapStackFlagShift |	// make sure stack-flag is set to one
			Value;
#else
		throw 1;
#endif
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size String<C, Traits, Allocator>::StackString::GetSize() const noexcept
	{	// most right bit (0000 000x) is stack/heap-flag, all other bits represent the remaining bytes
		return sizeof(HeapString) - 1 - (_RemainingBytesAndFlag >> 1);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr void String<C, Traits, Allocator>::StackString::SetSize(const Elysium::Core::Template::System::size Value) noexcept
	{	// seven most left bits represent the remaining bytes, most right bit represents stack-bitflag (0000 000F)
		_RemainingBytesAndFlag = 0x00 |	// make sure stack-flag is set to zero
			static_cast<Elysium::Core::Template::System::byte>(((sizeof(HeapString) - 1 - Value) << 1));
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr String<C, Traits, Allocator>::String() noexcept
		: String<C, Traits, Allocator>(nullptr, 0)
	{ }

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr String<C, Traits, Allocator>::String(ConstCharacterPointer Value) noexcept
		: String<C, Traits, Allocator>(Value, Traits::GetLength(Value))
	{ }

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr String<C, Traits, Allocator>::String(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length) noexcept
		: _InternalString{ 0x00 }
	{
		const Elysium::Core::Template::System::size Size = Length * Traits::MinimumByteLength;
		const Elysium::Core::Template::System::size SizeIncludingNullTerminator = Size + Traits::MinimumByteLength;
		if (SizeIncludingNullTerminator > MaximumSizeOnHeap)
		{	// ToDo: what to do? does this even occurre? linked list?
			//throw 1;
		}
		else if (SizeIncludingNullTerminator > MaximumSizeOnStack)
		{
			InitializeHeapString(Value, Size);
		}
		else
		{
			InitializeStackString(Value, Size);
		}
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr String<C, Traits, Allocator>::String(ConstCharacter Value, const System::size Count) noexcept
		: _InternalString{ 0x00 }
	{
		const Elysium::Core::Template::System::size Size = Count * Traits::MinimumByteLength;
		const Elysium::Core::Template::System::size SizeIncludingNullTerminator = Size + Traits::MinimumByteLength;
		if (SizeIncludingNullTerminator > MaximumSizeOnHeap)
		{	// ToDo: what to do? does this even occurre? linked list?
			//throw 1;
		}
		else if (SizeIncludingNullTerminator > MaximumSizeOnStack)
		{
			_InternalString._Heap._Data = _Allocator.Allocate(SizeIncludingNullTerminator);
			for (System::size i = 0; i < Count; i++)
			{
				memset(&_InternalString._Heap._Data[i * Traits::MinimumByteLength], Value, Traits::MinimumByteLength);
			}

			_InternalString._Heap._Size = Size;
			_InternalString._Heap.SetCapacity(Count);
		}
		else
		{
			memset(&_InternalString._Stack._Data[0], Value, Count);
			_InternalString._Stack.SetSize(Size);
		}
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr String<C, Traits, Allocator>::String(const Elysium::Core::Template::System::size Length) noexcept
		: _InternalString{ 0x00 }
	{
		const Elysium::Core::Template::System::size Size = Length * Traits::MinimumByteLength;
		const Elysium::Core::Template::System::size SizeIncludingNullTerminator = Size + Traits::MinimumByteLength;
		if (SizeIncludingNullTerminator > MaximumSizeOnHeap)
		{	// ToDo: what to do? does this even occurre? linked list?
			//throw 1;
		}
		else if (SizeIncludingNullTerminator > MaximumSizeOnStack)
		{
			_InternalString._Heap._Data = _Allocator.Allocate(SizeIncludingNullTerminator);
			_InternalString._Heap._Size = Size;
			_InternalString._Heap.SetCapacity(Length);
		}
		else
		{
			_InternalString._Stack.SetSize(Size);
		}
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr String<C, Traits, Allocator>::String(const String& Source)
		: _InternalString{ 0x00 }
	{
		if (Source.IsHeapAllocated())
		{
			const Elysium::Core::Template::System::size SourceLength = Source.GetLength();
			const Elysium::Core::Template::System::size SourceLengthIncludingNullTerminationCharacter = SourceLength + 
				Traits::MinimumByteLength;
			const Elysium::Core::Template::System::size SourceSize = SourceLength * Traits::MinimumByteLength;
			if (SourceLengthIncludingNullTerminationCharacter > GetCapacity())
			{	// source doesn't fit into this string
				DeleteHeapString();
				CopyHeapString(Source._InternalString._Heap._Data, SourceSize);
			}
			else
			{	// source fits into this string
				const Elysium::Core::Template::System::size SourceSizeIncludingNullTerminationCharacter = SourceLength * 
					Traits::MinimumByteLength + Traits::MinimumByteLength;
				memcpy(&_InternalString._Heap._Data[0], &Source._InternalString._Heap._Data[0], SourceSizeIncludingNullTerminationCharacter);
				_InternalString._Heap._Size = SourceSize;
			}
		}
		else
		{
#pragma warning (disable: 6385 6386)	// I want to copy 12/24 bytes
			memcpy(&_InternalString._Stack._Data[0], &Source._InternalString._Stack._Data[0], sizeof(StackString));
#pragma warning (default: 6385 6386)
		}
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr String<C, Traits, Allocator>::String(String&& Right) noexcept
		: _InternalString{ 0x00 }
	{
#pragma warning (disable: 6385 6386)	// I want to copy and set 12/24 bytes
		memcpy(&_InternalString._Stack._Data[0], &Right._InternalString._Stack._Data[0], sizeof(StackString));
		memset(&Right._InternalString._Stack._Data[0], 0x00, sizeof(StackString));
#pragma warning (default: 6385 6386)
		Right._InternalString._Stack.SetSize(0);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr String<C, Traits, Allocator>::~String()
	{
		DeleteHeapString();
	}
	
	template<Concepts::Character C, class Traits, class Allocator>
	inline String<C, Traits, Allocator>& String<C, Traits, Allocator>::operator=(ConstCharacterPointer Value)
	{
		const bool IsThisHeapAllocated = IsHeapAllocated();

		const Elysium::Core::Template::System::size ValueLength = Traits::GetLength(Value);
		const Elysium::Core::Template::System::size ValueLengthIncludingNullTerminator = ValueLength + 1;
		const Elysium::Core::Template::System::size ValueSize = ValueLength * Traits::MinimumByteLength;
		const Elysium::Core::Template::System::size ValueSizeIncludingNullTerminator = ValueSize + Traits::MinimumByteLength;
		if (ValueSizeIncludingNullTerminator > MaximumSizeOnHeap)
		{	// ToDo: what to do? does this even occurre? linked list?
			throw 1;
		}
		else if (ValueSizeIncludingNullTerminator > MaximumSizeOnStack)
		{
			if (IsThisHeapAllocated)
			{	// heap to heap
				if (ValueSizeIncludingNullTerminator > GetCapacity() * Traits::MinimumByteLength)
				{	// source doesn't fit into this string
					DeleteHeapString();
					CopyHeapString(Value, ValueSize);
				}
				else
				{	// source fits into this string
					memcpy(&_InternalString._Heap._Data[0], Value, ValueSizeIncludingNullTerminator);
					_InternalString._Heap._Size = ValueSize;
				}
			}
			else
			{	// heap to stack
				CopyHeapString(Value, ValueSize);
			}
		}
		else
		{
			if (IsThisHeapAllocated)
			{	// stack to heap
				memcpy(&_InternalString._Heap._Data[0], Value, ValueSizeIncludingNullTerminator);
				_InternalString._Heap._Size = ValueSize;
			}
			else
			{	// stack to stack
				CopyStackString(Value, ValueSize);
			}
		}

		return *this;
	}
	
	template<Concepts::Character C, class Traits, class Allocator>
	inline String<C, Traits, Allocator>& String<C, Traits, Allocator>::operator=(const String& Source)
	{
		if (this != &Source)
		{
			const bool IsThisHeapAllocated = IsHeapAllocated();
			const bool IsSourceHeapAllocated = Source.IsHeapAllocated();

			if (IsThisHeapAllocated && IsSourceHeapAllocated)
			{	// heap to heap
				const Elysium::Core::Template::System::size SourceSize = Source.GetLength() * Traits::MinimumByteLength;
				const Elysium::Core::Template::System::size SourceSizeIncludingNullTerminationCharacter = SourceSize + Traits::MinimumByteLength;
				if (SourceSizeIncludingNullTerminationCharacter > GetCapacity() * Traits::MinimumByteLength)
				{	// source doesn't fit into this string
					DeleteHeapString();
					CopyHeapString(Source._InternalString._Heap._Data, SourceSize);
				}
				else
				{	// source fits into this string
					memcpy(&_InternalString._Heap._Data[0], &Source._InternalString._Heap._Data[0], SourceSizeIncludingNullTerminationCharacter);
					_InternalString._Heap._Size = SourceSize;
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
				CopyHeapString(Source._InternalString._Heap._Data, Source.GetLength() * Traits::MinimumByteLength);
			}
			else
			{	// stack to heap
				memcpy(&_InternalString._Heap._Data[0], &Source._InternalString._Stack._Data[0], sizeof(StackString) - 1);
				_InternalString._Heap._Size = Source.GetLength() * Traits::MinimumByteLength;
			}
		}
		return *this;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline String<C, Traits, Allocator>& String<C, Traits, Allocator>::operator=(String&& Right) noexcept
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

	template<Concepts::Character C, class Traits, class Allocator>
	inline String<C, Traits, Allocator>::CharacterReference String<C, Traits, Allocator>::operator[](const Elysium::Core::Template::System::size Index) noexcept
	{
		return IsHeapAllocated() ?
			_InternalString._Heap._Data[Index] : (CharacterReference)_InternalString._Stack._Data[Index * Traits::MinimumByteLength];
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline String<C, Traits, Allocator>::ConstCharacterReference String<C, Traits, Allocator>::operator[](const Elysium::Core::Template::System::size Index) const noexcept
	{
		return IsHeapAllocated() ? 
			_InternalString._Heap._Data[Index] : 
			// do NOT cast to ConstCharacterReference here!
			(CharacterReference)_InternalString._Stack._Data[Index * Traits::MinimumByteLength];
	}
	
	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator==(ConstCharacterPointer Other) const
	{
		const Elysium::Core::Template::System::size OtherLength = Traits::GetLength(Other);

		if (IsHeapAllocated())
		{
			if(_InternalString._Heap._Size != OtherLength)
			{
				return false;
			}

			return Traits::Compare(&_InternalString._Heap._Data[0], Other, OtherLength) == 0;
		}
		else
		{
			if(_InternalString._Stack.GetSize() != OtherLength)
			{
				return false;
			}

			return Traits::Compare((ConstCharacterPointer)&_InternalString._Stack._Data[0], Other, OtherLength) == 0;
		}
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator!=(ConstCharacterPointer Other) const
	{
		if (IsHeapAllocated())
		{
			return Traits::Compare(&_InternalString._Heap._Data[0], Other, _InternalString._Heap._Size) == 0;
		}
		else
		{
			return Traits::Compare((ConstCharacterPointer)&_InternalString._Stack._Data[0], Other, _InternalString._Stack.GetSize()) == 0;
		}
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator<(ConstCharacterPointer Other) const
	{
		return false;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator>(ConstCharacterPointer Other) const
	{
		return false;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator<=(ConstCharacterPointer Other) const
	{
		return false;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator>=(ConstCharacterPointer Other) const
	{
		return false;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator==(const String& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) == 0;
		return operator==(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator!=(const String& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) != 0;
		return operator!=(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator<(const String& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) < 0;
		return operator<(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator>(const String& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) > 0;
		return operator>(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator<=(const String& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) <= 0;
		return operator<=(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::operator>=(const String& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) >= 0;
		return operator>=(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr const bool String<C, Traits, Allocator>::IsEmpty(const String& Value)
	{
		ConstCharacterPointer CurrentChar = Value.IsHeapAllocated() ? Value._InternalString._Heap._Data : (ConstCharacterPointer)&Value._InternalString._Stack._Data[0];
		return Traits::IsEmpty(CurrentChar);
	}

	template <Concepts::Character C, class Traits, class Allocator>
	inline const String<C, Traits, Allocator> String<C, Traits, Allocator>::Empty = String<C, Traits, Allocator>();

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size String<C, Traits, Allocator>::GetLength() const
	{
		return IsHeapAllocated() ? _InternalString._Heap._Size / Traits::MinimumByteLength : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr const Elysium::Core::Template::System::size String<C, Traits, Allocator>::GetCapacity() const
	{
		return IsHeapAllocated() ? _InternalString._Heap.GetCapacity() : MaximumSizeOnStack / Traits::MinimumByteLength;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline String<C, Traits, Allocator>::CharacterReference String<C, Traits, Allocator>::At(const System::size Index)
	{
		const bool HeapAllocated = IsHeapAllocated();
		const Elysium::Core::Template::System::size Capacity = HeapAllocated ? _InternalString._Heap.GetCapacity() : MaximumLengthOnStack;
		if (Index >= Capacity)
		{
			throw 1;
			//throw IndexOutOfRangeException();
		}

		// we possibly need to grow Length (in bounds of Capacity) as someone could write a char using this operator.
		const Elysium::Core::Template::System::size Length = HeapAllocated ? _InternalString._Heap._Size / Traits::MinimumByteLength : 
			_InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		if (Index >= Length)
		{
			const Elysium::Core::Template::System::size Size = (Length + 1) * Traits::MinimumByteLength;
			if (HeapAllocated)
			{
				_InternalString._Heap._Size = Size;
			}
			else
			{
				_InternalString._Stack.SetSize(Size);
			}
		}

		return HeapAllocated ? _InternalString._Heap._Data[Index] : (CharacterReference)_InternalString._Stack._Data[Index * Traits::MinimumByteLength];
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline String<C, Traits, Allocator>::ConstCharacterReference String<C, Traits, Allocator>::At(const System::size Index) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const Elysium::Core::Template::System::size Length = HeapAllocated ? _InternalString._Heap._Size / Traits::MinimumByteLength :
			_InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		if (Index >= Length)
		{
			throw 1;
			//throw IndexOutOfRangeException();
		}

		return HeapAllocated ? _InternalString._Heap._Data[Index] :
			// do NOT cast to ConstCharacterReference here!
			(CharacterReference)_InternalString._Stack._Data[Index * Traits::MinimumByteLength];
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void String<C, Traits, Allocator>::Resize(System::size Index)
	{
		throw 1;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr const bool String<C, Traits, Allocator>::StartsWith(ConstCharacterPointer Value) const
	{
		if (Value == nullptr)
		{
			return false;
		}

		const System::size ValueLength = Traits::GetLength(Value);
		const System::size Length = GetLength();
		if (ValueLength > Length)
		{
			return false;
		}

		ConstCharacterPointer Data = &operator[](0);
		for (System::size i = 0; i < ValueLength; i++)
		{
			if (Data[i] != Value[i])
			{
				return false;
			}
		}
		return true;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr const bool String<C, Traits, Allocator>::EndsWith(ConstCharacterPointer Value) const
	{
		if (Value == nullptr)
		{
			return false;
		}

		const System::size ValueLength = Traits::GetLength(Value);
		const System::size Length = GetLength();
		if (ValueLength > Length)
		{
			return false;
		}

		ConstCharacterPointer Data = &operator[](Length - 1);
		for (System::size i = Length - ValueLength; i < Length; i++)
		{
			if (Data[i] != Value[Length - 1 - i])
			{
				return false;
			}
		}
		return true;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr Elysium::Core::Template::System::size String<C, Traits, Allocator>::GetHashCode() const
	{	// code below should work similar to std::hash<std::u8string>()(_Data);
		Elysium::Core::Template::System::size Hash = 14695981039346656037ULL;
		const bool HeapAllocated = IsHeapAllocated();
		Elysium::Core::Template::System::size Size = HeapAllocated ? _InternalString._Heap._Size / Traits::MinimumByteLength : 
			_InternalString._Stack.GetSize() / Traits::MinimumByteLength;

		if (Size == 0)
		{
			return Hash;
		}
		
		ConstCharacterPointer CurrentChar = HeapAllocated ? _InternalString._Heap._Data : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		for (Elysium::Core::Template::System::size i = 0; i < Size; i++)
		{
			Hash ^= static_cast<Elysium::Core::Template::System::size>(CurrentChar[i]);
			Hash *= 1099511628211ULL;
		}
		
		return Hash;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size String<C, Traits, Allocator>::IndexOf(ConstCharacter Value) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data =  HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return Traits::IndexOf(Data, DataLength, Value);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size String<C, Traits, Allocator>::IndexOf(ConstCharacter Value, const Elysium::Core::Template::System::size StartIndex) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = (HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength) - StartIndex;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::IndexOf(Data, DataLength, Value);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size String<C, Traits, Allocator>::IndexOf(ConstCharacterPointer Sequence) const
	{
		if (Sequence == nullptr)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return Traits::IndexOf(Data, DataLength, Sequence);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size String<C, Traits, Allocator>::IndexOf(ConstCharacterPointer Sequence, const Elysium::Core::Template::System::size StartIndex) const
	{
		if (Sequence == nullptr)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::IndexOf(Data, DataLength, Sequence);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size String<C, Traits, Allocator>::IndexOf(const String<C, Traits, Allocator>& Sequence, const Elysium::Core::Template::System::size StartIndex) const
	{
		if (IsEmpty(Sequence))
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::IndexOf(Data, DataLength, &Sequence[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const System::size String<C, Traits, Allocator>::IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength) const noexcept
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return Traits::IndexOfAny(Data, DataLength, Sequence, SequenceLength);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const System::size String<C, Traits, Allocator>::IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength, const System::size StartIndex) const noexcept
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::IndexOfAny(Data, DataLength, Sequence, SequenceLength);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size String<C, Traits, Allocator>::LastIndexOf(ConstCharacter Value) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return Traits::LastIndexOf(Data, DataLength, Value);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const System::size String<C, Traits, Allocator>::LastIndexOf(ConstCharacter Value, const System::size StartIndex) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::LastIndexOf(Data, DataLength, Value);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size String<C, Traits, Allocator>::LastIndexOf(ConstCharacterPointer Sequence) const
	{
		if (Sequence == nullptr)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return Traits::LastIndexOf(Data, DataLength, Sequence);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size String<C, Traits, Allocator>::LastIndexOf(ConstCharacterPointer Sequence, const System::size StartIndex) const
	{
		if (Sequence == nullptr)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::LastIndexOf(Data, DataLength, Sequence);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size String<C, Traits, Allocator>::LastIndexOf(const String<C, Traits, Allocator>& Sequence, const Elysium::Core::Template::System::size StartIndex) const
	{
		if (IsEmpty(Sequence))
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::LastIndexOf(Data, DataLength, &Sequence[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline String<C, Traits, Allocator> String<C, Traits, Allocator>::Substring(const Elysium::Core::Template::System::size StartIndex) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		if (StartIndex > DataLength)
		{
			return String<C, Traits, Allocator>();
		}

		ConstCharacterPointer Data =  HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return String<C, Traits, Allocator>(Data, DataLength - StartIndex);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline String<C, Traits, Allocator> String<C, Traits, Allocator>::Substring(const Elysium::Core::Template::System::size StartIndex, const Elysium::Core::Template::System::size Length) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / Traits::MinimumByteLength;
		if (Length - StartIndex > DataLength)
		{
			return String<C, Traits, Allocator>();
		}

		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return String<C, Traits, Allocator>(Data, Length);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr void String<C, Traits, Allocator>::InitializeHeapString(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Size)
	{
		const Elysium::Core::Template::System::size SizeIncludingNullTerminator = Size + Traits::MinimumByteLength;

		_InternalString._Heap._Data = _Allocator.Allocate(SizeIncludingNullTerminator);
		memcpy(&_InternalString._Heap._Data[0], Value, Size);

		_InternalString._Heap._Size = Size;
		_InternalString._Heap.SetCapacity(Size / Traits::MinimumByteLength);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr void String<C, Traits, Allocator>::InitializeStackString(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Size)
	{
		memcpy(&_InternalString._Stack._Data[0], Value, Size);
		_InternalString._Stack.SetSize(Size);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void String<C, Traits, Allocator>::CopyHeapString(ConstCharacterPointer Value, const Elysium::Core::Template::System::size CharSize)
	{
		const Elysium::Core::Template::System::size SizeIncludingNullTerminationCharacter = CharSize + Traits::MinimumByteLength;

		_InternalString._Heap._Data = _Allocator.Allocate(SizeIncludingNullTerminationCharacter);
		memcpy(&_InternalString._Heap._Data[0], Value, SizeIncludingNullTerminationCharacter);

		_InternalString._Heap._Size = CharSize;
		_InternalString._Heap.SetCapacity(CharSize / Traits::MinimumByteLength);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void String<C, Traits, Allocator>::CopyStackString(ConstCharacterPointer Value, const Elysium::Core::Template::System::size ByteSize)
	{
		memcpy(&_InternalString._Stack._Data[0], Value, ByteSize);
		_InternalString._Stack.SetSize(ByteSize);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void String<C, Traits, Allocator>::DeleteHeapString()
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

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool String<C, Traits, Allocator>::IsHeapAllocated() const
	{	// most right bit (0000 000x)
		return (_InternalString._Stack._RemainingBytesAndFlag & _HeapStackFlagMask) == _HeapStackFlagMask;
	}
}
#endif
