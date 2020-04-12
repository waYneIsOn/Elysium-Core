#include "Asn1Length.hpp"

Elysium::Core::Security::Cryptography::Asn1::Asn1Length::Asn1Length(const int32_t Length, const int32_t EncodedLength)
	: _Length(Length), _EncodedLength(EncodedLength)
{ }
Elysium::Core::Security::Cryptography::Asn1::Asn1Length::~Asn1Length()
{ }
