/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1LENGTH
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1LENGTH

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	class Asn1Length
	{
	public:
		constexpr Asn1Length() = delete;

		inline constexpr Asn1Length(const Elysium::Core::Template::System::uint32_t Length, const Elysium::Core::Template::System::uint32_t EncodedLength)
			: _Length(Length), _EncodedLength(EncodedLength)
		{ }

		constexpr Asn1Length(const Asn1Length& Source) = default;

		constexpr Asn1Length(Asn1Length&& Right) noexcept = default;

		constexpr ~Asn1Length() = default;
	public:
		constexpr Asn1Length& operator=(const Asn1Length& Source) = default;

		constexpr Asn1Length& operator=(Asn1Length&& Right) noexcept = default;
	public:
		inline constexpr const Elysium::Core::Template::System::uint32_t GetLength() const
		{
			return _Length;
		}

		inline constexpr const Elysium::Core::Template::System::uint32_t GetEncodedLength() const
		{
			return _EncodedLength;
		}
	private:
		Elysium::Core::Template::System::uint32_t _Length;
		Elysium::Core::Template::System::uint32_t _EncodedLength;
	};
}
#endif
