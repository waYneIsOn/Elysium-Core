#include "Asn1String.hpp"

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::Asn1String(const Asn1Identifier & Identifier, const String & Value)
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(Identifier),
	_Value(Value)
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::~Asn1String()
{ }

const Elysium::Core::String & Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::GetValue() const
{
	return _Value;
}
