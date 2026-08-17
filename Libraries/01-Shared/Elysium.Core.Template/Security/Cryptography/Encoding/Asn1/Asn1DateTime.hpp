/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1DATETIME
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1DATETIME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIME
#include "../../../../Chrono/DateTime.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	class Asn1DateTime
	{
	public:
		constexpr Asn1DateTime() = delete;

		inline constexpr Asn1DateTime(const Asn1Identifier Identifier, const Elysium::Core::Template::Chrono::DateTime Value)
			: _Identifier(Identifier), _Value(Value)
		{ }

		constexpr Asn1DateTime(const Asn1DateTime& Source) = delete;

		constexpr Asn1DateTime(Asn1DateTime&& Right) noexcept = delete;

		constexpr ~Asn1DateTime() = default;
	public:
		Asn1DateTime& operator=(const Asn1DateTime& Source) = delete;

		Asn1DateTime& operator=(Asn1DateTime&& Right) noexcept = delete;
	public:
		inline constexpr const Asn1Identifier& GetIdentifier() const
		{
			return _Identifier;
		}

		inline constexpr const Elysium::Core::Template::Chrono::DateTime& GetValue() const
		{
			return _Value;
		}
	private:
		Asn1Identifier _Identifier;
		Elysium::Core::Template::Chrono::DateTime _Value;
	};
}
#endif
