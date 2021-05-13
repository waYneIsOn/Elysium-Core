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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core
{
	template <typename T>
	class Memory final
	{
	public:
		constexpr Memory();
		constexpr Memory(const Memory& Source) = delete;
		constexpr Memory(Memory&& Right) noexcept = delete;
		constexpr ~Memory();

		constexpr Memory& operator=(const Memory& Source) = delete;
		constexpr Memory& operator=(Memory&& Right) noexcept = delete;

		static constexpr void* Copy(void* Destination, const void* Source, size_t Length);
		static constexpr void* Move(void* Destination, const void* Source, size_t Length);
		static constexpr void* Set(void* Start, const Elysium::Core::uint8_t Value, size_t Length);
	private:
		size_t _Length;
		T* _Data;
	};

	template<typename T>
	inline constexpr Memory<T>::Memory()
		: _Length(0), _Data(nullptr)
	{ }
	template<typename T>
	inline constexpr Memory<T>::~Memory()
	{
		if (_Data != nullptr)
		{
			delete[] _Data;
			_Data = nullptr;
		}
	}

	template<typename T>
	inline constexpr void* Memory<T>::Copy(void* Destination, const void* Source, size_t Length)
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
	inline constexpr void* Memory<T>::Move(void* Destination, const void* Source, size_t Length)
	{
		Elysium::Core::byte* DestinationAddress = (Elysium::Core::byte*)Destination;
		Elysium::Core::byte* SourceAddress = (Elysium::Core::byte*)Source;

		Elysium::Core::byte* Temporary = new Elysium::Core::byte[Length];

		for (size_t i = 0; i < Length; i++)
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
	inline constexpr void* Memory<T>::Set(void* Start, const Elysium::Core::uint8_t Value, size_t Length)
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
