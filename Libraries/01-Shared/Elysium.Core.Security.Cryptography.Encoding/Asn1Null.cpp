#include "Asn1Null.hpp"

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Null::Asn1Null()
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(Asn1Identifier(Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1TagClass::Universal, false,
		Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag::Null, 0))
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Null::~Asn1Null()
{ }
