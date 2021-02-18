#include "DeflateStream.hpp"

#ifndef ELYSIUM_CORE_IO_COMPRESSION_DEFLATE_DEFLATEENCODINGMETHOD
#include "DeflateEncodingMethod.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION
#include "InvalidDataException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, const CompressionMode CompressionMode)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(false)
{ }
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, const CompressionMode CompressionMode, const bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _BaseStream(BaseStream), _CompressionMode(CompressionMode), _CompressionLevel(CompressionLevel::Optimal), _LeaveOpen(LeaveOpen)
{ }
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, const CompressionLevel CompressionLevel)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _BaseStream(BaseStream), _CompressionMode(CompressionMode::Compress), _CompressionLevel(CompressionLevel), _LeaveOpen(false)
{ }
Elysium::Core::IO::Compression::DeflateStream::DeflateStream(Stream & BaseStream, const CompressionLevel CompressionLevel, const bool LeaveOpen)
	: Elysium::Core::IO::Stream(),
	_Buffer(DefaultBufferSize), _BaseStream(BaseStream), _CompressionMode(CompressionMode::Compress), _CompressionLevel(CompressionLevel), _LeaveOpen(LeaveOpen)
{ }
Elysium::Core::IO::Compression::DeflateStream::~DeflateStream()
{
	if (!_LeaveOpen)
	{
		_BaseStream.Close();
	}
}

const Elysium::Core::IO::Stream & Elysium::Core::IO::Compression::DeflateStream::GetBaseStream() const
{
	return _BaseStream;
}

const bool Elysium::Core::IO::Compression::DeflateStream::GetCanRead() const
{
	return _CompressionMode == CompressionMode::Decompress && _BaseStream.GetCanRead();
}

const bool Elysium::Core::IO::Compression::DeflateStream::GetCanSeek() const
{
	return false;
}

const bool Elysium::Core::IO::Compression::DeflateStream::GetCanTimeout() const
{
	return false;
}

const bool Elysium::Core::IO::Compression::DeflateStream::GetCanWrite() const
{
	return _CompressionMode == CompressionMode::Compress && _BaseStream.GetCanWrite();
}

const size_t Elysium::Core::IO::Compression::DeflateStream::GetLength() const
{	// ToDo
	throw NotSupportedException();
}

const Elysium::Core::uint64_t Elysium::Core::IO::Compression::DeflateStream::GetPosition() const
{	// ToDo
	throw NotSupportedException();
}

const Elysium::Core::uint32_t Elysium::Core::IO::Compression::DeflateStream::GetReadTimeout() const
{
	return 0;
}

const Elysium::Core::uint32_t Elysium::Core::IO::Compression::DeflateStream::GetWriteTimeout() const
{
	return 0;
}

void Elysium::Core::IO::Compression::DeflateStream::SetLength(const size_t Value)
{	// ToDo
	throw NotSupportedException();
}

void Elysium::Core::IO::Compression::DeflateStream::SetPosition(const Elysium::Core::uint64_t Position)
{	// ToDo
	throw NotSupportedException();
}

void Elysium::Core::IO::Compression::DeflateStream::Close()
{ 	// ToDo
	throw NotSupportedException();
}

void Elysium::Core::IO::Compression::DeflateStream::Flush()
{ 	// ToDo
	throw NotSupportedException();
}

const size_t Elysium::Core::IO::Compression::DeflateStream::Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin)
{	// ToDo
	throw NotSupportedException();
}

const size_t Elysium::Core::IO::Compression::DeflateStream::Read(Elysium::Core::byte * Buffer, const size_t Count)
{
	if (_CompressionMode != CompressionMode::Decompress)
	{	// ToDo: message
		throw InvalidOperationException();
	}

	bool IsLastBlock;
	do
	{
		/*
		https://tools.ietf.org/html/rfc1951#section-3.2.3
		do
			read block header from input stream.
			if stored with no compression
				skip any remaining bits in current partially processed byte
				read LEN and NLEN (see next section)
				copy LEN bytes of data to output
			otherwise
				if compressed with dynamic Huffman codes
					read representation of code trees (see subsection below)
				loop (until end of block code recognized)
					decode literal/length value from input stream
					if value < 256
						copy value (literal byte) to output stream
					otherwise
					if value = end of block (256)
						break from loop
					otherwise (value = 257..285)
						decode distance from input stream

						move backwards distance bytes in the output stream and
						copy length bytes from this position to the output stream.
				end loop
		while not last block
		*/
		// read block header from input stream.
		//IsLastBlock = (_Buffer[_CurrentByteIndex] & 0x01) == 0x01;
		//EncodingMethod = (_Buffer[_CurrentByteIndex] >> 1) & 0x02;
		IsLastBlock = GetBits(1) == 0x01;
		Deflate::DeflateEncodingMethod EncodingMethod = static_cast<Deflate::DeflateEncodingMethod>(GetBits(2) & 0x03);
		switch (EncodingMethod)
		{
		case Deflate::DeflateEncodingMethod::Store:
		{
			// skip any remaining bits in current partially processed byte
			GetBits(5);

			// read LEN and NLEN
			Elysium::Core::uint16_t LEN = (GetBits(8) << 8) | GetBits(8);
			Elysium::Core::uint16_t NLEN = (GetBits(8) << 8) | GetBits(8);
			if (LEN != ~NLEN)
			{
				throw InvalidDataException(u8"LEN doesn't match complement of NLEN");
			}

			// copy LEN bytes of data to output
			if (LEN > 0)
			{	// ToDo: copy the block
				_BaseStream.Seek(LEN, SeekOrigin::Current);
			}
			break;
		}
		case Deflate::DeflateEncodingMethod::Dynamic:
		{
			/*
			https://tools.ietf.org/html/rfc1951#section-3.2.7
			5 Bits: HLIT, # of Literal/Length codes - 257 (257 - 286)
            5 Bits: HDIST, # of Distance codes - 1        (1 - 32)
            4 Bits: HCLEN, # of Code Length codes - 4     (4 - 19)
			*/
			// read representation of code trees
			Elysium::Core::uint16_t HLIT = GetBits(5) + 257;
			Elysium::Core::uint8_t HDIST = GetBits(5) + 1;
			Elysium::Core::uint8_t HCLEN = GetBits(4) + 4;
			if (HLIT < 257 || HLIT > 286)
			{
				throw InvalidDataException(u8"HLIT");
			}
			if (HDIST < 1 || HDIST > 32)
			{
				throw InvalidDataException(u8"HDIST");
			}
			if (HCLEN < 4 || HCLEN > 19)
			{
				throw InvalidDataException(u8"HCLEN");
			}

			/*
			0 - 15: Represent code lengths of 0 - 15
				16: Copy the previous code length 3 - 6 times.
					The next 2 bits indicate repeat length
							(0 = 3, ... , 3 = 6)
						Example:  Codes 8, 16 (+2 bits 11),
								16 (+2 bits 10) will expand to
								12 code lengths of 8 (1 + 6 + 5)
				17: Repeat a code length of 0 for 3 - 10 times.
					(3 bits of length)
				18: Repeat a code length of 0 for 11 - 138 times
					(7 bits of length)
			
			(HCLEN + 4) x 3 bits: code lengths for the code length alphabet given just above, in the order:
				16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15

                These code lengths are interpreted as 3-bit integers (0-7); as above, a code length of 0 means the corresponding symbol 
				(literal/length or distance code length) is not used.
			*/
			Elysium::Core::Collections::Template::Array<Elysium::Core::uint8_t> CodeLengthsLengths =
				Elysium::Core::Collections::Template::Array<Elysium::Core::uint8_t>(19, true);
			CodeLengthsLengths[16] = GetBits(3);
			CodeLengthsLengths[17] = GetBits(3);
			CodeLengthsLengths[18] = GetBits(3);
			CodeLengthsLengths[0] = GetBits(3);
			for (Elysium::Core::uint8_t i = 0; i < HCLEN - 4; i ++)
			{
				Elysium::Core::uint8_t ActualIndex = (i % 2 == 0) ? (8 + i / 2) : (7 - i / 2);
				CodeLengthsLengths[ActualIndex] = GetBits(3);
			}

			for (Elysium::Core::uint8_t i = 0; i < CodeLengthsLengths.GetLength(); i++)
			{
				Elysium::Core::uint8_t Value = CodeLengthsLengths[i];

				int asldkjf = 45;
			}

			/*
			HLIT + 257 code lengths for the literal/length alphabet, encoded using the code length Huffman code
            HDIST + 1 code lengths for the distance alphabet, encoded using the code length Huffman code
			*/
			Elysium::Core::Collections::Template::Array<Elysium::Core::uint8_t> CodeLengths = 
				Elysium::Core::Collections::Template::Array<Elysium::Core::uint8_t>(static_cast<Elysium::Core::uint64_t>(HLIT) + HDIST);

			int asdf = 45;
		}
		[[fallthrough]]; // C26819: fallthrough is explicit
		case Deflate::DeflateEncodingMethod::Static:
		{
			/*
			loop (until end of block code recognized)
				decode literal/length value from input stream
				if value < 256
					copy value (literal byte) to output stream
				otherwise
				if value = end of block (256)
					break from loop
				otherwise (value = 257..285)
					decode distance from input stream

					move backwards distance bytes in the output stream and
					copy length bytes from this position to the output stream.
			end loop
			*/






			int asdfdfg = 45;
		}
			break;
		case Deflate::DeflateEncodingMethod::Reserved:
			throw InvalidDataException(u8"Reserved encoding method.");
		default:
			throw InvalidDataException(u8"This must never happen!");
		}
	} while (!IsLastBlock);

	throw 1;
}

Elysium::Core::byte Elysium::Core::IO::Compression::DeflateStream::ReadByte()
{
	throw NotImplementedException();
}

void Elysium::Core::IO::Compression::DeflateStream::Write(const Elysium::Core::byte * Buffer, const size_t Count)
{
	if (_CompressionMode != CompressionMode::Compress)
	{	// ToDo: message
		throw InvalidOperationException();
	}

	throw NotImplementedException();
}

void Elysium::Core::IO::Compression::DeflateStream::ReadIfNecessary()
{
	if (_BytesAvailable == 0 || _CurrentByteIndex == _BytesAvailable)
	{
		_BytesAvailable = _BaseStream.Read(&_Buffer[0], _Buffer.GetLength());
		_CurrentByteIndex = DefaultByteIndex;
	}
}

const Elysium::Core::uint8_t Elysium::Core::IO::Compression::DeflateStream::GetBits(const Elysium::Core::uint8_t Amount)
{
	/*
	https://tools.ietf.org/html/rfc1951#section-3
	+--------+
	|76543210|
	+--------+
	*/
	/*
	// since this method is only called from this class, I will skip this check!
	if (Amount > 8)
	{
		throw ArgumentException(u8"Amount");
	}
	*/
	if (_CurrentBitIndex > DefaultBitIndex)
	{
		_CurrentByteIndex++;
		_CurrentBitIndex = DefaultBitIndex;
	}
	ReadIfNecessary();

	Elysium::Core::uint32_t Result;
	if (Amount > _CurrentBitIndex + 1)
	{	// not all required bits can be read from the current byte
		const Elysium::Core::uint8_t RemainingAmount = Amount - (_CurrentBitIndex + 1);
		Result = (_Buffer[_CurrentByteIndex] >> (DefaultBitIndex - _CurrentBitIndex)) << (RemainingAmount);

		_CurrentByteIndex++;
		_CurrentBitIndex = DefaultBitIndex;
		ReadIfNecessary();

		Elysium::Core::uint8_t BitMask = (1 << RemainingAmount) - 1;
		Result |= (_Buffer[_CurrentByteIndex] >> (DefaultBitIndex - _CurrentBitIndex)) & BitMask;
		_CurrentBitIndex -= RemainingAmount;
	}
	else
	{
		Elysium::Core::uint8_t BitMask = (1 << Amount) - 1;
		Result = (_Buffer[_CurrentByteIndex] >> (DefaultBitIndex - _CurrentBitIndex)) & BitMask;
		_CurrentBitIndex -= Amount;
	}

	return Result;
}
