/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKHEADER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKHEADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCKTYPE
#include "DeflateBlockType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Algorithm::Deflate
{
	class DeflateDecoder;
}

namespace Elysium::Core::Template::IO::Compression::Format::Deflate
{
	class DeflateBlockHeader final
	{
		friend class Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateDecoder;
	public:
		constexpr DeflateBlockHeader() noexcept = default;

		inline constexpr DeflateBlockHeader(const Elysium::Core::Template::System::byte Data) noexcept
			: _Data(Data)
		{ }

		constexpr DeflateBlockHeader(const DeflateBlockHeader& Source) = delete;

		constexpr DeflateBlockHeader(DeflateBlockHeader&& Right) noexcept = delete;

		~DeflateBlockHeader() = default;
	public:
		constexpr DeflateBlockHeader& operator=(const DeflateBlockHeader& Source) = delete;

		constexpr DeflateBlockHeader& operator=(DeflateBlockHeader&& Right) noexcept = delete;
	public:
		inline const bool GetIsFinalBlock() const
		{
			return _Data & 0x01;
		}

		inline const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType GetCompressionMethod() const
		{
			return static_cast<DeflateBlockType>((_Data >> 1) & 0x03);
		}
	public:
		inline static constexpr const Elysium::Core::Template::System::byte Size = 1;
	private:
		Elysium::Core::Template::System::byte _Data;
	};
}
#endif
