/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPHEADER
#define ELYSIUM_CORE_TEMPLATE_IO_COMPRESSION_FORMAT_GZIP_GZIPHEADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::GZip
{
	struct GZipHeader final
	{
	public:
		inline static constexpr const Elysium::Core::Template::System::byte Size = 10;
	public:
		Elysium::Core::Template::System::byte _Id1;
		Elysium::Core::Template::System::byte _Id2;
		Elysium::Core::Template::System::byte _CompressionMethod;
		Elysium::Core::Template::System::byte _Flags;
		Elysium::Core::Template::System::uint32_t _ModificationTime;
		Elysium::Core::Template::System::byte _ExtraFlags;	// compression level hint
		Elysium::Core::Template::System::byte _OperatingSystem;
	public:
		inline const bool ValidateIds() const
		{
			return 0x1F == _Id1 && 0x8B == _Id2;
		}

		inline const bool ValidateCompressionMethod() const
		{
			return 0x08 == _CompressionMethod;
		}
	public:
		inline const bool GetReserved7() const
		{
			return (_Flags >> 7) & 0x01;
		}

		inline const bool GetReserved6() const
		{
			return (_Flags >> 6) & 0x01;
		}

		inline const bool GetReserved5() const
		{
			return (_Flags >> 5) & 0x01;
		}

		inline const bool GetCommentExists() const
		{
			return (_Flags >> 4) & 0x01;
		}

		inline const bool GetNameExists() const
		{
			return (_Flags >> 3) & 0x01;
		}

		inline const bool GetExtraExists() const
		{
			return (_Flags >> 2) & 0x01;
		}

		inline const bool GetHeaderCrcExists() const
		{
			return (_Flags >> 1) & 0x01;
		}

		inline const bool GetTextExists() const
		{
			return (_Flags >> 0) & 0x01;
		}
	};
}
#endif
