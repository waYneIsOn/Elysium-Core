/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NULL
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NULL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
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
	class Asn1Null
	{
	public:
		inline constexpr Asn1Null()
			: _Identifier(Asn1TagClass::Universal, false, Asn1UniversalTag::Null, 0)
		{ }

		constexpr Asn1Null(const Asn1Null& Source) = delete;

		constexpr Asn1Null(Asn1Null&& Right) noexcept = delete;

		constexpr ~Asn1Null() = default;
	public:
		constexpr Asn1Null& operator=(const Asn1Null& Source) = delete;

		constexpr Asn1Null& operator=(Asn1Null&& Right) noexcept = delete;
	public:
		inline constexpr const Asn1Identifier& GetIdentifier() const
		{
			return _Identifier;
		}

	private:
		Asn1Identifier _Identifier;
	};
}
#endif
