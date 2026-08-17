/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1INTEGER
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1INTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MATH_NUMERICS_BIGINTEGER
#include "../../../../Math/Numerics/BigInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	class Asn1Integer
	{
	public:
		constexpr Asn1Integer() = delete;

		inline constexpr Asn1Integer(const Asn1Identifier Identifier, const Elysium::Core::Template::Math::Numerics::BigInteger<>& Value)
			: _Identifier(Identifier), _Value(Value)
		{}

		constexpr Asn1Integer(const Asn1Integer& Source) = delete;

		constexpr Asn1Integer(Asn1Integer&& Right) noexcept = delete;

		constexpr ~Asn1Integer() = default;
	public:
		constexpr Asn1Integer& operator=(const Asn1Integer& Source) = delete;

		constexpr Asn1Integer& operator=(Asn1Integer&& Right) noexcept = delete;
	public:
		inline constexpr const Asn1Identifier& GetIdentifier() const
		{
			return _Identifier;
		}

		inline constexpr const Elysium::Core::Template::Math::Numerics::BigInteger<>& GetValue() const
		{
			return _Value;
		}
	private:
		Asn1Identifier _Identifier;
		Elysium::Core::Template::Math::Numerics::BigInteger<> _Value;
	};
}
#endif
