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

namespace Elysium::Core::Template::IO::Compression::Format::Deflate
{
	struct DeflateBlockHeader final
	{
	public:
		inline static constexpr const Elysium::Core::Template::System::byte Size = 1;
	public:
		Elysium::Core::Template::System::byte _Data;
	public:
		inline const bool GetIsFinalBlock() const
		{
			return _Data & 0x01;
		}

		inline const Elysium::Core::Template::IO::Compression::Format::Deflate::DeflateBlockType GetCompressionMethod() const
		{
			return static_cast<DeflateBlockType>((_Data >> 1) & 0x03);
		}
	};
}
#endif
