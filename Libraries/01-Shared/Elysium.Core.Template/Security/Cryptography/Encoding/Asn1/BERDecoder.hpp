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
	class BERDecoder final
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

		inline constexpr const Asn1Length DecodeLength(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		inline constexpr const Asn1Length DecodeLength(const Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView)
		{
			return DecodeLength(DataView.GetData(), DataView.GetLength());
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
	private:
		Validator _Validator{};
	};
}
#endif
