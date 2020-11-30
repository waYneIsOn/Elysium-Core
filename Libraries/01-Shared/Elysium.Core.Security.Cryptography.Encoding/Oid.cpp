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
	// ToDo: convert wchar_t* to char* correctly!
	PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_NAME_KEY, static_cast<void*>(&FriendlyName[0]), (uint32_t)Group);
	if (NativeOid == nullptr)
	{
		throw CryptographicException();
	}

	return Oid(NativeOid);
}
Elysium::Core::Security::Cryptography::Oid Elysium::Core::Security::Cryptography::Oid::FromOidValue(const Elysium::Core::String & OidValue, const OidGroup Group)
{
	// ToDo: convert utf-8 char to char* correctly!
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = Text::Encoding::Default().GetBytes(OidValue, 0, OidValue.GetLength());
	PCCRYPT_OID_INFO NativeOid = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY, static_cast<void*>(&Bytes[0]), (uint32_t)Group);
	if (NativeOid == nullptr)
	{
		throw CryptographicException();
	}

	return Oid(NativeOid);
}

const Elysium::Core::String Elysium::Core::Security::Cryptography::Oid::GetFriendlyName() const
{
	// ToDo: convert wchar_t* to char16_t* correctly!
	const wchar_t* WideString = _NativeOid->pwszName;
	size_t WideStringLength = std::char_traits<wchar_t>::length(WideString);

	size_t CharStringLength = WideStringLength + 1;
	char* CharString = new char[CharStringLength];
	size_t NumberOfCharsConverted;
	size_t CharLength = wcstombs_s(&NumberOfCharsConverted, CharString, CharStringLength, WideString, WideStringLength);

	Elysium::Core::String Result = Text::Encoding::Default().GetString((const byte*)&CharString[0], CharStringLength);
	delete[] CharString;

	return Result;
}
const Elysium::Core::String Elysium::Core::Security::Cryptography::Oid::GetValue() const
{
	// ToDo: convert char* to char16_t* correctly!
	const char* CharString = _NativeOid->pszOID;
	return Text::Encoding::Default().GetString((const byte*)CharString, std::char_traits<char>::length(CharString));
}

Elysium::Core::Security::Cryptography::Oid::Oid(const ELYSIUM_CORE_SECURITY_CRYPTOHRAPHY_OIDPOINTER NativeOid)
	: _NativeOid(NativeOid)
{ }
