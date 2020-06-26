#include "Asn1Identifier.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const Asn1UniversalTag TagNumber, const int32_t EncodedLength)
	: _TagClass(TagClass), _IsConstructed(IsConstructed), _TagNumber(static_cast<const Elysium::Core::int32_t>(TagNumber)), _EncodedLength(EncodedLength)
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const int32_t TagNumber, const int32_t EncodedLength)
	: _TagClass(TagClass), _IsConstructed(IsConstructed), _TagNumber(TagNumber), _EncodedLength(EncodedLength)
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const Asn1UniversalTag TagNumber)
	: _TagClass(TagClass), _IsConstructed(IsConstructed), _TagNumber(static_cast<const Elysium::Core::int32_t>(TagNumber)), _EncodedLength(0)
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const int32_t TagNumber)
	: _TagClass(TagClass), _IsConstructed(IsConstructed), _TagNumber(TagNumber), _EncodedLength(0)
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::Asn1Identifier(const Asn1Identifier & Source)
	: _TagClass(Source._TagClass), _IsConstructed(Source._IsConstructed), _TagNumber(Source._TagNumber), _EncodedLength(Source._EncodedLength)
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::~Asn1Identifier()
{ }

const Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1TagClass Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::GetTagClass() const
{
	return _TagClass;
}
const bool Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::GetIsConstructed() const
{
	return _IsConstructed;
}
const Elysium::Core::int32_t Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::GetTagNumber() const
{
	return _TagNumber;
}
const Elysium::Core::int32_t Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::GetEncodedLength() const
{
	return _EncodedLength;
}
