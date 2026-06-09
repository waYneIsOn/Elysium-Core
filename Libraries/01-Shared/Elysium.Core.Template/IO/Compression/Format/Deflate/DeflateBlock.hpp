/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCK
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_DEFLATE_DEFLATEBLOCK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::Deflate
{
	struct DeflateBlock final
	{
	public:
		//inline static constexpr const Elysium::Core::Template::System::byte Size = 8;
	public:
		Elysium::Core::Template::System::byte _Bla;
	public:
		inline const bool GetIsFinalBlock() const
		{
			return (_Bla >> 7) & 1;
		}

		inline const Elysium::Core::Template::System::uint16_t GetCompressionMethod() const
		{
			//return (_Bla >> 1) & 0x03;
			return (_Bla >> 5) & 0x03;
		}
	};
}
#endif
