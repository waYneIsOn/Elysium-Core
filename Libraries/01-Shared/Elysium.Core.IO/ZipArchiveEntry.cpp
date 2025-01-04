#include "ZipArchiveEntry.hpp"

#ifndef ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION
#include "InvalidDataException.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIPARCHIVE
#include "ZipArchive.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPBITFLAG
#include "ZipBitFlag.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPCOMPRESSIONMETHOD
#include "ZipCompressionMethod.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPMADEBYPLATFORM
#include "ZipMadeByPlatform.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPVERSIONNEEDED
#include "ZipVersionNeeded.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::IO::Compression::ZipArchiveEntry::ZipArchiveEntry(ZipArchive * Archive, BinaryReader * Reader)
	: _Archive(Archive), _Reader(Reader), _FileName()
{
    ReadCentralDirectoryEntry();
}
Elysium::Core::IO::Compression::ZipArchiveEntry::ZipArchiveEntry(const ZipArchiveEntry & Source)
	: _Archive(Source._Archive), _Reader(Source._Reader), _FileName(Source._FileName)
{ }
Elysium::Core::IO::Compression::ZipArchiveEntry::ZipArchiveEntry(ZipArchiveEntry&& Right) noexcept
	: _Archive(nullptr), _Reader(nullptr), _FileName()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}
Elysium::Core::IO::Compression::ZipArchiveEntry::~ZipArchiveEntry()
{ }

Elysium::Core::IO::Compression::ZipArchiveEntry& Elysium::Core::IO::Compression::ZipArchiveEntry::operator=(const ZipArchiveEntry& Source)
{
	if (this != &Source)
	{
		_Archive = Source._Archive;
        _Reader = Source._Reader;
        _FileName = Source._FileName;
        _RelativeOffsetToFileEntry = Source._RelativeOffsetToFileEntry;
        _RelativeOffsetToCompressedData = Source._RelativeOffsetToCompressedData;
        _CompressedSize = Source._CompressedSize;
	}
	return *this;
}

Elysium::Core::IO::Compression::ZipArchiveEntry& Elysium::Core::IO::Compression::ZipArchiveEntry::operator=(ZipArchiveEntry && Right) noexcept
{
	if (this != &Right)
	{
		_Archive = Right._Archive;
		_Reader = Right._Reader;
        _FileName = Elysium::Core::Template::Functional::Move(Right._FileName);
        _RelativeOffsetToFileEntry = Right._RelativeOffsetToFileEntry;
        _RelativeOffsetToCompressedData = Right._RelativeOffsetToCompressedData;
        _CompressedSize = Right._CompressedSize;

		Right._Archive = nullptr;
        Right._Reader = nullptr;
        Right._FileName = Elysium::Core::Utf8String();
        Right._RelativeOffsetToFileEntry = 0;
        Right._RelativeOffsetToCompressedData = 0;
        Right._CompressedSize = 0;
	}
	return *this;
}

const bool Elysium::Core::IO::Compression::ZipArchiveEntry::operator==(const ZipArchiveEntry& Other)
{   // ToDo:
    throw 1;
}

const bool Elysium::Core::IO::Compression::ZipArchiveEntry::operator!=(const ZipArchiveEntry& Other)
{   // ToDo:
    throw 1;
}

const Elysium::Core::IO::Compression::ZipArchive* Elysium::Core::IO::Compression::ZipArchiveEntry::GetArchive() const
{
    return _Archive;
}

const Elysium::Core::Utf8String & Elysium::Core::IO::Compression::ZipArchiveEntry::GetFullName() const
{
    return _FileName;
}

const Elysium::Core::Utf8StringView Elysium::Core::IO::Compression::ZipArchiveEntry::GetName() const
{
    const Elysium::Core::size LastIndexOfSlash = _FileName.LastIndexOf(u8'/');
    if (LastIndexOfSlash == -1)
    {
        return Elysium::Core::Utf8StringView(&_FileName[0]);
    }
    else
    {
        return Elysium::Core::Utf8StringView(&_FileName[LastIndexOfSlash + 1], _FileName.GetLength() - LastIndexOfSlash - 1);
    }
}

Elysium::Core::IO::ReadOnlyStream Elysium::Core::IO::Compression::ZipArchiveEntry::Open()
{
    if (_RelativeOffsetToCompressedData == 0)
    {
        ReadFileEntry();
    }

    return Elysium::Core::IO::ReadOnlyStream(_Reader->GetBaseStream(), _RelativeOffsetToCompressedData, 
        static_cast<Elysium::Core::uint64_t>(_RelativeOffsetToCompressedData) + _CompressedSize);
}

void Elysium::Core::IO::Compression::ZipArchiveEntry::ReadCentralDirectoryEntry()
{
    /*
    https://en.wikipedia.org/wiki/ZIP_(file_format)#Central_directory_file_header
    Offset 	Bytes 	Description
    0 	    4 	    Central directory file header signature = 0x02014b50
    4 	    2 	    Version made by
    6 	    2 	    Version needed to extract (minimum)
    8 	    2 	    General purpose bit flag
    10 	    2 	    Compression method
    12 	    2 	    File last modification time
    14 	    2 	    File last modification date
    16 	    4 	    CRC-32 of uncompressed data
    20 	    4 	    Compressed size
    24 	    4 	    Uncompressed size
    28 	    2 	    File name length (n)
    30 	    2 	    Extra field length (m)
    32 	    2 	    File comment length (k)
    34 	    2 	    Disk number where file starts
    36 	    2 	    Internal file attributes
    38 	    4 	    External file attributes
    42 	    4 	    Relative offset of local file header. This is the number of bytes between the start of the first disk on which the file occurs, and the start of the local file header. This allows software reading the central directory to locate the position of the file inside the ZIP file.
    46 	    n 	    File name
    46+n 	m 	    Extra field
    46+n+m 	k 	    File comment
    */
    const Elysium::Core::uint32_t Signature = _Reader->ReadUInt32();
    if (Signature != _SignatureCentralDirectoryEntry)
    {
        throw InvalidDataException(u8"Central directory signature incorrect.");
    }

    const Zip::ZipMadeByPlatform VersionMadeBy = static_cast<Zip::ZipMadeByPlatform>(_Reader->ReadUInt16());
    const Zip::ZipVersionNeeded VersionNeededToExtract = static_cast<Zip::ZipVersionNeeded>(_Reader->ReadUInt16());
    const Zip::ZipBitFlag GeneralPurposeBitFlag = static_cast<Zip::ZipBitFlag>(_Reader->ReadUInt16());
    const Zip::ZipCompressionMethod CompressionMethod = static_cast<Zip::ZipCompressionMethod>(_Reader->ReadUInt16());
    const Elysium::Core::uint16_t FileLastModificationTime = _Reader->ReadUInt16();
    const Elysium::Core::uint16_t FileLastModificationDate = _Reader->ReadUInt16();
    const Elysium::Core::uint32_t CRC32Uncompressed = _Reader->ReadUInt32();
    _CompressedSize = _Reader->ReadUInt32();
    const Elysium::Core::uint32_t UncompressedSize = _Reader->ReadUInt32();
    const Elysium::Core::uint16_t FileNameLength = _Reader->ReadUInt16();
    const Elysium::Core::uint16_t ExtraFieldLength = _Reader->ReadUInt16();
    const Elysium::Core::uint16_t FileCommentLength = _Reader->ReadUInt16();
    const Elysium::Core::uint16_t DiskNumberWhereFileStarts = _Reader->ReadUInt16();
    const Elysium::Core::uint16_t InternalFileAttributes = _Reader->ReadUInt16();
    const Elysium::Core::uint32_t ExternalFileAttributes = _Reader->ReadUInt32();
    _RelativeOffsetToFileEntry = _Reader->ReadUInt32();

    Elysium::Core::Container::VectorOfByte FileNameBuffer = Elysium::Core::Container::VectorOfByte(FileNameLength);
    const Elysium::Core::size FileNameBytesRead = _Reader->ReadBytes(&FileNameBuffer[0], FileNameLength);
    if (FileNameBytesRead != FileNameLength)
    {   // ToDo
        throw 1;
    }
    _FileName = _Archive->GetEntryNameEncoding().GetString(&FileNameBuffer[0], FileNameLength);

    if (ExtraFieldLength > 0)
    {
        ReadExtraField(ExtraFieldLength);
    }

    if (FileCommentLength > 0)
    {
        Elysium::Core::Container::VectorOfByte FileCommentBuffer = Elysium::Core::Container::VectorOfByte(FileCommentLength);
        const Elysium::Core::size FileCommentBytesRead = _Reader->ReadBytes(&FileCommentBuffer[0], FileCommentLength);
        if (FileCommentBytesRead != FileCommentLength)
        {   // ToDo
            throw 1;
        }
        const Elysium::Core::Utf8String FileComment = _Archive->GetEntryNameEncoding().GetString(&FileCommentBuffer[0], FileCommentLength);
    }

    if ((GeneralPurposeBitFlag & Zip::ZipBitFlag::DataDescriptor) == Zip::ZipBitFlag::DataDescriptor)
    {
        ReadDataDescriptor();
    }
}

void Elysium::Core::IO::Compression::ZipArchiveEntry::ReadFileEntry()
{
    /*
    https://en.wikipedia.org/wiki/ZIP_(file_format)#Local_file_header
    Offset 	Bytes 	Description
    0 	    4 	    Local file header signature = 0x04034b50 (read as a little-endian number)
    4 	    2 	    Version needed to extract (minimum)
    6 	    2 	    General purpose bit flag
    8 	    2 	    Compression method
    10 	    2 	    File last modification time
    12 	    2 	    File last modification date
    14 	    4 	    CRC-32 of uncompressed data
    18 	    4 	    Compressed size
    22 	    4 	    Uncompressed size
    26 	    2 	    File name length (n)
    28 	    2 	    Extra field length (m)
    30 	    n 	    File name
    30+n 	m 	    Extra field
    */
    Elysium::Core::IO::Stream& BaseStream = _Reader->GetBaseStream();
    BaseStream.SetPosition(_RelativeOffsetToFileEntry);

    const Elysium::Core::uint32_t Signature = _Reader->ReadUInt32();
    if (Signature != _SignatureLocalFileHeader)
    {
        throw InvalidDataException(u8"Local file header signature incorrect.");
    }

    const Zip::ZipVersionNeeded VersionNeededToExtract = static_cast<Zip::ZipVersionNeeded>(_Reader->ReadUInt16());
    const Zip::ZipBitFlag GeneralPurposeBitFlag = static_cast<Zip::ZipBitFlag>(_Reader->ReadUInt16());
    const Zip::ZipCompressionMethod CompressionMethod = static_cast<Zip::ZipCompressionMethod>(_Reader->ReadUInt16());
    const Elysium::Core::uint16_t FileLastModificationTime = _Reader->ReadUInt16();
    const Elysium::Core::uint16_t FileLastModificationDate = _Reader->ReadUInt16();
    const Elysium::Core::uint32_t CRC32Uncompressed = _Reader->ReadUInt32();
    const Elysium::Core::uint32_t CompressedSize = _Reader->ReadUInt32();
    const Elysium::Core::uint32_t UncompressedSize = _Reader->ReadUInt32();
    const Elysium::Core::uint16_t FileNameLength = _Reader->ReadUInt16();
    const Elysium::Core::uint16_t ExtraFieldLength = _Reader->ReadUInt16();

    Elysium::Core::Container::VectorOfByte Buffer = Elysium::Core::Container::VectorOfByte(FileNameLength);
    Buffer.Clear();
    const Elysium::Core::size BytesRead = _Reader->ReadBytes(&Buffer[0], FileNameLength);
    if (BytesRead != FileNameLength)
    {   // ToDo
        throw 1;
    }
    const Elysium::Core::Utf8String FileName = _Archive->GetEntryNameEncoding().GetString(&Buffer[0], FileNameLength);

    if (ExtraFieldLength > 0)
    {
        ReadExtraField(ExtraFieldLength);
    }

    _RelativeOffsetToCompressedData = static_cast<Elysium::Core::uint32_t>(BaseStream.GetPosition());
    BaseStream.Seek(CompressedSize, SeekOrigin::Current);

    if ((GeneralPurposeBitFlag & Zip::ZipBitFlag::DataDescriptor) == Zip::ZipBitFlag::DataDescriptor)
    {
        ReadDataDescriptor();
    }
}

void Elysium::Core::IO::Compression::ZipArchiveEntry::ReadDataDescriptor()
{
    /*
    https://en.wikipedia.org/wiki/ZIP_(file_format)#Data_descriptor
    Offset 	Bytes 	Description
    0 	    0/4 	Optional data descriptor signature = 0x08074b50
    0/4 	4 	    CRC-32 of uncompressed data
    4/8 	4 	    Compressed size
    8/12 	4 	    Uncompressed size
    */
    const Elysium::Core::uint32_t OptionalSignature = _Reader->ReadUInt32();
    const Elysium::Core::uint32_t OptionalCRC32 = OptionalSignature == _SignatureOptionalDataDescriptor ? OptionalSignature : _Reader->ReadUInt32();
    const Elysium::Core::uint32_t OptionalCompressedSize = _Reader->ReadUInt32();
    const Elysium::Core::uint32_t OptionalUncompressedSize = _Reader->ReadUInt32();
}

void Elysium::Core::IO::Compression::ZipArchiveEntry::ReadExtraField(const Elysium::Core::uint16_t ExtraFieldLength)
{
    if (ExtraFieldLength % 4 != 0)
    {
        throw InvalidDataException(u8"Invalid extra field length.");
    }

    for (Elysium::Core::uint16_t i = 0; i < ExtraFieldLength / 4; i++)
    {
        const Elysium::Core::uint16_t Id = _Reader->ReadUInt16();
        const Elysium::Core::uint16_t Value = _Reader->ReadUInt16();
    }
}

Elysium::Core::IO::Compression::ZipArchiveEntry::ZipArchiveEntry()
	: _Archive(nullptr), _Reader(nullptr), _FileName()
{ }
