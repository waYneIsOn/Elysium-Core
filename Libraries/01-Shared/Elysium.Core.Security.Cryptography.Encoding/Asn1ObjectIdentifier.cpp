#include "Asn1ObjectIdentifier.hpp"

Elysium::Core::Security::Cryptography::Asn1::Asn1ObjectIdentifier::Asn1ObjectIdentifier(const Asn1Identifier & Identifier, const Oid & Value)
	: Elysium::Core::Security::Cryptography::Asn1::Asn1Object(Identifier),
	_Value(Value)
{ }
Elysium::Core::Security::Cryptography::Asn1::Asn1ObjectIdentifier::~Asn1ObjectIdentifier()
{ }

const Elysium::Core::Security::Cryptography::Oid & Elysium::Core::Security::Cryptography::Asn1::Asn1ObjectIdentifier::GetValue() const
{
	return _Value;
}
