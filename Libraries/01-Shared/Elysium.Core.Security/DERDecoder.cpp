#include "DERDecoder.hpp"

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#include "../Elysium.Core.IO/MemoryStream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_ENDOFSTREAMEXCEPTION
#include "../Elysium.Core.IO/EndOfStreamException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DERDecoder()
{ }
Elysium::Core::Security::Cryptography::Asn1::DERDecoder::~DERDecoder()
{ }

Elysium::Core::Security::Cryptography::Asn1::Asn1Identifier Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeIdentifier(const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeIdentifier(InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Identifier Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeIdentifier(IO::Stream & InputStream)
{
	size_t EncodedLength = 0;
	int32_t CurrentByteValue = InputStream.ReadByte();
	EncodedLength++;
	if (CurrentByteValue < 0)
	{
		throw IO::EndOfStreamException();
	}
	Asn1TagClass TagClass = (Asn1TagClass)(CurrentByteValue >> 6);  // read the first two bits
	bool IsConstructed = (CurrentByteValue & 0x20) != 0;    // read the third bit
	Asn1TagNumber TagNumber = (Asn1TagNumber)(CurrentByteValue & 0x1F); // read the other five bits. if Tag is less than 30, it's a single octet identifier
	if ((int)TagNumber == 0x1F)
	{   // if Tag is 30 or more, it's a multiple octet identifier which means we need to read at least one more byte
		TagNumber = (Asn1TagNumber)DecodeIdentifierTagNumber(InputStream, EncodedLength);
	}

	return Asn1Identifier(TagClass, IsConstructed, TagNumber, EncodedLength);
}

Elysium::Core::Security::Cryptography::Asn1::Asn1Length Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeLength(const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeLength(InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Length Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeLength(IO::Stream & InputStream)
{
	size_t EncodedLength = 0;
	size_t Length = 0;

	size_t CurrentByteValue = InputStream.ReadByte();
	EncodedLength++;
	if (CurrentByteValue < 0)
	{
		throw IO::EndOfStreamException();
	}
	if (CurrentByteValue == 0x80)
	{
		Length = -1;
	}
	else if (CurrentByteValue < 0x80)
	{
		Length = CurrentByteValue;
	}
	else
	{
		Length = 0;
		for (CurrentByteValue = CurrentByteValue & 0x7F; CurrentByteValue > 0; CurrentByteValue--)
		{
			int NextByteValue = InputStream.ReadByte();
			EncodedLength++;
			if (NextByteValue < 0)
			{
				throw IO::EndOfStreamException();
			}
			Length = (Length << 8) + NextByteValue;
		}
	}

	return Asn1Length(Length, EncodedLength);
}

Elysium::Core::Security::Cryptography::Asn1::Asn1Integer Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeInteger(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const Collections::Template::Array<byte>& Data, size_t Offset, size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeInteger(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Integer Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeInteger(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, IO::Stream & InputStream)
{
	return Asn1Integer(Asn1Identifier, Elysium::Core::Math::Numerics::BigInteger(1));
}

size_t Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeIdentifierTagNumber(IO::Stream & InputStream, size_t & EncodedLength)
{
	size_t TagNumber = 0;
	while (true)
	{
		size_t CurrentByteValue = InputStream.ReadByte();
		EncodedLength++;
		if (CurrentByteValue < 0)
		{
			throw IO::EndOfStreamException();
		}
		TagNumber = (TagNumber << 7) + (CurrentByteValue & 0x7F);
		if ((CurrentByteValue & 0x80) == 0)
		{
			break;
		}
	}
	return TagNumber;
}
