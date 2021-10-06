#include "Asn1Identifier.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::Asn1Identifier(const Asn1TagClass TagClass, const bool IsConstructed, const Asn1UniversalTag UniversalTag, const int32_t EncodedLength)
	: _TagClass(TagClass), _IsConstructed(IsConstructed), _UniversalTag(UniversalTag), _EncodedLength(EncodedLength)
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::Asn1Identifier(const Asn1Identifier & Source)
	: _TagClass(Source._TagClass), _IsConstructed(Source._IsConstructed), _UniversalTag(Source._UniversalTag), _EncodedLength(Source._EncodedLength)
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::Asn1Identifier(Asn1Identifier && Right) noexcept
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::~Asn1Identifier()
{ }

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::operator=(const Asn1Identifier& Source)
{
	if (this != &Source)
	{
		_TagClass = Source._TagClass;
		_IsConstructed = Source._IsConstructed;
		_UniversalTag = Source._UniversalTag;
		_EncodedLength = Source._EncodedLength;
	}
	return *this;
}

Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier& Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::operator=(Asn1Identifier&& Right) noexcept
{
	if (this != &Right)
	{
		_TagClass = Elysium::Core::Template::Functional::Move(Right._TagClass);
		_IsConstructed = Elysium::Core::Template::Functional::Move(Right._IsConstructed);
		_UniversalTag = Elysium::Core::Template::Functional::Move(Right._UniversalTag);
		_EncodedLength = Elysium::Core::Template::Functional::Move(Right._EncodedLength);
	}
	return *this;
}

const Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1TagClass Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::GetTagClass() const
{
	return _TagClass;
}

const bool Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::GetIsConstructed() const
{
	return _IsConstructed;
}

const Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1UniversalTag Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::GetUniversalTag() const
{
	return _UniversalTag;
}

const Elysium::Core::int32_t Elysium::Core::Security::Cryptography::Encoding::Asn1::Asn1Identifier::GetEncodedLength() const
{
	return _EncodedLength;
}
