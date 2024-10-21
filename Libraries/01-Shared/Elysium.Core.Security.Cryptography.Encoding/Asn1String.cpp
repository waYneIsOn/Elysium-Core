#include "Asn1String.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::Asn1String(const Asn1Identifier& Identifier, Elysium::Core::byte* Data, Elysium::Core::size Length)
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(Identifier),
	_Data(Length)
{
	memcpy(&_Data[0], &_Data[0], Length);
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::Asn1String(const Asn1Identifier & Identifier, Elysium::Core::Container::VectorOfByte&& Data)
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(Identifier),
	_Data(Elysium::Core::Template::Functional::Move(Data))
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::~Asn1String()
{ }

const Elysium::Core::Container::VectorOfByte& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::GetData() const
{
	return _Data;
}

const Elysium::Core::Utf8StringView Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1String::GetValue() const
{
	return Elysium::Core::Utf8StringView(reinterpret_cast<char8_t>(&_Data[0]));
}
