#include "Asn1Length.hpp"

Elysium::Core::Security::Cryptography::Asn1::Asn1Length::Asn1Length(const int32_t Length, const int32_t EncodedLength)
	: _Length(Length), _EncodedLength(EncodedLength)
{ }
Elysium::Core::Security::Cryptography::Asn1::Asn1Length::~Asn1Length()
{ }

const Elysium::Core::int32_t Elysium::Core::Security::Cryptography::Asn1::Asn1Length::GetLength() const
{
	return _Length;
}
const Elysium::Core::int32_t Elysium::Core::Security::Cryptography::Asn1::Asn1Length::GetEncodedLength() const
{
	return _EncodedLength;
}
