/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE_CUSTOM
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE_CUSTOM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILATIONSETTINGS
#include "../../../System/CompilationSettings.hpp"
#endif

#if defined ELYSIUM_CORE_USE_CUSTOM_IMPLEMENTATION_X509CERTIFICATE
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_BERDECODER
#include "../Encoding/Asn1/BERDecoder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_VALIDATION_DERVALIDATOR
#include "../Encoding/Asn1/Validation/DERValidator.hpp"
#endif

namespace Elysium::Core::Template::Net::Security
{
	template <class InnerSink, class InnerSource>
	class TlsSession;
}

namespace Elysium::Core::Template::Security::Cryptography::X509Certificates
{
	class X509Certificate
	{
	public:
		friend class X509Chain;
		friend class X509Store;
		friend class Elysium::Core::Template::Container::Vector<X509Certificate>;

		template <class InnerSink, class InnerSource>
		friend class Elysium::Core::Template::Net::Security::TlsSession;
	private:
		constexpr X509Certificate() = default;

		inline constexpr X509Certificate(Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>&& RawData)
			: _RawData(Elysium::Core::Template::Functional::Move(RawData))
		{}
	public:
		constexpr X509Certificate(const X509Certificate& Source) = default;

		constexpr X509Certificate(X509Certificate&& Right) noexcept = default;

		constexpr ~X509Certificate() = default;
	public:
		constexpr X509Certificate& operator=(const X509Certificate& Source) = default;

		constexpr X509Certificate& operator=(X509Certificate&& Right) noexcept = default;
	public:
		inline constexpr const bool operator==(const X509Certificate& Other) const
		{
			if (this == &Other)
			{
				return true;
			}

			throw;
		}
	public:
		inline constexpr const Elysium::Core::Template::Text::String<char8_t> GetIssuer() const
		{
			throw 1;
		}

		inline constexpr const Elysium::Core::Template::Text::String<char8_t> GetSubject() const
		{
			throw 1;
		}

		inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> GetRawCertData() const
		{
			throw 1;
		}
	public:
		inline Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Export(
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ContentType ContentType, const Elysium::Core::Template::Text::StringView<char8_t>* Password)
		{
			if (ContentType != Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ContentType::Cert &&
				ContentType != Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ContentType::SerializedCert &&
				ContentType != Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ContentType::Pkcs12)
			{	// @ToDo: message
				throw Elysium::Core::Template::Exceptions::Security::Cryptography::CryptographicException(u8"");
			}

			// @ToDo
			throw 1;
		}
	public:
		inline static constexpr X509Certificate LoadFromBlob(const Elysium::Core::Template::System::byte* RawData, const Elysium::Core::Template::System::size DataLength,
			const Elysium::Core::Template::Text::StringView<char8_t> Password = u8"", const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags Flags =
			Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags::All)
		{
			throw 1;
		}

		inline static constexpr X509Certificate LoadFromFile(const char8_t* FileName,
			const Elysium::Core::Template::Text::StringView<char8_t> Password = u8"", const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags Flags =
			Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags::All)
		{
			throw 1;
		}
	private:
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::BERDecoder<Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Validation::DERValidator> _DERDecoder{};
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _RawData{};
	};
}
#endif
#endif
