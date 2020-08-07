#include "DERDecoder.hpp"

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#include "../Elysium.Core.IO/MemoryStream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_CONVERT
#include "../Elysium.Core/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_ENDOFSTREAMEXCEPTION
#include "../Elysium.Core.IO/EndOfStreamException.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION
#include "../Elysium.Core.IO/InvalidDataException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DERDecoder()
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::~DERDecoder()
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeIdentifier(const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	return DecodeIdentifier(&Data[Offset], Length);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeIdentifier(const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeIdentifier(InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeIdentifier(IO::Stream & InputStream)
{
	int32_t EncodedLength = 0;
	byte CurrentByteValue = InputStream.ReadByte();
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

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeLength(const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeLength(InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeLength(const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeLength(InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeLength(IO::Stream & InputStream)
{
	int32_t EncodedLength = 0;
	int32_t Length = 0;

	byte CurrentByteValue = InputStream.ReadByte();
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

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Boolean Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeBoolean(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeBoolean(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Boolean Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeBoolean(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeBoolean(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Boolean Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeBoolean(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, IO::Stream & InputStream)
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

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Integer Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeInteger(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeInteger(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Integer Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeInteger(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeInteger(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Integer Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeInteger(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, IO::Stream & InputStream)
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

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeObjectIdentifier(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeObjectIdentifier(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeObjectIdentifier(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeObjectIdentifier(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeObjectIdentifier(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, IO::Stream & InputStream)
{
	const size_t OidLength = Asn1Length.GetLength();
	if (OidLength < 2)
	{	// two bytes equals three nodes
		throw IO::InvalidDataException(u8"An Oid must contain at least three nodes.");
	}

	Text::StringBuilder OidBuilder = Text::StringBuilder(OidLength + 1 + OidLength);	// start with one char16_t for each node and one for each dot in between

	// The first two nodes of the OID are encoded onto a single byte. The first node is multiplied by the decimal 40 and
	// the result is added to the value of the second node.
	byte FirstByte = InputStream.ReadByte();
	uint32_t FirstNode = FirstByte / 40;
	if (FirstNode > 2)
	{
		throw IO::InvalidDataException(u8"The first node of an Oid cannot be bigger than two.");
	}
	uint32_t SecondNode = FirstByte % 40;
	if (SecondNode > 39)
	{
		throw IO::InvalidDataException(u8"The second node of an Oid cannot be bigger than 39.");
	}

	OidBuilder.Append(Convert::ToString(FirstNode, 10));
	OidBuilder.Append(u8'.');
	OidBuilder.Append(Convert::ToString(SecondNode, 10));

	for (int32_t i = 1; i < OidLength; i++)
	{
		byte CurrentByte = InputStream.ReadByte();
		uint64_t Value = 0;
		bool IsMultipleByteEncoded;
		do 
		{
			// Node values less than or equal to 127 are encoded on one byte.
			Value <<= 7;
			Value += (uint64_t)(CurrentByte & 0x7F);

			// Node values greater than or equal to 128 are encoded on multiple bytes. Bit 7 of the leftmost byte is set to one.
			// Bits 0 through 6 of each byte contains the encoded value.
			IsMultipleByteEncoded = (CurrentByte & 0x80) > 0;
			if (IsMultipleByteEncoded)
			{
				CurrentByte = InputStream.ReadByte();
				i++;
			}
		} while (IsMultipleByteEncoded);

		OidBuilder.Append(u8'.');
		OidBuilder.Append(Convert::ToString(Value, 10));
	}

	return Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier(Asn1Identifier, Elysium::Core::Security::Cryptography::Oid::FromOidValue(OidBuilder.ToString(), Elysium::Core::Security::Cryptography::OidGroup::All));
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeString(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const Collections::Template::Array<byte>& Data, const size_t Offset, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Offset, Length);
	return DecodeString(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeString(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, const byte * Data, const size_t Length)
{
	IO::MemoryStream InputStream = IO::MemoryStream(Data, Length);
	return DecodeString(Asn1Identifier, Asn1Length, InputStream);
}
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeString(const Asn1Identifier & Asn1Identifier, const Asn1Length & Asn1Length, IO::Stream & InputStream)
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

size_t Elysium::Core::Security::Cryptography::Encoding::Asn1::DERDecoder::DecodeIdentifierTagNumber(IO::Stream & InputStream, int32_t EncodedLength)
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
