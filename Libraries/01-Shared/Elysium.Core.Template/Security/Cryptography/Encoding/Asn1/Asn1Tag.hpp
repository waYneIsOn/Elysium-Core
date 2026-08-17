/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAG
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1TAG

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
	// @ToDo: concept for Asn1Objects
	template <class Asn1Object>
	class Asn1Tag
	{
	public:
		constexpr Asn1Tag() = delete;

		inline constexpr Asn1Tag(const Asn1Identifier& Identifier, const Asn1Object& Content, const bool IsExplicitlyNamed)
			: _Identifier(Identifier), _Content(Content), _IsExplicitlyTagged(IsExplicitlyNamed)
		{}

		constexpr Asn1Tag(const Asn1Tag& Source) = delete;

		constexpr Asn1Tag(Asn1Tag&& Right) noexcept = delete;

		constexpr ~Asn1Tag() = default;
	public:
		constexpr Asn1Tag& operator=(const Asn1Tag& Source) = delete;

		constexpr Asn1Tag& operator=(Asn1Tag&& Right) noexcept = delete;
	public:
		inline constexpr const Asn1Object& GetContent() const
		{
			return _Content;
		}

		inline constexpr const bool GetIsExplicitlyTagged() const
		{
			return _IsExplicitlyTagged;
		}
	private:
		Asn1Identifier _Identifier;
		Asn1Object& _Content;
		bool _IsExplicitlyTagged;
	};
}
#endif
