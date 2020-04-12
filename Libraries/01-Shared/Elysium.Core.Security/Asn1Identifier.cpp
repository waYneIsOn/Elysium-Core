#include "Asn1Identifier.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Security::Cryptography::Asn1::Asn1Identifier::Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const Asn1TagNumber TagNumber, const int32_t EncodedLength)
	: _TagClass(TagClass), _IsConstructed(IsConstructed), _TagNumber(TagNumber), _EncodedLength(EncodedLength)
{ }
Elysium::Core::Security::Cryptography::Asn1::Asn1Identifier::Asn1Identifier(const Asn1Identifier & Source)
	: _TagClass(Source._TagClass), _IsConstructed(Source._IsConstructed), _TagNumber(Source._TagNumber), _EncodedLength(Source._EncodedLength)
{ }
Elysium::Core::Security::Cryptography::Asn1::Asn1Identifier::~Asn1Identifier()
{ }
