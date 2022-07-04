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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "Vector.hpp"
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
	class StringBase final
	{
	public:
		using ConstCharacter = const C;
		using CharacterPointer = C*;
		using ConstCharacterPointer = const C*;
		using CharacterReference = C&;
		using ConstCharacterReference = const C&;
	private:
		struct HeapString final
		{
			CharacterPointer _Data; // 4/8 bytes
			System::size _Size; // 4/8 bytes
			System::size _CapacityAndFlag; // 4/8 bytes -> 1 bit flag (stack/heap allocated) + 31/63 bit capacity

			System::size GetCapacity() const noexcept;

			void SetCapacity(const System::size Value) noexcept;
		};	// 12/24 bytes

		struct StackString final
		{
			System::byte _Data[sizeof(HeapString) - sizeof(System::byte)]; // 11/23 bytes
			System::byte _RemainingBytesAndFlag;	// 1 byte -> 1 bit flag (stack/heap allocated) + 7 bit remaining size

			System::size GetSize() const noexcept;

			void SetSize(const System::size Value) noexcept;
		};	// 12/24 bytes
	public:
		StringBase() noexcept;

		StringBase(ConstCharacterPointer Value) noexcept;

		StringBase(ConstCharacterPointer Value, const System::size Length) noexcept;

		StringBase(const System::size Length) noexcept;

		StringBase(const StringBase& Source);

		StringBase(StringBase&& Right) noexcept;

		~StringBase();
	public:
		StringBase<C, Traits, Allocator>& operator=(ConstCharacterPointer Value);

		StringBase<C, Traits, Allocator>& operator=(const StringBase& Source);

		StringBase<C, Traits, Allocator>& operator=(StringBase&& Right) noexcept;
	public:
		StringBase<C, Traits, Allocator>::CharacterReference operator[](const System::size Index);

		StringBase<C, Traits, Allocator>::ConstCharacterReference operator[](const System::size Index) const;
	public:
		const bool operator==(ConstCharacterPointer Other) const;

		const bool operator!=(ConstCharacterPointer Other) const;

		const bool operator<(ConstCharacterPointer Other) const;

		const bool operator>(ConstCharacterPointer Other) const;

		const bool operator<=(ConstCharacterPointer Other) const;

		const bool operator>=(ConstCharacterPointer Other) const;

		const bool operator==(const StringBase& Other) const;

		const bool operator!=(const StringBase& Other) const;

		const bool operator<(const StringBase& Other) const;

		const bool operator>(const StringBase& Other) const;

		const bool operator<=(const StringBase& Other) const;

		const bool operator>=(const StringBase& Other) const;
	public:
		static constexpr const bool IsEmpty(const StringBase& Value);
	public:
		const System::size GetLength() const;

		const System::size GetCapacity() const;
	public:
		constexpr const bool StartsWith(ConstCharacterPointer Value) const;

		constexpr const bool EndsWith(ConstCharacterPointer Value) const;

		constexpr System::size GetHashCode() const;
		
		const System::size IndexOf(ConstCharacter Value) const;
		
		const System::size IndexOf(ConstCharacter Value, const System::size StartIndex) const;

		const System::size IndexOf(ConstCharacterPointer Sequence) const;

		const System::size IndexOf(ConstCharacterPointer Sequence, const System::size StartIndex) const;

		const System::size IndexOf(const StringBase<C, Traits, Allocator>& Sequence, const System::size StartIndex) const;

		const System::size IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength) const noexcept;

		const System::size IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength, const System::size StartIndex) const noexcept;
		
		const System::size LastIndexOf(ConstCharacter Value) const;

		const System::size LastIndexOf(ConstCharacter Value, const System::size StartIndex) const;

		const System::size LastIndexOf(ConstCharacterPointer Sequence) const;

		const System::size LastIndexOf(ConstCharacterPointer Sequence, const System::size StartIndex) const;

		const System::size LastIndexOf(const StringBase<C, Traits, Allocator>& Sequence, const System::size StartIndex) const;
		
		StringBase<C, Traits, Allocator> Substring(const System::size StartIndex) const;

		StringBase<C, Traits, Allocator> Substring(const System::size StartIndex, const System::size Length) const;

		Container::Vector<StringBase<C, Traits, Allocator>> Split(ConstCharacter Delimiter);

		Container::Vector<StringBase<C, Traits, Allocator>> Split(ConstCharacterPointer Delimiter);

		//StringBase<C, Allocator>::CharPointer ToCharArray();

		//StringBase<C, Allocator>::ConstCharPointer ToCharArray() const;
	private:
		void InitializeHeapString(ConstCharacterPointer Value, const System::size Length);

		void InitializeStackString(ConstCharacterPointer Value, const System::size Size);
		
		void CopyHeapString(ConstCharacterPointer Value, const System::size CharSize);

		void CopyStackString(ConstCharacterPointer Value, const System::size ByteSize);

		void DeleteHeapString();

		const bool IsHeapAllocated() const;
	public:
		inline static constexpr const System::uint8_t MaximumSizeOnStack = sizeof(HeapString) - 1;
		inline static constexpr const System::uint8_t MaximumLengthOnStack = MaximumSizeOnStack / sizeof(C);
		 
		inline static constexpr const System::size MaximumSizeOnHeap = static_cast<Elysium::Core::Template::System::size>(-1) / 2;
		inline static constexpr const System::size MaximumLengthOnHeap = MaximumSizeOnHeap / sizeof(C);
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
	inline Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::HeapString::GetCapacity() const noexcept
	{
#ifdef ELYSIUM_CORE_LITTLEENDIAN
		return _CapacityAndFlag & _CapacityExtractMask;
#else
		throw 1;
#endif
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void StringBase<C, Traits, Allocator>::HeapString::SetCapacity(const Elysium::Core::Template::System::size Value) noexcept
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
	inline Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::StackString::GetSize() const noexcept
	{	// most right bit (0000 000x) is stack/heap-flag, all other bits represent the remaining bytes
		return sizeof(HeapString) - 1 - (_RemainingBytesAndFlag >> 1);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void StringBase<C, Traits, Allocator>::StackString::SetSize(const Elysium::Core::Template::System::size Value) noexcept
	{	// seven most left bits represent the remaining bytes, most right bit represents stack-bitflag (0000 000F)
		_RemainingBytesAndFlag = 0x00 |	// make sure stack-flag is set to zero
			static_cast<Elysium::Core::Template::System::byte>(((sizeof(HeapString) - 1 - Value) << 1));
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>::StringBase() noexcept
		: StringBase<C, Traits, Allocator>(nullptr, 0)
	{ }

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>::StringBase(ConstCharacterPointer Value) noexcept
		: StringBase<C, Traits, Allocator>(Value, Traits::GetLength(Value))
	{ }

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>::StringBase(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length) noexcept
		: _InternalString{ 0x00 }
	{
		const Elysium::Core::Template::System::size Size = Length * sizeof(C);
		const Elysium::Core::Template::System::size SizeIncludingNullTerminator = Size + sizeof(C);
		if (SizeIncludingNullTerminator > MaximumSizeOnHeap)
		{	// ToDo: what to do? does this even occurre? linked list?
			//throw 1;
		}
		else if (SizeIncludingNullTerminator > MaximumSizeOnStack)
		{
			InitializeHeapString(Value, Length);
		}
		else
		{
			InitializeStackString(Value, Size);
		}
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>::StringBase(const Elysium::Core::Template::System::size Length) noexcept
		: _InternalString{ 0x00 }
	{
		const Elysium::Core::Template::System::size Size = Length * sizeof(C);
		const Elysium::Core::Template::System::size SizeIncludingNullTerminator = Size + sizeof(C);
		if (SizeIncludingNullTerminator > MaximumSizeOnHeap)
		{	// ToDo: what to do? does this even occurre? linked list?
			//throw 1;
		}
		else if (SizeIncludingNullTerminator > MaximumSizeOnStack)
		{
			_InternalString._Heap._Data = _Allocator.Allocate(Length + 1);
			_InternalString._Heap._Size = 0;
			_InternalString._Heap.SetCapacity(Length);
		}
		else
		{
			_InternalString._Stack.SetSize(0);
		}
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>::StringBase(const StringBase& Source)
		: _InternalString{ 0x00 }
	{
		if (Source.IsHeapAllocated())
		{
			const Elysium::Core::Template::System::size SourceCharSize = Source.GetLength();
			const Elysium::Core::Template::System::size SourceCharSizeIncludingNullTerminationCharacter = SourceCharSize + 1;
			if (SourceCharSizeIncludingNullTerminationCharacter > GetCapacity())
			{	// source doesn't fit into this string
				DeleteHeapString();
				CopyHeapString(Source._InternalString._Heap._Data, SourceCharSize);
			}
			else
			{	// source fits into this string
				const Elysium::Core::Template::System::size SourceByteSizeIncludingNullTerminationCharacter = SourceCharSize * sizeof(C) + sizeof(C);
				memcpy(&_InternalString._Heap._Data[0], &Source._InternalString._Heap._Data[0], SourceByteSizeIncludingNullTerminationCharacter);
				_InternalString._Heap._Size = SourceCharSize;
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
	inline StringBase<C, Traits, Allocator>::StringBase(StringBase&& Right) noexcept
		: _InternalString{ 0x00 }
	{
#pragma warning (disable: 6385 6386)	// I want to copy and set 12/24 bytes
		memcpy(&_InternalString._Stack._Data[0], &Right._InternalString._Stack._Data[0], sizeof(StackString));
		memset(&Right._InternalString._Stack._Data[0], 0x00, sizeof(StackString));
#pragma warning (default: 6385 6386)
		Right._InternalString._Stack.SetSize(0);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>::~StringBase()
	{
		DeleteHeapString();
	}
	
	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>& StringBase<C, Traits, Allocator>::operator=(ConstCharacterPointer Value)
	{
		const bool IsThisHeapAllocated = IsHeapAllocated();

		const Elysium::Core::Template::System::size ValueLength = Traits::GetLength(Value);
		const Elysium::Core::Template::System::size ValueLengthIncludingNullTerminator = ValueLength + 1;
		const Elysium::Core::Template::System::size ValueSize = ValueLength * sizeof(C);
		const Elysium::Core::Template::System::size ValueSizeIncludingNullTerminator = ValueSize + sizeof(C);
		if (ValueSizeIncludingNullTerminator > MaximumSizeOnHeap)
		{	// ToDo: what to do? does this even occurre? linked list?
			throw 1;
		}
		else if (ValueSizeIncludingNullTerminator > MaximumSizeOnStack)
		{
			if (IsThisHeapAllocated)
			{	// heap to heap
				if (ValueLengthIncludingNullTerminator > GetCapacity())
				{	// source doesn't fit into this string
					DeleteHeapString();
					CopyHeapString(Value, ValueLength);
				}
				else
				{	// source fits into this string
					memcpy(&_InternalString._Heap._Data[0], Value, ValueSizeIncludingNullTerminator);
					_InternalString._Heap._Size = ValueLength;
				}
			}
			else
			{	// heap to stack
				CopyHeapString(Value, ValueLength);
			}
		}
		else
		{
			if (IsThisHeapAllocated)
			{	// stack to heap
				memcpy(&_InternalString._Heap._Data[0], Value, ValueSizeIncludingNullTerminator);
				_InternalString._Heap._Size = ValueLength;
			}
			else
			{	// stack to stack
				CopyStackString(Value, ValueSize);
			}
		}

		return *this;
	}
	
	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>& StringBase<C, Traits, Allocator>::operator=(const StringBase& Source)
	{
		if (this != &Source)
		{
			const bool IsThisHeapAllocated = IsHeapAllocated();
			const bool IsSourceHeapAllocated = Source.IsHeapAllocated();

			if (IsThisHeapAllocated && IsSourceHeapAllocated)
			{	// heap to heap
				const Elysium::Core::Template::System::size SourceCharSize = Source.GetLength();
				const Elysium::Core::Template::System::size SourceCharSizeIncludingNullTerminationCharacter = SourceCharSize + 1;
				if (SourceCharSizeIncludingNullTerminationCharacter > GetCapacity())
				{	// source doesn't fit into this string
					DeleteHeapString();
					CopyHeapString(Source._InternalString._Heap._Data, SourceCharSize);
				}
				else
				{	// source fits into this string
					const Elysium::Core::Template::System::size SourceByteSizeIncludingNullTerminationCharacter = SourceCharSize * sizeof(C) + sizeof(C);
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
				CopyHeapString(Source._InternalString._Heap._Data, Source.GetLength());
			}
			else
			{	// stack to heap
				
				memcpy(&_InternalString._Heap._Data[0], &Source._InternalString._Stack._Data[0], sizeof(StackString) - 1);
				_InternalString._Heap._Size = Source.GetLength();
			}
		}
		return *this;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>& StringBase<C, Traits, Allocator>::operator=(StringBase&& Right) noexcept
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
	inline StringBase<C, Traits, Allocator>::CharacterReference StringBase<C, Traits, Allocator>::operator[](const Elysium::Core::Template::System::size Index)
	{
		const bool HeapAllocated = IsHeapAllocated();
		const Elysium::Core::Template::System::size Length = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		if (Index >= Length)
		{
			throw 1;
			//throw IndexOutOfRangeException();
		}

		return HeapAllocated ? _InternalString._Heap._Data[Index] : *(CharacterPointer)&_InternalString._Stack._Data[Index];
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator>::ConstCharacterReference StringBase<C, Traits, Allocator>::operator[](const Elysium::Core::Template::System::size Index) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const Elysium::Core::Template::System::size Length = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		if (Index >= Length)
		{
			throw 1;
			//throw IndexOutOfRangeException();
		}

		return HeapAllocated ? _InternalString._Heap._Data[Index] : *(ConstCharacterPointer)&_InternalString._Stack._Data[Index];
	}
	
	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator==(ConstCharacterPointer Other) const
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
	inline const bool StringBase<C, Traits, Allocator>::operator!=(ConstCharacterPointer Other) const
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
	inline const bool StringBase<C, Traits, Allocator>::operator<(ConstCharacterPointer Other) const
	{
		return false;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator>(ConstCharacterPointer Other) const
	{
		return false;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator<=(ConstCharacterPointer Other) const
	{
		return false;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator>=(ConstCharacterPointer Other) const
	{
		return false;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator==(const StringBase& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) == 0;
		return operator==(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator!=(const StringBase& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) != 0;
		return operator!=(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator<(const StringBase& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) < 0;
		return operator<(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator>(const StringBase& Other) const
	{
		if (this == &Other)
		{
			return false;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) > 0;
		return operator>(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator<=(const StringBase& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) <= 0;
		return operator<=(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const bool StringBase<C, Traits, Allocator>::operator>=(const StringBase& Other) const
	{
		if (this == &Other)
		{
			return true;
		}
		//return Traits::Compare(_Data, Other._Data, Other._Length) >= 0;
		return operator>=(&Other[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr const bool StringBase<C, Traits, Allocator>::IsEmpty(const StringBase& Value)
	{
		return Traits::IsEmpty(&Value[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::GetLength() const
	{
		return IsHeapAllocated() ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::GetCapacity() const
	{
		return IsHeapAllocated() ? _InternalString._Heap.GetCapacity() : MaximumSizeOnStack / sizeof(C);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline constexpr const bool StringBase<C, Traits, Allocator>::StartsWith(ConstCharacterPointer Value) const
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
	inline constexpr const bool StringBase<C, Traits, Allocator>::EndsWith(ConstCharacterPointer Value) const
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
	inline constexpr Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::GetHashCode() const
	{	// code below should work similar to std::hash<std::u8string>()(_Data);
		Elysium::Core::Template::System::size Hash = 14695981039346656037ULL;
		const bool HeapAllocated = IsHeapAllocated();
		Elysium::Core::Template::System::size Size = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);

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
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::IndexOf(ConstCharacter Value) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data =  HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return Traits::IndexOf(Data, DataLength, Value);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::IndexOf(ConstCharacter Value, const Elysium::Core::Template::System::size StartIndex) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::IndexOf(Data, DataLength, Value);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::IndexOf(ConstCharacterPointer Sequence) const
	{
		if (Sequence == nullptr)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return Traits::IndexOf(Data, DataLength, Sequence);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::IndexOf(ConstCharacterPointer Sequence, const Elysium::Core::Template::System::size StartIndex) const
	{
		if (Sequence == nullptr)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::IndexOf(Data, DataLength, Sequence);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::IndexOf(const StringBase<C, Traits, Allocator>& Sequence, const Elysium::Core::Template::System::size StartIndex) const
	{
		if (IsEmpty(Sequence))
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::IndexOf(Data, DataLength, &Sequence[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const System::size StringBase<C, Traits, Allocator>::IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength) const noexcept
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return CharacterTraits<C>::IndexOfAny(Data, DataLength, Sequence, SequenceLength);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const System::size StringBase<C, Traits, Allocator>::IndexOfAny(ConstCharacterPointer Sequence, const System::size SequenceLength, const System::size StartIndex) const noexcept
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return CharacterTraits<C>::IndexOfAny(Data, DataLength, Sequence, SequenceLength);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::LastIndexOf(ConstCharacter Value) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return Traits::LastIndexOf(Data, DataLength, Value);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const System::size StringBase<C, Traits, Allocator>::LastIndexOf(ConstCharacter Value, const System::size StartIndex) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::LastIndexOf(Data, DataLength, Value);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::LastIndexOf(ConstCharacterPointer Sequence) const
	{
		if (Sequence == nullptr)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];
		return Traits::LastIndexOf(Data, DataLength, Sequence);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::LastIndexOf(ConstCharacterPointer Sequence, const System::size StartIndex) const
	{
		if (Sequence == nullptr)
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::LastIndexOf(Data, DataLength, Sequence);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline const Elysium::Core::Template::System::size StringBase<C, Traits, Allocator>::LastIndexOf(const StringBase<C, Traits, Allocator>& Sequence, const Elysium::Core::Template::System::size StartIndex) const
	{
		if (IsEmpty(Sequence))
		{
			return static_cast<Elysium::Core::Template::System::size>(-1);
		}

		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return Traits::LastIndexOf(Data, DataLength, &Sequence[0]);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator> StringBase<C, Traits, Allocator>::Substring(const Elysium::Core::Template::System::size StartIndex) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		if (StartIndex > DataLength)
		{
			return StringBase<C, Traits, Allocator>();
		}

		ConstCharacterPointer Data =  HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return StringBase<C, Traits, Allocator>(Data, DataLength - StartIndex);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline StringBase<C, Traits, Allocator> StringBase<C, Traits, Allocator>::Substring(const Elysium::Core::Template::System::size StartIndex, const Elysium::Core::Template::System::size Length) const
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		if (Length - StartIndex > DataLength)
		{
			return StringBase<C, Traits, Allocator>();
		}

		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[StartIndex] : (ConstCharacterPointer)&_InternalString._Stack._Data[StartIndex];
		return StringBase<C, Traits, Allocator>(Data, Length);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline Container::Vector<StringBase<C, Traits, Allocator>> StringBase<C, Traits, Allocator>::Split(ConstCharacter Delimiter)
	{
		const bool HeapAllocated = IsHeapAllocated();
		const System::size DataLength = HeapAllocated ? _InternalString._Heap._Size : _InternalString._Stack.GetSize() / sizeof(C);
		ConstCharacterPointer Data = HeapAllocated ? &_InternalString._Heap._Data[0] : (ConstCharacterPointer)&_InternalString._Stack._Data[0];

		Container::Vector<StringBase<C, Traits, Allocator>> Result = Container::Vector<StringBase<C, Traits, Allocator>>();
		System::size StartIndex = 0;
		System::size Length = 0;
		for (System::size i = 0; i < DataLength; i++)
		{
			Length = IndexOf(Delimiter, StartIndex);
			if (Length == static_cast<Elysium::Core::Template::System::size>(-1))
			{
				if (DataLength - StartIndex > 0)
				{
					Result.PushBack(Functional::Move(StringBase<C, Traits, Allocator>(&Data[StartIndex], DataLength - StartIndex)));
				}
				break;
			}
			Result.PushBack(Functional::Move(StringBase<C, Traits, Allocator>(&Data[StartIndex], Length)));
			StartIndex += Length + 1;
		}

		return Result;
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline Container::Vector<StringBase<C, Traits, Allocator>> StringBase<C, Traits, Allocator>::Split(ConstCharacterPointer Delimiter)
	{
		throw 1;
		/*
		System::size DelimiterLength = Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(Delimiter);
		System::size StartIndex = 0;
		System::size Length = 0;

		while (true)
		{
			Length = IndexOf(Delimiter, StartIndex);
			if (Length == static_cast<Elysium::Core::Template::System::size>(-1))
			{
				if (_Length - StartIndex > 0)
				{
					Target.Add(Utf8String(&_Data[StartIndex], _Length - StartIndex));
				}
				break;
			}
			Target.Add(Utf8String(&_Data[StartIndex], Length - StartIndex));
			StartIndex += (Length - StartIndex) + DelimiterLength;
		}
		*/
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void StringBase<C, Traits, Allocator>::InitializeHeapString(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Length)
	{
		const Elysium::Core::Template::System::size LengthIncludingNullTerminationCharacter = Length + 1;

		_InternalString._Heap._Data = _Allocator.Allocate(LengthIncludingNullTerminationCharacter);
		memcpy(&_InternalString._Heap._Data[0], Value, LengthIncludingNullTerminationCharacter);

		_InternalString._Heap._Size = Length;
		_InternalString._Heap.SetCapacity(Length);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void StringBase<C, Traits, Allocator>::InitializeStackString(ConstCharacterPointer Value, const Elysium::Core::Template::System::size Size)
	{
		memcpy(&_InternalString._Stack._Data[0], Value, Size);
		_InternalString._Stack.SetSize(Size);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void StringBase<C, Traits, Allocator>::CopyHeapString(ConstCharacterPointer Value, const Elysium::Core::Template::System::size CharSize)
	{
		const Elysium::Core::Template::System::size SizeIncludingNullTerminationCharacter = CharSize + 1;

		_InternalString._Heap._Data = _Allocator.Allocate(SizeIncludingNullTerminationCharacter);
		memcpy(&_InternalString._Heap._Data[0], Value, SizeIncludingNullTerminationCharacter);

		_InternalString._Heap._Size = CharSize;
		_InternalString._Heap.SetCapacity(CharSize);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void StringBase<C, Traits, Allocator>::CopyStackString(ConstCharacterPointer Value, const Elysium::Core::Template::System::size ByteSize)
	{
		memcpy(&_InternalString._Stack._Data[0], Value, ByteSize);
		_InternalString._Stack.SetSize(ByteSize);
	}

	template<Concepts::Character C, class Traits, class Allocator>
	inline void StringBase<C, Traits, Allocator>::DeleteHeapString()
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
	inline const bool StringBase<C, Traits, Allocator>::IsHeapAllocated() const
	{	// most right bit (0000 000x)
		return (_InternalString._Stack._RemainingBytesAndFlag & _HeapStackFlagMask) == _HeapStackFlagMask;
	}
}
#endif
