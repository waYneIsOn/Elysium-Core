#include "Asn1ObjectIdentifier.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier::Asn1ObjectIdentifier(const Asn1Identifier & Identifier, const Oid & Value)
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(Identifier),
	_Value(Value)
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier::Asn1ObjectIdentifier(const Asn1ObjectIdentifier & Source)
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(*this),
	_Value(Source._Value)
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier::Asn1ObjectIdentifier(Asn1ObjectIdentifier&& Right) noexcept
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(*this),
	_Value()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier::~Asn1ObjectIdentifier()
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier::operator=(const Asn1ObjectIdentifier & Source)
{
	if (this != &Source)
	{
		_Value = Source._Value;
	}
	return *this;
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier::operator=(Asn1ObjectIdentifier&& Right) noexcept
{
	if (this != &Right)
	{
		_Value = Elysium::Core::Template::Functional::Move(Right._Value);
	}
	return *this;
}

const Elysium::Core::Security::Cryptography::Oid & Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ObjectIdentifier::GetValue() const
{
	return _Value;
}
