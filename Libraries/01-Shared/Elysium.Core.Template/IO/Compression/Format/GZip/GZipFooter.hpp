/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPFOOTER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPFOOTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::GZip
{
	struct GZipFooter final
	{
	public:
		inline static constexpr const Elysium::Core::Template::System::byte Size = 8;
	public:
		Elysium::Core::Template::System::uint32_t _Crc32;
		Elysium::Core::Template::System::uint32_t _UncompressedSize;
	};
}
#endif
