/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVEENTRY
#define ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVEENTRY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_BINARYREADER
#include "BinaryReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_READONLYSTREAM
#include "ReadOnlyStream.hpp"
#endif

namespace Elysium::Core::IO::Compression
{
	class ZipArchive;

	class ELYSIUM_CORE_API ZipArchiveEntry final
	{
		friend class Elysium::Core::Template::Container::Vector<ZipArchiveEntry>;
	private:
		ZipArchiveEntry();
	public:
		//ZipArchiveEntry(ZipArchive* Archive, Stream& BaseStream);

		ZipArchiveEntry(ZipArchive* Archive, BinaryReader* Reader);

		ZipArchiveEntry(const ZipArchiveEntry& Source);

		ZipArchiveEntry(ZipArchiveEntry&& Right) noexcept;

		~ZipArchiveEntry();
	public:
		ZipArchiveEntry& operator=(const ZipArchiveEntry& Source);

		ZipArchiveEntry& operator=(ZipArchiveEntry&& Right) noexcept;
	public:
		const bool operator==(const ZipArchiveEntry& Other);

		const bool operator!=(const ZipArchiveEntry& Other);
	public:
		const Elysium::Core::IO::Compression::ZipArchive* GetArchive() const;

		const Elysium::Core::Utf8String& GetFullName() const;

		const Elysium::Core::Utf8StringView GetName() const;
	public:
		Elysium::Core::IO::ReadOnlyStream Open();
	private:
		void ReadCentralDirectoryEntry();
		void ReadFileEntry();
		void ReadExtraField(const Elysium::Core::uint16_t ExtraFieldLength);
		void ReadDataDescriptor();
	private:
		static const Elysium::Core::uint32_t _SignatureCentralDirectoryEntry = 0x02014B50;
		static const Elysium::Core::uint32_t _SignatureLocalFileHeader = 0x04034B50;
		static const Elysium::Core::uint32_t _SignatureOptionalDataDescriptor = 0x08074b50;
	private:
		ZipArchive* _Archive;
        BinaryReader* _Reader;

		Elysium::Core::Utf8String _FileName;
		Elysium::Core::uint32_t _RelativeOffsetToFileEntry = 0;
		Elysium::Core::uint32_t _RelativeOffsetToCompressedData = 0;
		Elysium::Core::uint32_t _CompressedSize = 0;
	};
}
#endif
