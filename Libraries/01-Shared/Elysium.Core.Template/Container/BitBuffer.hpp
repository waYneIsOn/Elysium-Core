/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_BITBUFFER
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_BITBUFFER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_ARCHTECTURE
#include "../System/Architecture.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "../TypeTraits/Conditional.hpp"
#endif

#include <cassert>

namespace Elysium::Core::Template::Container
{
	template <Elysium::Core::Template::System::uint16_t BitsRequired = 64, bool LeastSignificantBitFirst = true>
	class BitBuffer
	{
		static_assert(BitsRequired > 0, "BitBuffer capacity cannot be 0.");
		static_assert(BitsRequired <= 2048, "BitBuffer capacity cannot be larger than 2048 bit.");	// @ToDo: think about this limit!
		static_assert(Elysium::Core::Template::System::Architecture::BitsPerByte == 8, "BitBuffer currently requires eight bits per byte.");
	public:
		using BufferType = 
			Elysium::Core::Template::TypeTraits::ConditionalType<BitsRequired <= 8, Elysium::Core::Template::System::uint8_t,
			Elysium::Core::Template::TypeTraits::ConditionalType<BitsRequired <= 16, Elysium::Core::Template::System::uint16_t,
			Elysium::Core::Template::TypeTraits::ConditionalType<BitsRequired <= 32, Elysium::Core::Template::System::uint32_t,
				Elysium::Core::Template::System::uint64_t>>>;

		using CountType =
			Elysium::Core::Template::TypeTraits::ConditionalType<BitsRequired <= 255, Elysium::Core::Template::System::uint8_t,
			Elysium::Core::Template::System::uint16_t>;
	public:
		inline static constexpr CountType Capacity = sizeof(BufferType) * Elysium::Core::Template::System::Architecture::BitsPerByte;

		inline static constexpr CountType SafeShiftThreshold = Capacity - Elysium::Core::Template::System::Architecture::BitsPerByte;
	public:
		constexpr BitBuffer() noexcept = default;

		constexpr BitBuffer(const BitBuffer& Source) = delete;

		constexpr BitBuffer(BitBuffer&& Right) noexcept = delete;

		constexpr ~BitBuffer() = default;
	public:
		constexpr BitBuffer<Capacity, LeastSignificantBitFirst>& operator=(const BitBuffer& Source) = delete;

		constexpr BitBuffer<Capacity, LeastSignificantBitFirst>& operator=(BitBuffer&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Returns number of used bits!
		/// </summary>
		/// <returns></returns>
		inline constexpr Elysium::Core::Template::System::uint8_t GetLength() const noexcept
		{
			return _Count;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline constexpr bool GetIsFull() const noexcept
		{
			return _Count > SafeShiftThreshold;
		}
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Bits"></param>
		/// <returns></returns>
		inline constexpr bool HasBits(const CountType Bits) noexcept
		{
			return _Count >= Bits;
		}
	public:
		inline constexpr BufferType Peek(const CountType Bits)
		{
			assert(Bits <= Capacity);

			if (0 == _Count)
			{	// @ToDo
				throw 1;
			}

			if (Bits == Capacity) ELYSIUM_CORE_PATH_UNLIKELY
			{	// handle UB (for instance 1_ui64 << 64)
				return _Buffer;
			}

			if constexpr (LeastSignificantBitFirst)
			{
				return static_cast<BufferType>(_Buffer & ((static_cast<BufferType>(1) << Bits) - 1));
			}
			else
			{
				return static_cast<BufferType>(_Buffer >> (_Count - Bits)) & ((static_cast<BufferType>(1) << Bits) - 1);
			}
		}

		inline constexpr void Consume(const CountType Bits)
		{
			assert(Bits <= Capacity);

			_Count -= Bits;

			if constexpr (LeastSignificantBitFirst)
			{
				if (Bits == Capacity) ELYSIUM_CORE_PATH_UNLIKELY
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
				if (Bits == Capacity) ELYSIUM_CORE_PATH_UNLIKELY
				{
					_Buffer = 0;
				}
				else
				{
					_Buffer &= ((static_cast<BufferType>(1) << _Count) - 1);
				}
			}
		}

		inline constexpr BufferType Read(const CountType Bits)
		{
			BufferType TemporaryValue = Peek(Bits);
			Consume(Bits);

			return TemporaryValue;
		}

		inline constexpr void AlignToByteBoundary()
		{
			const CountType BitsToSkip = (_Count % 8);
			Consume(BitsToSkip);

			assert((_Buffer & ((static_cast<BufferType>(1) << SafeShiftThreshold) - 1)) == _Buffer);
		}
	public:
		inline void Push(const Elysium::Core::Template::System::byte Byte)
		{
			assert(_Count <= SafeShiftThreshold);

			if constexpr (LeastSignificantBitFirst)
			{
				_Buffer |= static_cast<BufferType>(Byte) << _Count;
				_Count += 8;
			}
			else
			{
				_Buffer >>= 8;
				_Buffer |= static_cast<BufferType>(Byte & 0xFF) << SafeShiftThreshold;
				_Count += 8;
			}
		}

		inline void Push(const BufferType Bits, const CountType Length)
		{
			assert(_Count + Length <= Capacity);
			assert(Length <= Capacity);

			if (0 == Length)
			{
				return;
			}

			const BufferType Mask = (Length == Capacity) ? ~BufferType(0) : ((BufferType(1) << Length) - BufferType(1));
			const BufferType Value = Bits & Mask;

			if constexpr (LeastSignificantBitFirst)
			{
				_Buffer |= Value << _Count;
			}
			else
			{
				_Buffer |= Value << (Capacity - _Count - Length);
			}

			_Count += Length;
		}
	private:
		BufferType _Buffer{};
		CountType _Count{};
	};
}
#endif
