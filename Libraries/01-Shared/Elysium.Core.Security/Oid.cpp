#include "Oid.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM
#include "System.hpp"
#endif

Elysium::Core::Security::Cryptography::Oid::Oid()
{ }
Elysium::Core::Security::Cryptography::Oid::~Oid()
{ }

Elysium::Core::Security::Cryptography::Oid Elysium::Core::Security::Cryptography::Oid::FromFriendlyName(const String & FriendlyName, const OidGroup Group)
{
	// CryptFindOIDInfo - https://docs.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptfindoidinfo
	return Oid();
}
Elysium::Core::Security::Cryptography::Oid Elysium::Core::Security::Cryptography::Oid::FromOidValue(const String & OidValue, const OidGroup Group)
{
	// CryptFindOIDInfo - https://docs.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptfindoidinfo
	return Oid();
}

const Elysium::Core::String Elysium::Core::Security::Cryptography::Oid::GetFriendlyName() const
{
	return _FriendlyName;
}
const Elysium::Core::String Elysium::Core::Security::Cryptography::Oid::GetValue() const
{
	return _Value;
}

void Elysium::Core::Security::Cryptography::Oid::SetFriendlyName(const String & Value)
{
	_FriendlyName = Value;
}
void Elysium::Core::Security::Cryptography::Oid::SetFriendlyName(String && Value)
{
	_FriendlyName = Value;
}
void Elysium::Core::Security::Cryptography::Oid::SetValue(const String & Value)
{
	_Value = Value;
}
void Elysium::Core::Security::Cryptography::Oid::SetValue(String && Value)
{
	_Value = Value;
}
