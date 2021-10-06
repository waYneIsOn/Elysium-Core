#include "Asn1ByteArray.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ByteArray::Asn1ByteArray(const Asn1Identifier& Identifier, Elysium::Core::Collections::Template::Array<Elysium::Core::byte>&& Data)
	: Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Object(Identifier),
	_Data(Elysium::Core::Template::Functional::Move(Data))
{ }
Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ByteArray::~Asn1ByteArray()
{ }

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1ByteArray::GetData() const
{
	return _Data;
}
