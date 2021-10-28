/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPBITFLAG
#define ELYSIUM_CORE_IO_COMPRESSION_ZIP_ZIPBITFLAG

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::IO::Compression::Zip
{
    /*
    ToDo 
    
    Bit 0: If set, indicates that the file is encrypted.

    (For Method 6 - Imploding)
    Bit 1: If the compression method used was type 6,
            Imploding, then this bit, if set, indicates
            an 8K sliding dictionary was used.  If clear,
            then a 4K sliding dictionary was used.

    Bit 2: If the compression method used was type 6,
            Imploding, then this bit, if set, indicates
            3 Shannon-Fano trees were used to encode the
            sliding dictionary output.  If clear, then 2
            Shannon-Fano trees were used.

    (For Methods 8 and 9 - Deflating)
    Bit 2  Bit 1
        0      0    Normal (-en) compression option was used.
        0      1    Maximum (-exx/-ex) compression option was used.
        1      0    Fast (-ef) compression option was used.
        1      1    Super Fast (-es) compression option was used.

    (For Method 14 - LZMA)
    Bit 1: If the compression method used was type 14,
            LZMA, then this bit, if set, indicates
            an end-of-stream (EOS) marker is used to
            mark the end of the compressed data stream.
            If clear, then an EOS marker is not present
            and the compressed data size must be known
            to extract.

    Note:  Bits 1 and 2 are undefined if the compression
            method is any other.

    Bit 3: If this bit is set, the fields crc-32, compressed
            size and uncompressed size are set to zero in the
            local header.  The correct values are put in the
            data descriptor immediately following the compressed
            data.  (Note: PKZIP version 2.04g for DOS only
            recognizes this bit for method 8 compression, newer
            versions of PKZIP recognize this bit for any
            compression method.)

    Bit 4: Reserved for use with method 8, for enhanced
            deflating.

    Bit 5: If this bit is set, this indicates that the file is
            compressed patched data.  (Note: Requires PKZIP
            version 2.70 or greater)

    Bit 6: Strong encryption.  If this bit is set, you MUST
            set the version needed to extract value to at least
            50 and you MUST also set bit 0.  If AES encryption
            is used, the version needed to extract value MUST
            be at least 51. See the section describing the Strong
            Encryption Specification for details.  Refer to the
            section in this document entitled "Incorporating PKWARE
            Proprietary Technology into Your Product" for more
            information.

    Bit 7: Currently unused.

    Bit 8: Currently unused.

    Bit 9: Currently unused.

    Bit 10: Currently unused.

    Bit 11: Language encoding flag (EFS).  If this bit is set,
            the filename and comment fields for this file
            MUST be encoded using UTF-8. (see APPENDIX D)

    Bit 12: Reserved by PKWARE for enhanced compression.

    Bit 13: Set when encrypting the Central Directory to indicate
            selected data values in the Local Header are masked to
            hide their actual values.  See the section describing
            the Strong Encryption Specification for details.  Refer
            to the section in this document entitled "Incorporating
            PKWARE Proprietary Technology into Your Product" for
            more information.

    Bit 14: Reserved by PKWARE for alternate streams.

    Bit 15: Reserved by PKWARE.
    */
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ZipBitFlag : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
	enum class ZipBitFlag
#else
#error "undefined os"
#endif
	{
		Default = 0,

		DataDescriptor = 8,

		UnicodeFileName = 2048,
	};

	inline ZipBitFlag operator|(const ZipBitFlag Left, const ZipBitFlag Right)
	{
		return static_cast<ZipBitFlag>(static_cast<Elysium::Core::uint16_t>(Left) | static_cast<Elysium::Core::uint16_t>(Right));
	}
	inline ZipBitFlag operator&(const ZipBitFlag Left, const ZipBitFlag Right)
	{
		return static_cast<ZipBitFlag>(static_cast<Elysium::Core::uint16_t>(Left) & static_cast<Elysium::Core::uint16_t>(Right));
	}
}
#endif
