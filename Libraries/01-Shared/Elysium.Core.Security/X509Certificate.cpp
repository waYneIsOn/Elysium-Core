#include "X509Certificate.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef __WINCRYPT_H__
#ifndef _WINDOWS_
#include <windows.h>
#endif

#include <wincrypt.h>
#endif

const Elysium::Core::String Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::_Format = u"X509";

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(const Collections::Template::Array<byte>& RawData, const String & Password, const X509KeyStorageFlags Flags)
	: _RawData(RawData)
{
	LoadCertificateFromBlob(RawData, Password, Flags);
}
Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(const String & FileName, const String & Password, const X509KeyStorageFlags Flags)
	: _RawData(Collections::Template::Array<byte>(0))
{
	LoadCertificateFromFile(FileName, Password, Flags);
}
Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(const X509Certificate & Source)
	: _RawData(Source._RawData)
{ }
Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(X509Certificate && Right) noexcept
	: _RawData(Collections::Template::Array<byte>(0))
{
	*this = std::move(Right);
}
Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::~X509Certificate()
{

}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::operator=(const X509Certificate & Source)
{
	if (this != &Source)
	{
		_RawData = Source._RawData;
	}
	return *this;
}

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::operator=(X509Certificate && Right) noexcept
{
	if (this != &Right)
	{
		_RawData = std::move(Right._RawData);
	}
	return *this;
}

void Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadCertificateFromBlob(const Collections::Template::Array<byte>& RawData, const String & Password, const X509KeyStorageFlags Flags)
{
}
void Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadCertificateFromFile(const String & FileName, const String & Password, const X509KeyStorageFlags Flags)
{
}
