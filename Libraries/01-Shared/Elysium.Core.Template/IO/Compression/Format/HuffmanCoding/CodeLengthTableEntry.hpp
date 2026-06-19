/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_CODELENGTHTABLEENTRY
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_CODELENGTHTABLEENTRY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::HuffmanCoding
{
	class CodeLengthTableEntry
	{
	public:
		constexpr CodeLengthTableEntry() = default;

		inline constexpr CodeLengthTableEntry(const Elysium::Core::Template::System::uint8_t Symbol, const Elysium::Core::Template::System::uint8_t Length) noexcept
			: _Symbol(Symbol), _Length(Length)
		{ }

		constexpr CodeLengthTableEntry(const CodeLengthTableEntry& Source) = default;

		constexpr CodeLengthTableEntry(CodeLengthTableEntry&& Right) noexcept = default;

		constexpr ~CodeLengthTableEntry() = default;
	public:
		constexpr CodeLengthTableEntry& operator=(const CodeLengthTableEntry& Source) = default;

		constexpr CodeLengthTableEntry& operator=(CodeLengthTableEntry&& Right) noexcept = default;
	public:
		inline constexpr bool GetIsValid()
		{
			return _Length > 0 && (0 <= _Symbol && 19 > _Symbol);
		}
	public:
		Elysium::Core::Template::System::uint8_t _Symbol;
		Elysium::Core::Template::System::uint8_t _Length;
	};
}
#endif
