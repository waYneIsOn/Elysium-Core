/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BYTEARRAY
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1BYTEARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	class Asn1ByteArray
	{
	public:
		constexpr Asn1ByteArray() = delete;

		inline constexpr Asn1ByteArray(const Asn1Identifier Identifier, Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>&& Data)
			: _Identifier(Identifier), _Data(Elysium::Core::Template::Functional::Move(Data))
		{ }

		constexpr Asn1ByteArray(const Asn1ByteArray& Source) = delete;

		constexpr Asn1ByteArray(Asn1ByteArray&& Right) noexcept = delete;

		constexpr ~Asn1ByteArray() = default;
	public:
		constexpr Asn1ByteArray& operator=(const Asn1ByteArray& Source) = delete;

		constexpr Asn1ByteArray& operator=(Asn1ByteArray&& Right) noexcept = delete;
	public:
		inline constexpr const Asn1Identifier& GetIdentifier() const
		{
			return _Identifier;
		}
		
		inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte>& GetData() const
		{
			return _Data;
		}
	private:
		Asn1Identifier _Identifier;
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> _Data;
	};
}
#endif
