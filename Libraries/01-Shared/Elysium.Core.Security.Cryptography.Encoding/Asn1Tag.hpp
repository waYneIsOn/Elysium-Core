/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1TAG
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1TAG

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ASN1_ASN1OBJECT
#include "Asn1Object.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Asn1
{
	class ELYSIUM_CORE_SECURITY_API Asn1Tag final : public Asn1Object
	{
	public:
		Asn1Tag(const Asn1Identifier& Identifier, const Asn1Object& Content, const bool IsExplicitlyNamed);
		Asn1Tag(const Asn1Tag& Source) = delete;
		Asn1Tag(Asn1Tag&& Right) noexcept = delete;
		virtual ~Asn1Tag();

		Asn1Tag& operator=(const Asn1Tag& Source) = delete;
		Asn1Tag& operator=(Asn1Tag&& Right) noexcept = delete;

		const Asn1Object& GetContent() const;
		const bool GetIsExplicitlyTagged() const;
	private:
		const Asn1Object& _Content;
		const bool _IsExplicitlyTagged;
	};
}
#endif
