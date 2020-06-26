#include "Asn1Boolean.hpp"

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Boolean::Asn1Boolean(const Asn1Identifier & Identifier, const bool Value)
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(Identifier),
	_Value(Value)
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Boolean::~Asn1Boolean()
{ }

const bool Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Boolean::GetValue() const
{
	return _Value;
}
