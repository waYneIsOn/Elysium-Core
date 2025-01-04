#include "Asn1Object.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object::Asn1Object(const Asn1Identifier& Identifier)
	: _Identifier(Identifier)
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object::Asn1Object(const Asn1Object& Source)
	: _Identifier(Source._Identifier)
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object::Asn1Object(Asn1Object&& Right) noexcept
	: _Identifier(Asn1TagClass::Universal, false, Asn1UniversalTag::EndOfContent, 0)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object::~Asn1Object()
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object::operator=(const Asn1Object & Source)
{
	if (this != &Source)
	{
		_Identifier = Source._Identifier;
	}
	return *this;
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object::operator=(Asn1Object&& Right) noexcept
{
	if (this != &Right)
	{
		_Identifier = Elysium::Core::Template::Functional::Move(Right._Identifier);
	}
	return *this;
}

const Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier & Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object::GetIdentifier() const
{
	return _Identifier;
}
