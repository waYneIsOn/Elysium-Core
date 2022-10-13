/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVE
#define ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_BINARYREADER
#include "BinaryReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_GZIPSTREAM_VECTOROFZIPARCHIVEENTRY
#include "VectorOfZipArchiveEntry.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVEENTRY
#include "ZipArchiveEntry.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVEMODE
#include "ZipArchiveMode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
	class ELYSIUM_CORE_API ZipArchive final
	{
		friend class ZipArchiveEntry;
	public:
		ZipArchive(Elysium::Core::IO::Stream& Stream, const Elysium::Core::IO::Compression::ZipArchiveMode Mode, const bool LeaveOpen, 
			Elysium::Core::Text::Encoding& EntryNameEncoding);
		ZipArchive(const ZipArchive& Source) = delete;
		ZipArchive(ZipArchive&& Right) noexcept = delete;
		~ZipArchive();

		ZipArchive& operator=(const ZipArchive& Source) = delete;
		ZipArchive& operator=(ZipArchive&& Right) noexcept = delete;

		const VectorOfZipArchiveEntry GetEntries() const;
		const ZipArchiveMode GetMode() const;
	private:
		Elysium::Core::IO::Stream& _Stream;
		const ZipArchiveMode _Mode;
		const Elysium::Core::Text::Encoding& _Encoding;
		BinaryReader _Reader;

		Elysium::Core::uint16_t _TotalNumberOfCentralDirectoryRecords = 0;
		Elysium::Core::uint32_t _OffsetToCentralDirectory = 0;
		VectorOfZipArchiveEntry _Entries;

		static const Elysium::Core::uint8_t _SizeOfBlockEndOfCentralDirectoryWithSignature = 22;

		static const Elysium::Core::uint32_t _SignatureEntry = 0x04034B50;
		static const Elysium::Core::uint32_t _SignatureEndOfCentralDirectory = 0x06054B50;

		Elysium::Core::IO::Stream& GetStream();
		const Elysium::Core::Text::Encoding& GetEntryNameEncoding() const;

		void ReadCentralDirectory();
		void ReadEndOfCentralDirectory();
	};
}
#endif
