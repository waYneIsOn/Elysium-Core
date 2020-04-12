#include "Asn1Object.hpp"

Elysium::Core::Security::Cryptography::Asn1::Asn1Object::~Asn1Object()
{ }

Elysium::Core::Security::Cryptography::Asn1::Asn1Object::Asn1Object(const Asn1Identifier & Identifier)
	: _Identifier(Asn1Identifier(Identifier))
{ }
