#include "Asn1String.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::Asn1String(const Asn1Identifier & Identifier, Elysium::Core::String&& Value)
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(Identifier),
	_Value(Elysium::Core::Template::Functional::Move(Value))
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::~Asn1String()
{ }

const Elysium::Core::String & Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::GetValue() const
{
	return _Value;
}
