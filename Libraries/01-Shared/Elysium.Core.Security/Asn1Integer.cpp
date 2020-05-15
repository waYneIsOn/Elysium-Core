#include "Asn1Integer.hpp"

Elysium::Core::Security::Cryptography::Asn1::Asn1Integer::Asn1Integer(const Asn1Identifier & Identifier, const Math::Numerics::BigInteger & Value)
	: Elysium::Core::Security::Cryptography::Asn1::Asn1Numeric::Asn1Numeric(Identifier),
	_Value(Elysium::Core::Math::Numerics::BigInteger(Value))
{ }
Elysium::Core::Security::Cryptography::Asn1::Asn1Integer::~Asn1Integer()
{ }

const Elysium::Core::Math::Numerics::BigInteger Elysium::Core::Security::Cryptography::Asn1::Asn1Integer::GetValue() const
{
	return _Value;
}
