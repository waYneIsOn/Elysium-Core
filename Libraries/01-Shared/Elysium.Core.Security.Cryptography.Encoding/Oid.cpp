#include "Oid.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "CryptographicException.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM
#include "../Elysium.Core.Security/System.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>	// std::char_traits
#endif

Elysium::Core::Security::Cryptography::Oid::Oid()
	: _Value(), _FriendlyName()
{ }

Elysium::Core::Security::Cryptography::Oid::Oid(Elysium::Core::String && Value, Elysium::Core::String && FriendlyName)
	: _Value(Elysium::Core::Template::Functional::Move(Value)), _FriendlyName(Elysium::Core::Template::Functional::Move(FriendlyName))
{ }

Elysium::Core::Security::Cryptography::Oid::Oid(const Oid & Source)
	: _Value(Source._Value), _FriendlyName(Source._FriendlyName)
{ }

Elysium::Core::Security::Cryptography::Oid::Oid(Oid && Right) noexcept
	: _Value(), _FriendlyName()
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Security::Cryptography::Oid::~Oid()
{ }

Elysium::Core::Security::Cryptography::Oid& Elysium::Core::Security::Cryptography::Oid::operator=(const Oid& Source)
{
	if (this != &Source)
	{
		_Value = Source._Value;
		_FriendlyName = Source._FriendlyName;
	}
	return *this;
}

Elysium::Core::Security::Cryptography::Oid& Elysium::Core::Security::Cryptography::Oid::operator=(Oid&& Right) noexcept
{
	if (this != &Right)
	{
		_Value = Elysium::Core::Template::Functional::Move(Right._Value);
		_FriendlyName = Elysium::Core::Template::Functional::Move(Right._FriendlyName);
	}
	return *this;
}

Elysium::Core::Security::Cryptography::Oid Elysium::Core::Security::Cryptography::Oid::FromFriendlyName(const Elysium::Core::String& FriendlyName, const OidGroup Group)
{
	PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_NAME_KEY, static_cast<void*>(&Text::Encoding::UTF16LE().GetBytes(&FriendlyName[0], FriendlyName.GetLength(), sizeof(char16_t))[0]), (Elysium::Core::uint32_t)Group);
	if (NativeOid == nullptr)
	{
		throw CryptographicException(u8"The OID was not found.");
	}

	return Oid(
		Elysium::Core::Template::Functional::Move(Text::Encoding::ASCII().GetString((const Elysium::Core::byte*)NativeOid->pszOID,
			std::char_traits<char>::length(NativeOid->pszOID) * sizeof(char))),
		Elysium::Core::Template::Functional::Move(Text::Encoding::UTF16LE().GetString((const Elysium::Core::byte*)NativeOid->pwszName,
			std::char_traits<wchar_t>::length(NativeOid->pwszName) * sizeof(wchar_t)))
	);
}

Elysium::Core::Security::Cryptography::Oid Elysium::Core::Security::Cryptography::Oid::FromOidValue(const Elysium::Core::String& OidValue, const OidGroup Group)
{
	PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY, static_cast<void*>((char8_t*)&OidValue[0]), (Elysium::Core::uint32_t)Group);
	if (NativeOid == nullptr)
	{
		throw CryptographicException(u8"The friendly name for the OID value was not found.");
	}

	return Oid(
		Elysium::Core::Template::Functional::Move(Text::Encoding::ASCII().GetString((const Elysium::Core::byte*)NativeOid->pszOID,
			std::char_traits<char>::length(NativeOid->pszOID) * sizeof(char))),
		Elysium::Core::Template::Functional::Move(Text::Encoding::UTF16LE().GetString((const Elysium::Core::byte*)NativeOid->pwszName,
			std::char_traits<wchar_t>::length(NativeOid->pwszName) * sizeof(wchar_t)))
	);
}

const Elysium::Core::String& Elysium::Core::Security::Cryptography::Oid::GetValue() const
{
	return _Value;
}

const Elysium::Core::String& Elysium::Core::Security::Cryptography::Oid::GetFriendlyName() const
{
	return _FriendlyName;
}
