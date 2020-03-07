#include "Oid.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOGRAPHICEXCEPTION
#include "CryptographicException.hpp"
#endif

Elysium::Core::Security::Cryptography::Oid::~Oid()
{ }

Elysium::Core::Security::Cryptography::Oid Elysium::Core::Security::Cryptography::Oid::FromFriendlyName(const WideString & FriendlyName, const OidGroup Group)
{
	PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_NAME_KEY, (void*)&FriendlyName[0], (uint32_t)Group);
	if (NativeOid == nullptr)
	{
		throw CryptographicException();
	}

	return Oid(NativeOid);
}
Elysium::Core::Security::Cryptography::Oid Elysium::Core::Security::Cryptography::Oid::FromOidValue(const CharString & OidValue, const OidGroup Group)
{
	PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY, (void*)&OidValue[0], (uint32_t)Group);
	if (NativeOid == nullptr)
	{
		throw CryptographicException();
	}

	return Oid(NativeOid);
}

const Elysium::Core::WideString Elysium::Core::Security::Cryptography::Oid::GetFriendlyName() const
{
	return WideString(_NativeOid->pwszName);
}
const Elysium::Core::CharString Elysium::Core::Security::Cryptography::Oid::GetValue() const
{
	return CharString(_NativeOid->pszOID);
}

Elysium::Core::Security::Cryptography::Oid::Oid(const ELYSIUM_CORE_SECURITY_CRYPTOHRAPHY_OIDPOINTER NativeOid)
	: _NativeOid(NativeOid)
{ }
