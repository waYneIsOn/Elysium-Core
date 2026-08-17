/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAGCLASS
#include "Asn1TagClass.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UNIVERSALTAG
#include "Asn1UniversalTag.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	class Asn1Identifier
	{
	public:
		constexpr Asn1Identifier() = delete;

		inline constexpr Asn1Identifier(const Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1TagClass TagClass, const bool IsConstructed,
			const Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag UniversalTag, const Elysium::Core::Template::System::int32_t EncodedLength)
			: _TagClass(TagClass), _IsConstructed(IsConstructed), _UniversalTag(UniversalTag), _EncodedLength(EncodedLength)
		{ }

		constexpr Asn1Identifier(const Asn1Identifier& Source) = default;

		constexpr Asn1Identifier(Asn1Identifier&& Right) noexcept = default;

		constexpr ~Asn1Identifier() = default;
	public:
		constexpr Asn1Identifier& operator=(const Asn1Identifier& Source) = default;

		constexpr Asn1Identifier& operator=(Asn1Identifier&& Right) noexcept = default;
	public:
		inline constexpr const Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1TagClass GetTagClass() const
		{
			return _TagClass;
		}

		inline constexpr const bool GetIsConstructed() const
		{
			return _IsConstructed;
		}

		inline constexpr const Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag GetUniversalTag() const
		{
			return _UniversalTag;
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetEncodedLength() const
		{
			return _EncodedLength;
		}
	private:
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1TagClass _TagClass;
		bool _IsConstructed;
		Elysium::Core::Template::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag _UniversalTag;
		Elysium::Core::Template::System::int32_t _EncodedLength;
	};
}
#endif
