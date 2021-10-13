/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MEMORY
#define ELYSIUM_CORE_MEMORY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_SPAN
#include "Span.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core
{
	template <typename T>
	class Memory final
	{
	public:
		Memory(const T& StartElement, const Elysium::Core::uint64_t Length);
		Memory(const Memory& Source) = delete;
		Memory(Memory&& Right) noexcept = delete;
		~Memory();

		Memory& operator=(const Memory& Source) = delete;
		Memory& operator=(Memory&& Right) noexcept = delete;

		const Elysium::Core::uint64_t GetLength() const;

		const bool GetIsEmpty() const;

		Span<T> GetSpan();

		const Span<T> GetSpan() const;

		Memory<T> Slice(const Elysium::Core::uint64_t Start, const Elysium::Core::uint64_t Length);

		static void* Copy(void* Destination, const void* Source, Elysium::Core::size Length);
		static void* Move(void* Destination, const void* Source, Elysium::Core::size Length);
		static void* Set(void* Start, const Elysium::Core::uint8_t Value, Elysium::Core::size Length);
	private:
		Elysium::Core::size _Length;
		T* _Data;
	};

	template<typename T>
	inline Memory<T>::Memory(const T& StartElement, const Elysium::Core::uint64_t Length)
		: _Length(Length), _Data(Length == 0 ? nullptr : new T[_Length])
	{
		if (_Data != nullptr)
		{
			Elysium::Core::Memory<char8_t>::Copy(_Data, &StartElement, _Length * sizeof(T));
		}
	}
	template<typename T>
	inline Memory<T>::~Memory()
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
			_Data = nullptr;
		}
	}

	template<typename T>
	inline const Elysium::Core::uint64_t Memory<T>::GetLength() const
	{
		return _Length;
	}

	template<typename T>
	inline const bool Memory<T>::GetIsEmpty() const
	{
		return _Length == 0;
	}

	template<typename T>
	inline Span<T> Memory<T>::GetSpan()
	{
		return Span<T>(*_Data, _Length);
	}

	template<typename T>
	inline const Span<T> Memory<T>::GetSpan() const
	{
		return Span<T>(*_Data, _Length);
	}

	template<typename T>
	inline Memory<T> Memory<T>::Slice(const Elysium::Core::uint64_t Start, const Elysium::Core::uint64_t Length)
	{
		// ToDo: check start & length
		return Memory(_Data[Start], Length);
	}

	template<typename T>
	inline void* Memory<T>::Copy(void* Destination, const void* Source, Elysium::Core::size Length)
	{
		Elysium::Core::byte* DestinationAddress = (Elysium::Core::byte*)Destination;
		Elysium::Core::byte* SourceAddress = (Elysium::Core::byte*)Source;
		while (Length-- > 0)
		{
			*DestinationAddress++ = *SourceAddress++;
		}
		return Destination;
	}

	template<typename T>
	inline void* Memory<T>::Move(void* Destination, const void* Source, Elysium::Core::size Length)
	{
		Elysium::Core::byte* DestinationAddress = (Elysium::Core::byte*)Destination;
		Elysium::Core::byte* SourceAddress = (Elysium::Core::byte*)Source;

		Elysium::Core::byte* Temporary = new Elysium::Core::byte[Length];

		for (Elysium::Core::size i = 0; i < Length; i++)
		{
			Temporary[i] = SourceAddress[i];
		}

		while (Length-- > 0)
		{
			*DestinationAddress++ = Temporary++;
		}

		delete[] Temporary;

		return Destination;
	}

	template<typename T>
	inline void* Memory<T>::Set(void* Start, const Elysium::Core::uint8_t Value, Elysium::Core::size Length)
	{
		Elysium::Core::byte* Address = (Elysium::Core::byte*)Start;
		while (Length-- > 0)
		{
			*Address++ = Value;
		}
		return Start;
	}
}
#endif
