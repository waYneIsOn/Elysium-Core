/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_BITBUFFER
#define ELYSIUM_CORE_TEMPLATE_IO_BITBUFFER

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
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="LeastSignificantBitFirst"></typeparam>
	template <bool LeastSignificantBitFirst = true>
	class BitBuffer
	{
	public:
		using BufferType = Elysium::Core::Template::System::uint64_t;
	public:
		constexpr BitBuffer() noexcept = default;

		constexpr BitBuffer(const BitBuffer& Source) = delete;

		constexpr BitBuffer(BitBuffer&& Right) noexcept = delete;

		constexpr ~BitBuffer() = default;
	public:
		constexpr BitBuffer<LeastSignificantBitFirst>& operator=(const BitBuffer& Source) = delete;

		constexpr BitBuffer<LeastSignificantBitFirst>& operator=(BitBuffer&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Returns length as numbers of BITS!
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

			if (Bits == sizeof(Elysium::Core::Template::System::uint64_t) * 8) ELYSIUM_CORE_PATH_UNLIKELY
			{
				return _Buffer;
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
			_Count -= Bits;

			if constexpr (LeastSignificantBitFirst)
			{
				if (Bits == sizeof(Elysium::Core::Template::System::uint64_t) * 8) ELYSIUM_CORE_PATH_UNLIKELY
				{
					_Buffer = 0;
				}
				else
				{
					_Buffer >>= Bits;
				}
			}
			else
			{
				if (Bits == sizeof(Elysium::Core::Template::System::uint64_t) * 8) ELYSIUM_CORE_PATH_UNLIKELY
				{
					_Buffer = 0;
				}
				else
				{
					_Buffer &= ((1_ui64 << _Count) - 1);
				}
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

		inline void Push(const BufferType Bits, const Elysium::Core::Template::System::uint8_t Length)
		{
			constexpr Elysium::Core::Template::System::uint8_t Width = sizeof(BufferType) * 8;

			assert(_Count + Length <= Capacity);
			assert(Length <= Width);

			if (0 == Length)
			{
				return;
			}

			const BufferType Mask = (Length == Width) ? ~BufferType(0) : ((BufferType(1) << Length) - BufferType(1));
			const BufferType Value = Bits & Mask;

			if constexpr (LeastSignificantBitFirst)
			{
				_Buffer |= Value << _Count;
			}
			else
			{
				_Buffer |= Value << (Width - _Count - Length);
			}

			_Count += Length;
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
