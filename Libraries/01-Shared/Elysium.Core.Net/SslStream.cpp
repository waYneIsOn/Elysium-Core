#include "SslStream.hpp"

Elysium::Core::Net::Security::SslStream::SslStream(IO::Stream & InnerStream, const bool LeaveInnerStreamOpen)
	: AuthenticatedStream(InnerStream, LeaveInnerStreamOpen)
{ }
Elysium::Core::Net::Security::SslStream::~SslStream()
{ }

const bool Elysium::Core::Net::Security::SslStream::GetIsAuthenticated() const
{
	return false;
}
const bool Elysium::Core::Net::Security::SslStream::GetIsEncrypted() const
{
	return false;
}
const bool Elysium::Core::Net::Security::SslStream::GetIsMutuallyAuthenticated() const
{
	return false;
}
const bool Elysium::Core::Net::Security::SslStream::GetIsServer() const
{
	return false;
}
const bool Elysium::Core::Net::Security::SslStream::GetIsSigned() const
{
	return false;
}

void Elysium::Core::Net::Security::SslStream::AuthenticateAsClient(const String & TargetHost, const Core::Security::Cryptography::X509Certificates::X509CertificateCollection & ClientCertificates, const SslProtocols EnabledSsslProtocols, const bool CheckCertficateRevocation)
{
}
void Elysium::Core::Net::Security::SslStream::AuthenticateAsServer(const Core::Security::Cryptography::X509Certificates::X509CertificateCollection & ClientCertificates, const bool ClientCertificateRequired, const SslProtocols EnabledSsslProtocols, const bool CheckCertficateRevocation)
{
}
