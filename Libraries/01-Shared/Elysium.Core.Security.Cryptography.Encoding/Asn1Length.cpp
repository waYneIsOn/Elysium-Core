#include "Asn1Length.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length::Asn1Length(const Elysium::Core::uint32_t Length, const Elysium::Core::uint32_t EncodedLength)
	: _Length(Length), _EncodedLength(EncodedLength)
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length::Asn1Length(const Asn1Length& Source)
	: _Length(Source._Length), _EncodedLength(Source._EncodedLength)
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length::Asn1Length(Asn1Length&& Right) noexcept
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length::~Asn1Length()
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length::operator=(const Asn1Length& Source)
{
	if (this != &Source)
	{
		_Length = Source._Length;
		_EncodedLength = Source._EncodedLength;
	}
	return *this;
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length::operator=(Asn1Length&& Right) noexcept
{
	if (this != &Right)
	{
		_Length = Elysium::Core::Template::Functional::Move(Right._Length);
		_EncodedLength = Elysium::Core::Template::Functional::Move(Right._EncodedLength);
	}
	return *this;
}

const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length::GetLength() const
{
	return _Length;
}
const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Length::GetEncodedLength() const
{
	return _EncodedLength;
}
