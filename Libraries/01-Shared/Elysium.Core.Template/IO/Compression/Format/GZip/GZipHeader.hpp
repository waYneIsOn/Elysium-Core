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

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::IO::Compression::Format::GZip
{
	struct GZipHeader final
	{
	public:
		inline static constexpr Elysium::Core::Template::System::byte Size = 10;

		inline static constexpr Elysium::Core::Template::System::byte MagicValue0 = 0x1F;
		inline static constexpr Elysium::Core::Template::System::byte MagicValue1 = 0x8B;

		inline static constexpr Elysium::Core::Template::System::byte CompressionMethodDeflate = 0x08;
	public:
		Elysium::Core::Template::System::byte _Id1;
		Elysium::Core::Template::System::byte _Id2;
		Elysium::Core::Template::System::byte _CompressionMethod;
		Elysium::Core::Template::System::byte _Flags;
		Elysium::Core::Template::System::uint32_t _ModificationTime;
		Elysium::Core::Template::System::byte _ExtraFlags;	// compression level hint
		Elysium::Core::Template::System::byte _OperatingSystem;

		Elysium::Core::Template::System::uint16_t _ExtraLength;
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _ExtraBuffer;

		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _NameBuffer;

		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _CommentBuffer;

		Elysium::Core::Template::System::uint16_t _Crc;
	public:
		inline const bool ValidateIds() const
		{
			return MagicValue0 == _Id1 && 0x8B == MagicValue1;
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
