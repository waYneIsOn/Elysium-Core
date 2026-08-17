/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_BERDECODER
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_BERDECODER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VIEW_SPAN
#include "../../../../Container/View/Span.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTEXCEPTION
#include "../../../../Exceptions/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTNULLEXCEPTION
#include "../../../../Exceptions/ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BOOLEAN
#include "Asn1Boolean.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BYTEARRAY
#include "Asn1ByteArray.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1DATETIME
#include "Asn1DateTime.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1INTEGER
#include "Asn1Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1LENGTH
#include "Asn1Length.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NULL
#include "Asn1Null.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECTIDENTIFIER
#include "Asn1ObjectIdentifier.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UTF8STRING
#include "Asn1Utf8String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../../../../Text/Convert.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	/// <summary>
	/// "Basic Encoding Rules" Decoder
	/// 
	/// Subsets:
	/// - CER (Canonical Encoding Rules)
	/// - DER (Distinguished Encoding Rules)
	/// - LBER (Lightweight BER)
	/// </summary>
	// @ToDo: concept for Validator
	template <class Validator>
	class BERDecoder
	{
	public:
		constexpr BERDecoder() = default;

		constexpr BERDecoder(const BERDecoder& Source) = default;

		constexpr BERDecoder(BERDecoder&& Right) noexcept = default;

		constexpr ~BERDecoder() = default;
	public:
		constexpr BERDecoder& operator=(const BERDecoder& Source) = default;

		constexpr BERDecoder& operator=(BERDecoder&& Right) noexcept = default;
	public:
		inline constexpr const Asn1Identifier DecodeIdentifier(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			/*
			if (nullptr == Data)
			{
				throw Elysium::Core::Template::Exceptions::ArgumentNullException(u8"Data");
			}
			if (0 == Length)
			{
				throw Elysium::Core::Template::Exceptions::ArgumentException(u8"Length");
			}
			*/
			const Elysium::Core::Template::System::byte CurrentByteValue = Data[0];

			const Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1TagClass TagClass =
				static_cast<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1TagClass>(CurrentByteValue >> 6);  // first two bits
			const bool IsConstructed = (CurrentByteValue & 0x20) != 0;    // third bit
			const Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag TagNumber =
				static_cast<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag>(CurrentByteValue & 0x1F); // other five bits

			//const bool TagClassValidationResult = _Validator.ValidateTagClass(TagClass);

			if (0x1E < static_cast<Elysium::Core::Template::System::uint8_t>(TagNumber))
			{	// If Tag is less than 30, it's a single octet identifier.
				return Asn1Identifier(TagClass, IsConstructed, TagNumber, 1);
			}
			else
			{	// Otherwise it's a multiple octet identifier (high-tag-number form) which means we need to read n more byte.
				Elysium::Core::Template::System::int32_t EncodedLength = 1;
				const Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag RevisedTagNumber = 
					static_cast<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag>(DecodeIdentifierTagNumber(Data, Length, EncodedLength));

				return Asn1Identifier(TagClass, IsConstructed, RevisedTagNumber, EncodedLength);
			}
		}

		inline constexpr const Asn1Identifier DecodeIdentifier(const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeIdentifier(DataView.GetData(), DataView.GetLength());
		}

		// @ToDo: use compositional streams asap
		template <class Stream>
		inline constexpr const Asn1Identifier DecodeIdentifier(Stream& InputStream)
		{
			Elysium::Core::Template::System::int32_t EncodedLength = 0;
			Elysium::Core::Template::System::byte CurrentByteValue = InputStream.ReadByte();
			if (CurrentByteValue < 0)
			{
				throw;
				//throw IO::EndOfStreamException();
			}
			EncodedLength++;
			Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1TagClass TagClass =
				(Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1TagClass)(CurrentByteValue >> 6);  // read the first two bits
			bool IsConstructed = (CurrentByteValue & 0x20) != 0;    // read the third bit
			Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag TagNumber =
				(Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag)(CurrentByteValue & 0x1F); // read the other five bits. if Tag is less than 30, it's a single octet identifier
			if ((int)TagNumber == 0x1F)
			{   // if Tag is 30 or more, it's a multiple octet identifier which means we need to read at least one more byte
				TagNumber = static_cast<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag>(DecodeIdentifierTagNumber(InputStream, EncodedLength));
			}

			return Asn1Identifier(TagClass, IsConstructed, TagNumber, EncodedLength);
		}

		inline constexpr const Asn1Length DecodeLength(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		inline constexpr const Asn1Length DecodeLength(const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeLength(DataView.GetData(), DataView.GetLength());
		}

		// @ToDo: use compositional streams asap
		template <class Stream>
		inline constexpr const Asn1Length DecodeLength(Stream& InputStream)
		{
			Elysium::Core::Template::System::int32_t EncodedLength = 0;
			Elysium::Core::Template::System::int32_t Length = 0;

			Elysium::Core::Template::System::byte CurrentByteValue = InputStream.ReadByte();
			EncodedLength++;
			if (CurrentByteValue < 0)
			{
				throw;
				//throw IO::EndOfStreamException();
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
					Elysium::Core::Template::System::int32_t NextByteValue = InputStream.ReadByte();
					EncodedLength++;
					if (NextByteValue < 0)
					{
						throw;
						//throw IO::EndOfStreamException();
					}
					Length = (Length << 8) + NextByteValue;
				}
			}

			return Asn1Length(Length, EncodedLength);
		}
	public:
		inline constexpr const Asn1Boolean DecodeBoolean(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		inline constexpr const Asn1Boolean DecodeBoolean(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length,
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeBoolean(Asn1Identifier, Asn1Length, DataView.GetData(), DataView.GetLength());
		}

		// @ToDo: use compositional streams asap
		template <class Stream>
		inline constexpr const Asn1Boolean DecodeBoolean(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, Stream& InputStream)
		{
			bool Value = false;
			if (Asn1Length.GetLength() > 0)
			{
				// ToDo: can a DER-encoded boolean actually be represented using zero or more than one byte?
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Data(Asn1Length.GetLength());
				Elysium::Core::Template::System::size TotalBytesRead = 0;
				while (TotalBytesRead < Data.GetLength())
				{
					Elysium::Core::Template::System::size BytesRead = InputStream.Read(&Data[TotalBytesRead], Data.GetLength() - TotalBytesRead);
					if (BytesRead < 0)
					{
						throw;
						//throw IO::EndOfStreamException();
					}
					TotalBytesRead += BytesRead;
				}
				Value = Data[0] != 0x00;
			}
			return Asn1Boolean(Asn1Identifier, Value);
		}

		inline constexpr const Asn1ByteArray DecodeByteArray(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, const Elysium::Core::Template::System::byte* Data, 
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		inline constexpr const Asn1ByteArray DecodeByteArray(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length,
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeByteArray(Asn1Identifier, Asn1Length, DataView.GetData(), DataView.GetLength());
		}

		// @ToDo: use compositional streams asap
		template <class Stream>
		inline constexpr const Asn1ByteArray DecodeByteArray(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, Stream& InputStream)
		{
			const Elysium::Core::Template::System::size Length = Asn1Length.GetLength();
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Bytes(Length);
			Elysium::Core::Template::System::size TotalBytesRead = 0;
			do
			{
				const Elysium::Core::Template::System::size BytesRead = InputStream.Read(&Bytes[TotalBytesRead], Length - TotalBytesRead);
				TotalBytesRead += BytesRead;
			} while (TotalBytesRead != Length);

			return Asn1ByteArray(Asn1Identifier, Elysium::Core::Template::Functional::Move(Bytes));
		}

		inline constexpr const Asn1DateTime DecodeDateTime(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		inline constexpr const Asn1DateTime DecodeDateTime(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length,
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeDateTime(Asn1Identifier, Asn1Length, DataView.GetData(), DataView.GetLength());
		}
		
		// @ToDo: use compositional streams asap
		template <class Stream>
		inline constexpr const Asn1DateTime DecodeDateTime(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, Stream& InputStream)
		{
			const Elysium::Core::Template::System::int32_t Length = Asn1Length.GetLength();
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Bytes(Length);
			for (Elysium::Core::Template::System::int32_t i = 0; i < Length; i++)
			{
				Bytes[i] = InputStream.ReadByte();
			}

			switch (Asn1Identifier.GetUniversalTag())
			{
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::UTCTime:
			{
				//const Elysium::Core::Template::Text::String<char8_t> Value = Elysium::Core::Text::Encoding::UTF8().GetString(&Bytes[0], Length);
				const Elysium::Core::Template::Text::String<char8_t> Value(reinterpret_cast<char8_t*>(&Bytes[0]), Length);
				if (Value.EndsWith(u8"Z"))
				{	// "YYMMDDhhmm[ss]Z
					const Elysium::Core::Template::System::int32_t Year = 1900 + Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[0], 2, 10);
					const Elysium::Core::Template::System::int32_t Month = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[2], 2, 10);
					const Elysium::Core::Template::System::int32_t Day = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[4], 2, 10);
					switch (Value.GetLength())
					{
					case 11:
						return Asn1DateTime(Asn1Identifier, Elysium::Core::Template::Chrono::DateTime(
							Year > 1950 ? Year : Year + 100, Month, Day,
							Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[6], 2, 10),
							Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[8], 2, 10),
							0, 0, Elysium::Core::Template::Chrono::DateTimeKind::Utc
						));
					case 13:
						return Asn1DateTime(Asn1Identifier, Elysium::Core::Template::Chrono::DateTime(
							Year > 1950 ? Year : Year + 100, Month, Day,
							Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[6], 2, 10),
							Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[8], 2, 10),
							Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[10], 2, 10),
							0, Elysium::Core::Template::Chrono::DateTimeKind::Utc
						));
					default:
						// ToDo: while this shouldn't ever happen, throw a specific exception as data is invalid
						throw 1;
					}
				}
				else
				{	// "YYMMDDhhmm[ss](+|-)hhmm"
					// @ToDo:
					throw 1;
				}
			}
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::GeneralizedTime:
			{
				/*
				* local time:					YYYYMMDDHH[MM[SS[.fff]]]
				* UTC time:						YYYYMMDDHH[MM[SS[.fff]]]Z
				* difference local/utc time:	YYYYMMDDHH[MM[SS[.fff]]]+-HHMM
				*/
				//const Elysium::Core::Template::Text::String<char8_t> Value = Elysium::Core::Text::Encoding::UTF8().GetString(&Bytes[0], Length);
				const Elysium::Core::Template::Text::String<char8_t> Value(reinterpret_cast<char8_t*>(&Bytes[0]), Length);
				if (Value.EndsWith(u8"Z"))
				{
					const Elysium::Core::Template::System::int32_t Year = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[0], 4, 10);
					const Elysium::Core::Template::System::int32_t Month = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[4], 2, 10);
					const Elysium::Core::Template::System::int32_t Day = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[6], 2, 10);
					const Elysium::Core::Template::System::int32_t Hour = Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[8], 2, 10);
					switch (Value.GetLength())
					{	// YYYYMMDDhhmmssZ
					case 15:
						return Asn1DateTime(Asn1Identifier, Elysium::Core::Template::Chrono::DateTime(
							Year, Month, Day, Hour,
							Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[10], 2, 10),
							Elysium::Core::Template::Text::Convert<char8_t>::ToInt32(&Value[12], 2, 10),
							0, Elysium::Core::Template::Chrono::DateTimeKind::Utc
						));
					default:
						// @ToDo
						throw 1;
					}
				}
				else
				{
					// @ToDo:
					throw 1;
				}
			}
			default:
				throw;
				//throw NotImplementedException(u8"Unhandled Asn1UniversalTag for DateTime.");
			}
		}
		
		inline constexpr const Asn1Integer DecodeInteger(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		inline constexpr const Asn1Integer DecodeInteger(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length,
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeInteger(Asn1Identifier, Asn1Length, DataView.GetData(), DataView.GetLength());
		}

		// @ToDo: use compositional streams asap
		template <class Stream>
		inline constexpr const Asn1Integer DecodeInteger(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, Stream& InputStream)
		{
			if (Asn1Length.GetLength() == 0)
			{
				// @ToDo: can this ever occurre? if so, should we just "return Asn1Integer(Asn1Identifier, Math::Numerics::BigInteger(0));"?
				//throw NotImplementedException();
				throw;
			}
			else
			{
				Elysium::Core::Template::System::int32_t FirstByteValue = InputStream.ReadByte();
				if (FirstByteValue < 0)
				{
					//throw IO::EndOfStreamException();
					throw;
				}

				Elysium::Core::Template::Math::Numerics::BigInteger<> Value = (FirstByteValue & 0x80) != 0 ?
					Elysium::Core::Template::Math::Numerics::BigInteger<>(-1) : Elysium::Core::Template::Math::Numerics::BigInteger<>(0);
				Value = (Value << 8) | FirstByteValue;

				Elysium::Core::Template::System::int32_t CurrentByteValue;
				for (int i = 1; i < Asn1Length.GetLength(); i++)
				{
					CurrentByteValue = InputStream.ReadByte();
					Value = (Value << 8) | CurrentByteValue;
				}
				return Asn1Integer(Asn1Identifier, Value);
			}
		}

		inline constexpr const Asn1Null DecodeNull(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		inline constexpr const Asn1Null DecodeNull(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length,
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeNull(Asn1Identifier, Asn1Length, DataView.GetData(), DataView.GetLength());
		}

		inline constexpr const Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, 
			const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		inline constexpr const Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length,
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeObjectIdentifier(Asn1Identifier, Asn1Length, DataView.GetData(), DataView.GetLength());
		}

		// @ToDo: use compositional streams asap
		template <class Stream>
		inline constexpr const Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, Stream& InputStream)
		{
			const Elysium::Core::Template::System::size OidLength = Asn1Length.GetLength();
			if (OidLength < 2)
			{	// two bytes equals three nodes
				throw;
				//throw IO::InvalidDataException(u8"An Oid must contain at least three nodes.");
			}

			// start with one char8_t for each node and one for each dot in between
			Elysium::Core::Template::Container::Vector<char8_t> OidBuilder(OidLength + 1 + OidLength);
			OidBuilder.Clear();

			// The first two nodes of the OID are encoded onto a single byte. The first node is multiplied by the decimal 40 and
			// the result is added to the value of the second node.
			Elysium::Core::Template::System::byte FirstByte = InputStream.ReadByte();
			Elysium::Core::Template::System::uint32_t FirstNode = FirstByte / 40;
			if (FirstNode > 2)
			{
				throw;
				//throw IO::InvalidDataException(u8"The first node of an Oid cannot be bigger than two.");
			}
			Elysium::Core::Template::System::uint32_t SecondNode = FirstByte % 40;
			if (SecondNode > 39)
			{
				throw;
				//throw IO::InvalidDataException(u8"The second node of an Oid cannot be bigger than 39.");
			}

			Elysium::Core::Template::Text::String<char8_t> FN = Elysium::Core::Template::Text::Convert<char8_t>::ToString(FirstNode, 10);
			Elysium::Core::Template::Text::String<char8_t> SN = Elysium::Core::Template::Text::Convert<char8_t>::ToString(SecondNode, 10);

			OidBuilder.PushBackRange(&FN[0], FN.GetLength());
			OidBuilder.PushBack(u8'.');
			OidBuilder.PushBackRange(&SN[0], SN.GetLength());

			for (Elysium::Core::Template::System::int32_t i = 1; i < OidLength; i++)
			{
				Elysium::Core::Template::System::byte CurrentByte = InputStream.ReadByte();
				Elysium::Core::Template::System::uint64_t Value = 0;
				bool IsMultipleByteEncoded;
				do
				{
					// Node values less than or equal to 127 are encoded on one byte.
					Value <<= 7;
					Value += (Elysium::Core::Template::System::uint64_t)(CurrentByte & 0x7F);

					// Node values greater than or equal to 128 are encoded on multiple bytes. Bit 7 of the leftmost byte is set to one.
					// Bits 0 through 6 of each byte contains the encoded value.
					IsMultipleByteEncoded = (CurrentByte & 0x80) > 0;
					if (IsMultipleByteEncoded)
					{
						CurrentByte = InputStream.ReadByte();
						i++;
					}
				} while (IsMultipleByteEncoded);

				Elysium::Core::Template::Text::String<char8_t> V = Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);

				OidBuilder.PushBack(u8'.');
				OidBuilder.PushBackRange(&V[0], V.GetLength());
			}
			OidBuilder.PushBack(u8'\0');

			return Asn1ObjectIdentifier(Asn1Identifier, Oid::FromOidValue(&OidBuilder[0], OidGroup::All));
		}

		inline constexpr const Asn1Utf8String DecodeUtf8String(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		inline constexpr const Asn1Utf8String DecodeUtf8String(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length,
			const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeUtf8String(Asn1Identifier, Asn1Length, DataView.GetData(), DataView.GetLength());
		}

		// @ToDo: use compositional streams asap
		template <class Stream>
		inline constexpr const Asn1Utf8String DecodeUtf8String(const Asn1Identifier Asn1Identifier, const Asn1Length Asn1Length, Stream& InputStream)
		{
			const Elysium::Core::Template::System::uint32_t Length = Asn1Length.GetLength();
			if (Length == 0)
			{
				return Asn1Utf8String(Asn1Identifier, nullptr, 0);
			}

			switch (Asn1Identifier.GetUniversalTag())
			{
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::IA5String:
				// International Alphabet 5 (International ASCII)
				[[fallthrough]];
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::PrintableString:
				// Upper and lower case letters, digits, space, apostrophe, left/right parenthesis, plus sign, comma, hyphen, full stop, solidus, colon, 
				// equal sign and question mark.
				[[fallthrough]];
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::TeletexString:
				// Latin-1 (ISO 8859-1)
				[[fallthrough]];
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::UTF8String:
			{	// ...
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Bytes(Length);
				Elysium::Core::Template::System::size TotalBytesRead = 0;
				do
				{
					const Elysium::Core::Template::System::size BytesRead = InputStream.Read(&Bytes[TotalBytesRead], Length - TotalBytesRead);
					TotalBytesRead += BytesRead;
				} while (TotalBytesRead != Length);

				return Asn1Utf8String(Asn1Identifier, reinterpret_cast<char8_t*>(&Bytes[0]), Length);
			}
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::BitString:
				[[fallthrough]];
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::OctetString:
				throw;
				//throw Elysium::Core::InvalidOperationException(u8"Asn1 datatype can be interpreted in multiple ways. Please make use of DecodeByteArray(...) instead.");
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::NumericString:
			{	// 0 - 9 and whitespace
				throw 1;
			}
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::VideotexString:
			{
				throw 1;
			}
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::GraphicString:
			{
				throw 1;
			}
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::VisibleString:
			{
				throw 1;
			}
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::GeneralString:
			{
				throw 1;
			}
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::UniversalString:
			{
				throw 1;
			}
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::CharacterString:
			{
				throw 1;
			}
			case Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::BmpString:
			{
				throw 1;
			}
			default:
				throw;
				//throw NotImplementedException(u8"Unhandled Asn1UniversalTag for String.");
			}
		}
	private:
		inline constexpr const Elysium::Core::Template::System::size DecodeIdentifierTagNumber(const Elysium::Core::Template::System::byte* Data, 
			const Elysium::Core::Template::System::size Length, Elysium::Core::Template::System::int32_t& EncodedLength)
		{
			/*
			if (nullptr == Data)
			{
				throw Elysium::Core::Template::Exceptions::ArgumentNullException(u8"Data");
			}
			if (0 == Length)
			{
				throw Elysium::Core::Template::Exceptions::ArgumentException(u8"Length");
			}
			*/
			Elysium::Core::Template::System::size TagNumber = 0;
			while (true)
			{
				if (EncodedLength >= Length)
				{	// @ToDo
					throw;
				}

				Elysium::Core::Template::System::byte CurrentByteValue = Data[EncodedLength++];
				TagNumber = (TagNumber << 7) + (CurrentByteValue & 0x7F);
				if ((CurrentByteValue & 0x80) == 0)
				{
					break;
				}
			}

			return TagNumber;
		}

		// @ToDo: remove asap
		template <class Stream>
		inline constexpr const Elysium::Core::Template::System::size DecodeIdentifierTagNumber(Stream& InputStream, Elysium::Core::Template::System::int32_t& EncodedLength)
		{
			Elysium::Core::Template::System::size TagNumber = 0;
			while (true)
			{
				Elysium::Core::Template::System::int32_t CurrentByteValue = InputStream.ReadByte();
				EncodedLength++;
				if (CurrentByteValue < 0)
				{
					throw;
					//throw IO::EndOfStreamException();
				}
				TagNumber = (TagNumber << 7) + (CurrentByteValue & 0x7F);
				if ((CurrentByteValue & 0x80) == 0)
				{
					break;
				}
			}
			return TagNumber;
		}
	private:
		Validator _Validator{};
	};
}
#endif
