/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECTIDENTIFIER
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1OBJECTIDENTIFIER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OID
#include "../Oid.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	class Asn1ObjectIdentifier
	{
	public:
		constexpr Asn1ObjectIdentifier() = delete;

		inline constexpr Asn1ObjectIdentifier(const Asn1Identifier& Identifier, const Oid& Value)
			: _Identifier(Identifier), _Value(Value)
		{ }

		constexpr Asn1ObjectIdentifier(const Asn1ObjectIdentifier& Source) = delete;

		constexpr Asn1ObjectIdentifier(Asn1ObjectIdentifier&& Right) noexcept = delete;

		constexpr ~Asn1ObjectIdentifier() = default;
	public:
		constexpr Asn1ObjectIdentifier& operator=(const Asn1ObjectIdentifier& Source) = delete;

		constexpr Asn1ObjectIdentifier& operator=(Asn1ObjectIdentifier&& Right) noexcept = delete;
	public:
		inline constexpr const Oid& GetValue() const
		{
			return _Value;
		}
	private:
		Asn1Identifier _Identifier;
		Oid _Value;
	};
}
#endif
