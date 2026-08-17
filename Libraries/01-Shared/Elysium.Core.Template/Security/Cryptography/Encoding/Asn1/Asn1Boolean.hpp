/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BOOLEAN
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BOOLEAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	class Asn1Boolean
	{
	public:
		constexpr Asn1Boolean() = delete;

		inline constexpr Asn1Boolean(const Asn1Identifier Identifier, const bool Value)
			: _Identifier(Identifier), _Value(Value)
		{ }

		constexpr Asn1Boolean(const Asn1Boolean& Source) = delete;

		constexpr Asn1Boolean(Asn1Boolean&& Right) noexcept = delete;

		constexpr ~Asn1Boolean() = default;
	public:
		constexpr Asn1Boolean& operator=(const Asn1Boolean& Source) = delete;

		constexpr Asn1Boolean& operator=(Asn1Boolean&& Right) noexcept = delete;
	public:
		inline constexpr const Asn1Identifier& GetIdentifier() const
		{
			return _Identifier;
		}

		inline constexpr const bool GetValue() const
		{
			return _Value;
		}
	private:
		Asn1Identifier _Identifier;
		bool _Value;
	};
}
#endif
