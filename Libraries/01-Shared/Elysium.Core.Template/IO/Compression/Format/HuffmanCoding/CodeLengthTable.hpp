/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_CODELENGTHTABLE
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_CODELENGTHTABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_HUFFMANCODING_CODELENGTHTABLEENTRY
#include "CodeLengthTableEntry.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::HuffmanCoding
{
	class CodeLengthTable
	{
	public:
		constexpr CodeLengthTable() = default;

		constexpr CodeLengthTable(const CodeLengthTable& Source) = default;

		constexpr CodeLengthTable(CodeLengthTable&& Right) noexcept = default;

		constexpr ~CodeLengthTable() = default;
	public:
		constexpr CodeLengthTable& operator=(const CodeLengthTable& Source) = default;

		constexpr CodeLengthTable& operator=(CodeLengthTable&& Right) noexcept = default;
	public:
		/// <summary>
		/// 
		/// CodeLength has a maximum of 7 bit.
		/// </summary>
		inline static constexpr Elysium::Core::Template::System::uint8_t FastTableBits = 7;

		/// <summary>
		/// 2^7 = 128
		/// </summary>
		inline static constexpr Elysium::Core::Template::System::uint8_t TableLength = 1 << FastTableBits;
	public:
		inline constexpr CodeLengthTableEntry& operator[](const System::size Index) noexcept
		{
			return _Entries[Index];
		}
	public:
		CodeLengthTableEntry _Entries[TableLength] = { };
	};
}
#endif
