#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "../../../Libraries/01-Shared/Elysium.Core.Net/Socket.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM
#include "../../..//Libraries/01-Shared/Elysium.Core.Net/NetworkStream.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSSTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.Net/TlsStream.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSPOLICYERRORS
#include "../../../Libraries/01-Shared/Elysium.Core.Net/TlsPolicyErrors.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_DERENCODER
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.Encoding/DEREncoder.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.Net/NetworkStream.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_TLSPROTOCOLS
#include "../../../Libraries/01-Shared/Elysium.Core.Security/TlsProtocols.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Exception.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Net::Security;
using namespace Elysium::Core::Net::Sockets;
using namespace Elysium::Core::Security::Authentication;
using namespace Elysium::Core::Security::Cryptography::Encoding::Asn1;
using namespace Elysium::Core::Security::Cryptography::X509Certificates;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Net::Security
{
	TEST_CLASS(SslStreamTests)
	{
	public:
		TEST_METHOD(Https)
		{
			Socket TcpSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			TcpSocket.Connect(String(u8"52.6.191.28"), 443);	// https://ulfheim.net/
			NetworkStream InnerStream = NetworkStream(TcpSocket);
			
			TlsStream Stream = TlsStream(InnerStream, false, TlsClientAuthenticationOptions(true,
				Array<TlsCipherSuite>({
					/*
					TlsCipherSuite::TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256,
					TlsCipherSuite::TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256,
					TlsCipherSuite::TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,
					TlsCipherSuite::TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,
					TlsCipherSuite::TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,
					TlsCipherSuite::TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,
					TlsCipherSuite::TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA,
					TlsCipherSuite::TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA,
					TlsCipherSuite::TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,
					TlsCipherSuite::TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA,
					TlsCipherSuite::TLS_RSA_WITH_AES_128_GCM_SHA256,
					TlsCipherSuite::TLS_RSA_WITH_AES_256_GCM_SHA384,
					TlsCipherSuite::TLS_RSA_WITH_AES_128_CBC_SHA,
					TlsCipherSuite::TLS_RSA_WITH_AES_256_CBC_SHA,
					TlsCipherSuite::TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA,
					TlsCipherSuite::TLS_RSA_WITH_3DES_EDE_CBC_SHA
					*/
					TlsCipherSuite::TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
					}),
				Elysium::Core::Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Net::Security::TlsPolicyErrors>::CreateDelegate<&SslStreamTests::ValidateServerCertificate>(),
				Elysium::Core::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Collections::Template::Array<Elysium::Core::String>&>::CreateDelegate<&SslStreamTests::SelectLocalCertificate>()));
			try
			{ 
				Stream.AuthenticateAsClient(String(u8"3.232.168.170"), nullptr, TlsProtocols::Tls12);
			}
			/*
			catch (const AuthenticationException& ex)
			{
				TcpSocket.Disconnect(true);
				Assert::Fail();
			}
			*/
			catch (const Exception& ex)
			{
				TcpSocket.Disconnect(true);
				Assert::Fail();
			}
			
			TcpSocket.Disconnect(true);
		}
	private:
		static const bool ValidateServerCertificate(const void* Sender, const X509Certificate& Certificate, const X509Chain& Chain, const TlsPolicyErrors PolicyErrors)
		{
			if (PolicyErrors == TlsPolicyErrors::None)
			{
				return true;
			}

			return false;
		}

		static const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& SelectLocalCertificate(const void* Sender, const String& TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection& LocalCertificates, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& RemoteCertificate, const Collections::Template::Array<String>& AcceptableIssuers)
		{
			// https://docs.microsoft.com/en-us/dotnet/api/system.net.security.localcertificateselectioncallback?view=netcore-3.1
			if (LocalCertificates.GetCount() > 0 && AcceptableIssuers.GetLength() > 0)
			{

			}

			return LocalCertificates[0];
		}
	};
}
