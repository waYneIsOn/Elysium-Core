#include "Asn1DateTime.hpp"

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1DateTime::Asn1DateTime(const Asn1Identifier& Identifier, const DateTime& Value)
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(Identifier),
	_Value(Value)
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1DateTime::~Asn1DateTime()
{ }

const Elysium::Core::DateTime& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1DateTime::GetValue() const
{
	return _Value;
}
