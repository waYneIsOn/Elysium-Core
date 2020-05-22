#include "Asn1Object.hpp"

Elysium::Core::Security::Cryptography::Asn1::Asn1Object::~Asn1Object()
{ }

const Elysium::Core::Security::Cryptography::Asn1::Asn1Identifier & Elysium::Core::Security::Cryptography::Asn1::Asn1Object::GetIdentifier() const
{
	return _Identifier;
}

Elysium::Core::Security::Cryptography::Asn1::Asn1Object::Asn1Object(const Asn1Identifier & Identifier)
	: _Identifier(Asn1Identifier(Identifier))
{ }
