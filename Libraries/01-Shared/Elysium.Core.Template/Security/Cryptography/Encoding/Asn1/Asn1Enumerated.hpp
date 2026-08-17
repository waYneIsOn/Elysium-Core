/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1ENUMERATED
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1ENUMERATED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATION
#include "../../../../Concepts/Enumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	template <Elysium::Core::Template::Concepts::Enumeration Enum>
	class Asn1Enumerated
	{
	public:
		constexpr Asn1Enumerated() = delete;

		inline constexpr Asn1Enumerated(const Asn1Identifier Identifier, const Enum Value)
			: _Identifier(Identifier), _Value(Value)
		{}

		constexpr Asn1Enumerated(const Asn1Enumerated& Source) = delete;

		constexpr Asn1Enumerated(Asn1Enumerated&& Right) noexcept = delete;

		constexpr ~Asn1Enumerated() = default;
	public:
		constexpr Asn1Enumerated& operator=(const Asn1Enumerated& Source) = delete;

		constexpr Asn1Enumerated& operator=(Asn1Enumerated&& Right) noexcept = delete;
	public:
		inline constexpr const Asn1Identifier& GetIdentifier() const
		{
			return _Identifier;
		}

		inline constexpr const Enum GetValue() const
		{
			return _Value;
		}
	private:
		Asn1Identifier _Identifier;
		Enum _Value;
	};
}
#endif
