/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANCODE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_HUFFMANCODING_HUFFMANCODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::HuffmanCoding
{
	class HuffmanCode
	{
	public:
		constexpr HuffmanCode() = default;

		inline constexpr HuffmanCode(const Elysium::Core::Template::System::uint32_t Bits, const Elysium::Core::Template::System::uint8_t Length)
			: _Bits(Bits), _Length(Length)
		{ }

		constexpr HuffmanCode(const HuffmanCode& Source) = default;

		constexpr HuffmanCode(HuffmanCode&& Right) noexcept = default;

		constexpr ~HuffmanCode() = default;
	public:
		constexpr HuffmanCode& operator=(const HuffmanCode& Source) = default;

		constexpr HuffmanCode& operator=(HuffmanCode&& Right) noexcept = default;
	public:
		Elysium::Core::Template::System::uint32_t _Bits;	// most algorithms limit codes to 16 bit or less, bzip2 limits it to 20 bit. so in most real world cases 32 bit should be enough!
		Elysium::Core::Template::System::uint8_t _Length;
	};
}
#endif
