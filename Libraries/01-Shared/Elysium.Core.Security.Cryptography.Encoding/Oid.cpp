#include "Oid.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "CryptographicException.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>	// std::char_traits
#endif

Elysium::Core::Security::Cryptography::Oid::Oid(const Oid & Source)
	: _NativeOid(Source._NativeOid)
{ }
Elysium::Core::Security::Cryptography::Oid::~Oid()
{ }

Elysium::Core::Security::Cryptography::Oid Elysium::Core::Security::Cryptography::Oid::FromFriendlyName(const Elysium::Core::String & FriendlyName, const OidGroup Group)
{
	PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_NAME_KEY, static_cast<void*>(&Text::Encoding::UTF16LE().GetBytes(&FriendlyName[0], FriendlyName.GetLength(), sizeof(char16_t))[0]), (Elysium::Core::uint32_t)Group);
	if (NativeOid == nullptr)
	{
		throw CryptographicException(u8"The OID was not found.");
	}

	return Oid(NativeOid);
}
Elysium::Core::Security::Cryptography::Oid Elysium::Core::Security::Cryptography::Oid::FromOidValue(const Elysium::Core::String & OidValue, const OidGroup Group)
{
	PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY, static_cast<void*>((char8_t*)&OidValue[0]), (Elysium::Core::uint32_t)Group);
	if (NativeOid == nullptr)
	{
		throw CryptographicException(u8"The friendly name for the OID value was not found.");
	}

	return Oid(NativeOid);
}

const Elysium::Core::String Elysium::Core::Security::Cryptography::Oid::GetFriendlyName() const
{
	return Text::Encoding::UTF16LE().GetString((const Elysium::Core::byte*)_NativeOid->pwszName, std::char_traits<wchar_t>::length(_NativeOid->pwszName) * sizeof(wchar_t));
}
const Elysium::Core::String Elysium::Core::Security::Cryptography::Oid::GetValue() const
{
	return Text::Encoding::ASCII().GetString((const Elysium::Core::byte*)_NativeOid->pszOID, std::char_traits<char>::length(_NativeOid->pszOID) * sizeof(char));
}

Elysium::Core::Security::Cryptography::Oid::Oid(const ELYSIUM_CORE_SECURITY_CRYPTOHRAPHY_OIDPOINTER NativeOid)
	: _NativeOid(NativeOid)
{ }
