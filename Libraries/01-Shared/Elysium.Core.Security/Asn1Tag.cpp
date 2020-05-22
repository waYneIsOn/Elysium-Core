#include "Asn1Tag.hpp"

Elysium::Core::Security::Cryptography::Asn1::Asn1Tag::Asn1Tag(const Asn1Identifier & Identifier, const Asn1Object & Content, const bool IsExplicitlyNamed)
	: Elysium::Core::Security::Cryptography::Asn1::Asn1Object(Identifier),
	_Content(Content), _IsExplicitlyTagged(IsExplicitlyNamed)
{ }
Elysium::Core::Security::Cryptography::Asn1::Asn1Tag::~Asn1Tag()
{ }

const Elysium::Core::Security::Cryptography::Asn1::Asn1Object & Elysium::Core::Security::Cryptography::Asn1::Asn1Tag::GetContent() const
{
	return _Content;
}
const bool Elysium::Core::Security::Cryptography::Asn1::Asn1Tag::GetIsExplicitlyTagged() const
{
	return _IsExplicitlyTagged;
}
