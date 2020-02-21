#include "X509Certificate.hpp"

const Elysium::Core::String Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::_Format = u"X509";
const Elysium::Core::Security::Cryptography::X509Certificates::X509KeyStorageFlags KeyStorageFlagsAll =
Elysium::Core::Security::Cryptography::X509Certificates::X509KeyStorageFlags::UserKeySet |
Elysium::Core::Security::Cryptography::X509Certificates::X509KeyStorageFlags::MachineKeySet |
Elysium::Core::Security::Cryptography::X509Certificates::X509KeyStorageFlags::Exportable |
Elysium::Core::Security::Cryptography::X509Certificates::X509KeyStorageFlags::UserProtected |
Elysium::Core::Security::Cryptography::X509Certificates::X509KeyStorageFlags::PersistKeySet |
Elysium::Core::Security::Cryptography::X509Certificates::X509KeyStorageFlags::EphemeralKeySet;

Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::X509Certificate(const String & FileName, const String & Password, const X509KeyStorageFlags Flags)
{
	LoadCertificateFromFile(FileName, Password, Flags);
}
Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::~X509Certificate()
{
}

void Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadCertificateFromBlob(const Collections::Template::Array<byte>& RawData, const String & Password, const X509KeyStorageFlags Flags)
{
}
void Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate::LoadCertificateFromFile(const String & FileName, const String & Password, const X509KeyStorageFlags Flags)
{
}
