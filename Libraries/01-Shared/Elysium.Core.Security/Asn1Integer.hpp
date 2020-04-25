/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1INTEGER
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1INTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1NUMERIC
#include "Asn1Numeric.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_BIGINTEGER
#include "../Elysium.Core.Math/BigInteger.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1Integer final : public Asn1Numeric
	{
	public:
		Asn1Integer(const Asn1Identifier& Identifier, const Math::Numerics::BigInteger& Value);
		virtual ~Asn1Integer();
	private:
		const Math::Numerics::BigInteger _Value;
	};
}
#endif
