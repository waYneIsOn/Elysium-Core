#include "ZipArchive.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION
#include "InvalidDataException.hpp"
#endif

Elysium::Core::IO::Compression::ZipArchive::ZipArchive(Elysium::Core::IO::Stream& Stream, const Elysium::Core::IO::Compression::ZipArchiveMode Mode, const bool LeaveOpen, Elysium::Core::Text::Encoding& EntryNameEncoding)
    : _Stream(Stream), _Mode(Mode), _Encoding(EntryNameEncoding), _Reader(Stream, EntryNameEncoding, LeaveOpen),
    _Entries()
{
    ReadEndOfCentralDirectory();
    ReadCentralDirectory();
}
Elysium::Core::IO::Compression::ZipArchive::~ZipArchive()
{ }

const Elysium::Core::Collections::Template::List<Elysium::Core::IO::Compression::ZipArchiveEntry> Elysium::Core::IO::Compression::ZipArchive::GetEntries() const
{
    return _Entries;
}

const Elysium::Core::IO::Compression::ZipArchiveMode Elysium::Core::IO::Compression::ZipArchive::GetMode() const
{
    return _Mode;
}

Elysium::Core::IO::Stream& Elysium::Core::IO::Compression::ZipArchive::GetStream()
{
    return _Stream;
}

const Elysium::Core::Text::Encoding& Elysium::Core::IO::Compression::ZipArchive::GetEntryNameEncoding() const
{
    return _Encoding;
}

void Elysium::Core::IO::Compression::ZipArchive::ReadCentralDirectory()
{
    _Reader.GetBaseStream().SetPosition(_OffsetToCentralDirectory);

    for (Elysium::Core::uint16_t i = 0; i < _TotalNumberOfCentralDirectoryRecords; i++)
    {
        _Entries.Add(ZipArchiveEntry(this, &_Reader));
    }
}

void Elysium::Core::IO::Compression::ZipArchive::ReadEndOfCentralDirectory()
{
    /*
    https://en.wikipedia.org/wiki/ZIP_(file_format)#End_of_central_directory_record_(EOCD)
    Offset 	Bytes 	Description
    0 	    4 	    End of central directory signature = 0x06 05 4b 50
    4 	    2 	    Number of this disk
    6 	    2 	    Disk where central directory starts
    8 	    2 	    Number of central directory records on this disk
    10 	    2 	    Total number of central directory records
    12 	    4 	    Size of central directory (bytes)
    16 	    4 	    Offset of start of central directory, relative to start of archive
    20 	    2 	    Comment length (n)
    22 	    n 	    Comment
    */
    _Reader.GetBaseStream().Seek(-_SizeOfBlockEndOfCentralDirectoryWithSignature, Elysium::Core::IO::SeekOrigin::End);

    bool SignatureFound = false;
    Elysium::Core::uint32_t Signature = _Reader.ReadUInt32();
    if (Signature == _SignatureEndOfCentralDirectory)
    {
        SignatureFound = true;
    }
    else
    {   // A comment has been appended to the end of the file. As the maximum length is the one of uint16_t, we need to search through those bytes.
        // ToDo
        throw 1;
    }

    if (!SignatureFound)
    {
        throw InvalidDataException(u8"End of directory not found.");
    }

    const Elysium::Core::uint16_t NumberOfThisDisk = _Reader.ReadUInt16();
    const Elysium::Core::uint16_t DiskWhereCentralDirectoryStarts = _Reader.ReadUInt16();
    const Elysium::Core::uint16_t NumberOfCentralDirectoryRecordsOnThisDisk = _Reader.ReadUInt16();
    _TotalNumberOfCentralDirectoryRecords = _Reader.ReadUInt16();
    const Elysium::Core::uint32_t SizeOfCentralDirectory = _Reader.ReadUInt32();
    _OffsetToCentralDirectory = _Reader.ReadUInt32();
    const Elysium::Core::uint16_t CommentLength = _Reader.ReadUInt16();

    if (CommentLength > 0)
    {
        Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Buffer = 
            Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(CommentLength);
        const size_t BytesRead = _Reader.ReadBytes(&Buffer[0], CommentLength);
        if (BytesRead != CommentLength)
        {   // ToDo
            throw 1;
        }
        const Elysium::Core::String Comment = _Encoding.GetString(&Buffer[0], CommentLength);
    }
}
