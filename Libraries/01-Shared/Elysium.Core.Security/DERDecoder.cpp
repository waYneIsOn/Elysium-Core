#include "DERDecoder.hpp"

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#include "../Elysium.Core.IO/MemoryStream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
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

Elysium::Core::Security::Cryptography::Asn1::Asn1Identifier Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeIdentifier(const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	return DecodeIdentifier(&Data[Offset], Length);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Identifier Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeIdentifier(const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeIdentifier(InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Identifier Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeIdentifier(IO::Stream & InputStream)
{
	int32_t EncodedLength = 0;
	int32_t CurrentByteValue = InputStream.ReadByte();
	if (CurrentByteValue < 0)
	{
		throw IO::EndOfStreamException();
	}
	EncodedLength++;
	Asn1TagClass TagClass = (Asn1TagClass)(CurrentByteValue >> 6);  // read the first two bits
	bool IsConstructed = (CurrentByteValue & 0x20) != 0;    // read the third bit
	Asn1UniversalTag TagNumber = (Asn1UniversalTag)(CurrentByteValue & 0x1F); // read the other five bits. if Tag is less than 30, it's a single octet identifier
	if ((int)TagNumber == 0x1F)
	{   // if Tag is 30 or more, it's a multiple octet identifier which means we need to read at least one more byte
		TagNumber = static_cast<Asn1UniversalTag>(DecodeIdentifierTagNumber(InputStream, EncodedLength));
	}

	return Asn1Identifier(TagClass, IsConstructed, TagNumber, EncodedLength);
}

Elysium::Core::Security::Cryptography::Asn1::Asn1Length Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeLength(const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeLength(InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Length Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeLength(const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeLength(InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Length Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeLength(IO::Stream & InputStream)
{
	int32_t EncodedLength = 0;
	int32_t Length = 0;

	int32_t CurrentByteValue = InputStream.ReadByte();
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

Elysium::Core::Security::Cryptography::Asn1::Asn1Boolean Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeBoolean(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeBoolean(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Boolean Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeBoolean(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeBoolean(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Boolean Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeBoolean(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, IO::Stream & InputStream)
{
	bool Value = false;
	if (Asn1Length.GetLength() > 0)
	{
		// ToDo: can a DER-encoded boolean actually be represented using zero or more than one byte?
		Collections::Template::Array<byte> Data = Collections::Template::Array<byte>(Asn1Length.GetLength());
		size_t TotalBytesRead = 0;
		while (TotalBytesRead < Data.GetLength())
		{
			size_t BytesRead = InputStream.Read(&Data[TotalBytesRead], Data.GetLength() - TotalBytesRead);
			if (BytesRead < 0)
			{
				throw IO::EndOfStreamException();
			}
			TotalBytesRead += BytesRead;
		}
		Value = Data[0] != 0x00;
	}
	return Asn1Boolean(Asn1Identifier, Value);
}

Elysium::Core::Security::Cryptography::Asn1::Asn1Integer Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeInteger(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeInteger(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Integer Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeInteger(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeInteger(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1Integer Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeInteger(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, IO::Stream & InputStream)
{
	if (Asn1Length.GetLength() == 0)
	{
		// ToDo: can this ever occurre? if so, should we just "return Asn1Integer(Asn1Identifier, Math::Numerics::BigInteger(0));"?
		throw NotImplementedException();
	}
	else
	{
		int32_t FirstByteValue = InputStream.ReadByte();
		if (FirstByteValue < 0)
		{
			throw IO::EndOfStreamException();
		}

		Math::Numerics::BigInteger Value = Math::Numerics::BigInteger(0);
		if ((FirstByteValue & 0x80) != 0)
		{
			Value = Math::Numerics::BigInteger(-1);
		}
		Value = (Value << 8) | FirstByteValue;
		
		int32_t CurrentByteValue;
		for (int i = 1; i < Asn1Length.GetLength(); i++)
		{
			CurrentByteValue = InputStream.ReadByte();
			Value = (Value << 8) | CurrentByteValue;
		}
		return Asn1Integer(Asn1Identifier, Value);
	}
}

Elysium::Core::Security::Cryptography::Asn1::Asn1ObjectIdentifier Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeObjectIdentifier(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeObjectIdentifier(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1ObjectIdentifier Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeObjectIdentifier(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeObjectIdentifier(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1ObjectIdentifier Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeObjectIdentifier(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, IO::Stream & InputStream)
{
	Elysium::Core::Collections::Template::Array<byte> OidBytes = Elysium::Core::Collections::Template::Array<byte>(Asn1Length.GetLength());
	InputStream.Read(&OidBytes[0], OidBytes.GetLength());


	// - The first two nodes of the OID are encoded onto a single byte. The first node is multiplied by the decimal 40 and
	//	 the result is added to the value of the second node.
	// - Node values less than or equal to 127 are encoded on one byte.
	// - Node values greater than or equal to 128 are encoded on multiple bytes. Bit 7 of the leftmost byte is set to one. 
	//	 Bits 0 through 6 of each byte contains the encoded value.


	const size_t OidLength = OidBytes.GetLength();
	if (OidLength <= 9)
	{	// fast path
		int64_t AccumulatedValue = 0;
		for (int32_t i = 0; i < OidLength; i++)
		{
			byte CurrentByte = OidBytes[i];
			AccumulatedValue <<= 7;
			AccumulatedValue |= static_cast<byte>(CurrentByte & 0x7F);
		}

		byte FirstArc;
		if (AccumulatedValue < 40)
		{
			FirstArc = 0;
		}
		else if (AccumulatedValue < 80)
		{
			FirstArc = 1;
			AccumulatedValue -= 40;
		}
		else
		{
			FirstArc = 1;
			AccumulatedValue -= 80;
		}

		throw NotImplementedException();
	}
	else
	{	// slow path
		throw NotImplementedException();
	}
}

Elysium::Core::Security::Cryptography::Asn1::Asn1String Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeString(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeString(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1String Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeString(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeString(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Asn1::Asn1String Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeString(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, IO::Stream & InputStream)
{
	const int32_t Length = Asn1Length.GetLength();
	Elysium::Core::Collections::Template::Array<byte> Bytes = Elysium::Core::Collections::Template::Array<byte>(Length);
	for (int32_t i = 0; i < Length; i++)
	{
		Bytes[i] = InputStream.ReadByte();
	}
	/*
	switch (Asn1Identifier.GetTagNumber())
	{
		case static_cast<int32_t>(Asn1UniversalTag::BitString):
			throw NotImplementedException();
		default:
			throw NotImplementedException();
	}
	
	throw NotImplementedException();
	*/
	const Elysium::Core::String Value = Elysium::Core::Text::Encoding::UTF8().GetString(&Bytes[0], Length);
	return Asn1String(Asn1Identifier, Value);
}

size_t Elysium::Core::Security::Cryptography::Asn1::DERDecoder::DecodeIdentifierTagNumber(IO::Stream & InputStream, int32_t EncodedLength)
{
	size_t TagNumber = 0;
	while (true)
	{
		int32_t CurrentByteValue = InputStream.ReadByte();
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
