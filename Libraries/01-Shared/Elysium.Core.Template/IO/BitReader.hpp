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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO
{
	template <bool LeastSignificantBitFirst = true>
	class BitReader
	{
	public:
		constexpr BitReader() noexcept = delete;

		constexpr BitReader(const Elysium::Core::Template::System::byte* Start, const Elysium::Core::Template::System::size Length) noexcept
			: _Start(Start), _End(&_Start[Length]), _Current(Start), _BitBuffer(), _BitCounter()
		{ }

		constexpr BitReader(const BitReader& Source) = delete;

		constexpr BitReader(BitReader&& Right) noexcept = delete;

		~BitReader() = default;
	public:
		constexpr BitReader& operator=(const BitReader& Source) = delete;

		constexpr BitReader& operator=(BitReader&& Right) noexcept = delete;
	private:
		inline static constexpr const Elysium::Core::Template::System::uint8_t _SafeShiftThreshold = 56;
	private:
		inline void RepopulateBuffer()
		{
			while (_BitCounter <= _SafeShiftThreshold)
			{
				if (_End < _Current)
				{	// @ToDo:
					throw 1;
				}

				if constexpr (LeastSignificantBitFirst)
				{
					_BitBuffer |= static_cast<Elysium::Core::Template::System::uint64_t>(*_Current++) << _BitCounter;
					_BitCounter += 8;
				}
				else
				{

				}
			}
		}
	private:
		const Elysium::Core::Template::System::byte* _Start;
		const Elysium::Core::Template::System::byte* _End;

		const Elysium::Core::Template::System::byte* _Current;

		Elysium::Core::Template::System::uint64_t _BitBuffer;
		Elysium::Core::Template::System::uint8_t _BitCounter;
	};
}
#endif
