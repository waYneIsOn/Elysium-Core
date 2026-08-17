/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_OERDECODER
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_OERDECODER

#ifdef _MSC_VER
#pragma once
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

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1STRING
#include "Asn1String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	/// <summary>
	/// "Octet Encoding Rules" Decoder
	/// 
	/// Subsets:
	/// - COER (Canonical OER)
	/// </summary>
	class OERDecoder final
	{
	public:
		constexpr OERDecoder() = default;

		constexpr OERDecoder(const OERDecoder& Source) = default;

		constexpr OERDecoder(OERDecoder&& Right) noexcept = default;

		constexpr ~OERDecoder() = default;
	public:
		constexpr OERDecoder& operator=(const OERDecoder& Source) = default;

		constexpr OERDecoder& operator=(OERDecoder&& Right) noexcept = default;
	public:
		inline constexpr const Asn1Identifier DecodeIdentifier(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		// @ToDo: concept for readable streams (both InOutStream as well as OutStream)
		template <class Stream>
		inline constexpr const Asn1Identifier DecodeIdentifier(Stream& ReadingStream)
		{
			throw;
		}

		inline constexpr const Asn1Length DecodeLength(const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		// @ToDo: concept for readable streams (both InOutStream as well as OutStream)
		template <class Stream>
		inline constexpr const Asn1Length DecodeLength(Stream& ReadingStream)
		{
			throw;
		}
	public:
		inline constexpr const Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		// @ToDo: concept for readable streams (both InOutStream as well as OutStream)
		template <class Stream>
		inline constexpr const Asn1Boolean DecodeBoolean(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, Stream& ReadingStream)
		{
			throw;
		}

		inline constexpr const Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		// @ToDo: concept for readable streams (both InOutStream as well as OutStream)
		template <class Stream>
		inline constexpr const Asn1ByteArray DecodeByteArray(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, Stream& ReadingStream)
		{
			throw;
		}

		inline constexpr const Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		// @ToDo: concept for readable streams (both InOutStream as well as OutStream)
		template <class Stream>
		inline constexpr const Asn1DateTime DecodeDateTime(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, Stream& ReadingStream)
		{
			throw;
		}

		inline constexpr const Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		// @ToDo: concept for readable streams (both InOutStream as well as OutStream)
		template <class Stream>
		inline constexpr const Asn1Integer DecodeInteger(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, Stream& ReadingStream)
		{
			throw;
		}

		inline constexpr const Asn1Null DecodeNull(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		// @ToDo: concept for readable streams (both InOutStream as well as OutStream)
		template <class Stream>
		inline constexpr const Asn1Null DecodeNull(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, Stream& ReadingStream)
		{
			throw;
		}

		inline constexpr const Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length,
			const Elysium::Core::Template::System::byte* Data, const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		// @ToDo: concept for readable streams (both InOutStream as well as OutStream)
		template <class Stream>
		inline constexpr const Asn1ObjectIdentifier DecodeObjectIdentifier(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, Stream& ReadingStream)
		{
			throw;
		}

		inline constexpr const Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, const Elysium::Core::Template::System::byte* Data,
			const Elysium::Core::Template::System::size Length)
		{
			throw;
		}

		// @ToDo: concept for readable streams (both InOutStream as well as OutStream)
		template <class Stream>
		inline constexpr const Asn1String DecodeString(const Asn1Identifier& Asn1Identifier, const Asn1Length& Asn1Length, Stream& ReadingStream)
		{
			throw;
		}
	};
}
#endif
