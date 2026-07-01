/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_BITREADER
#define ELYSIUM_CORE_TEMPLATE_IO_BITREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_LITERALS
#include "../System/Literals.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#include <cassert>

namespace Elysium::Core::Template::IO
{
	template <bool LeastSignificantBitFirst = true>
	class BitReader
	{
	public:
		using BufferType = Elysium::Core::Template::System::uint64_t;
	public:
		constexpr BitReader() noexcept = default;

		constexpr BitReader(const BitReader& Source) = delete;

		constexpr BitReader(BitReader&& Right) noexcept = delete;

		~BitReader() = default;
	public:
		constexpr BitReader& operator=(const BitReader& Source) = delete;

		constexpr BitReader& operator=(BitReader&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Returns length in count of BITS!
		/// </summary>
		/// <returns></returns>
		inline constexpr Elysium::Core::Template::System::uint8_t GetLength() const noexcept
		{
			return _Count;
		}

		inline constexpr const bool GetIsFull() const noexcept
		{
			return _Count > SafeShiftThreshold;
		}
	public:
		inline constexpr Elysium::Core::Template::System::uint64_t Peek(const Elysium::Core::Template::System::uint8_t Bits)
		{
			if (0 == _Count)
			{	// @ToDo:
				throw 1;
			}

			if constexpr (LeastSignificantBitFirst)
			{
				return static_cast<Elysium::Core::Template::System::uint64_t>(_Buffer & ((1_ui64 << Bits) - 1));
			}
			else
			{
				return static_cast<Elysium::Core::Template::System::uint64_t>(_Buffer >> (_Count - Bits)) & ((1_ui64 << Bits) - 1);
			}
		}

		inline constexpr void Consume(const Elysium::Core::Template::System::uint8_t Bits)
		{
			if constexpr (LeastSignificantBitFirst)
			{
				_Buffer >>= Bits;
				_Count -= Bits;
			}
			else
			{
				_Count -= Bits;
				_Buffer &= ((1_ui64 << _Count) - 1);
			}
		}

		inline constexpr void AlignToByteBoundary()
		{
			const Elysium::Core::Template::System::uint8_t BitsToSkip = (_Count % 8);
			Consume(BitsToSkip);

			assert((_Buffer & ((1_ui64 << SafeShiftThreshold) - 1)) == _Buffer);
		}

		inline constexpr Elysium::Core::Template::System::uint64_t Read(const Elysium::Core::Template::System::uint8_t Bits)
		{
			Elysium::Core::Template::System::uint64_t TemporaryValue = Peek(Bits);
			Consume(Bits);

			return TemporaryValue;
		}

		inline constexpr const bool HasBits(const Elysium::Core::Template::System::uint8_t Bits) noexcept
		{
			return _Count >= Bits;
		}
		
		inline void Push(const Elysium::Core::Template::System::byte Byte)
		{
			assert(_Count <= SafeShiftThreshold);

			if constexpr (LeastSignificantBitFirst)
			{
				_Buffer |= static_cast<Elysium::Core::Template::System::uint64_t>(Byte) << _Count;
				_Count += 8;
			}
			else
			{
				_Buffer >>= 8;
				_Buffer |= static_cast<Elysium::Core::Template::System::uint64_t>(Byte & 0xFF) << SafeShiftThreshold;
				_Count += 8;
			}
		}
	public:
		inline static constexpr const Elysium::Core::Template::System::uint8_t Capacity = sizeof(BufferType) * 8;

		inline static constexpr const Elysium::Core::Template::System::uint8_t SafeShiftThreshold = Capacity - 8;
	private:
		BufferType _Buffer;
		Elysium::Core::Template::System::uint8_t _Count;
	};
}
#endif
