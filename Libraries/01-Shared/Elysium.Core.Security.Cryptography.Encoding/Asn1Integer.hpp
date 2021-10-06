/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1INTEGER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1INTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1NUMERIC
#include "Asn1Numeric.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_BIGINTEGER
#include "../Elysium.Core.Math/BigInteger.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Encoding::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1Integer final : public Asn1Numeric
	{
	public:
		Asn1Integer(const Asn1Identifier& Identifier, const Math::Numerics::BigInteger& Value);
		Asn1Integer(const Asn1Integer& Source) = delete;
		Asn1Integer(Asn1Integer&& Right) noexcept = delete;
		virtual ~Asn1Integer();

		Asn1Integer& operator=(const Asn1Integer& Source) = delete;
		Asn1Integer& operator=(Asn1Integer&& Right) noexcept = delete;

		const Math::Numerics::BigInteger& GetValue() const;
	private:
		const Math::Numerics::BigInteger _Value;
	};
}
#endif
