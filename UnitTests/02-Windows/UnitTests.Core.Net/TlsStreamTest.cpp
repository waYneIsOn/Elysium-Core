#include "CppUnitTest.h"

#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Exception.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Net/Socket.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Net/NetworkStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Net/TlsStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Net/TlsPolicyErrors.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Net/IPEndPoint.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Security/AuthenticationException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Security.Cryptography.Encoding/DEREncoder.hpp"
//#include "../../../Libraries/01-Shared/Elysium.Core.Net/NetworkStream.hpp"
//#include "../../../Libraries/01-Shared/Elysium.Core.Security/TlsProtocols.hpp"
//#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Exception.hpp"

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
	TEST_CLASS(TlsStreamTests)
	{
	public:
		TEST_METHOD(Https)
		{
			Socket TcpSocket = Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			TcpSocket.Connect(Elysium::Core::Net::IPEndPoint(Elysium::Core::Net::IPAddress::Parse(Elysium::Core::Utf8String(u8"52.6.191.28")), 443));	// https://ulfheim.net/
			NetworkStream InnerStream = NetworkStream(TcpSocket);
			
			const Array<TlsCipherSuite> CipherSuites = Array<TlsCipherSuite>({
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
				});

			Elysium::Core::Template::Container::Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&,
				const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&,
				const Elysium::Core::Net::Security::TlsPolicyErrors> UserCertificateValidationCallback =
				Elysium::Core::Template::Container::Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&,
				const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&,
				const Elysium::Core::Net::Security::TlsPolicyErrors>::Bind<&TlsStreamTests::ValidateServerCertificate>();

			Elysium::Core::Template::Container::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::Utf8String&,
				const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&,
				const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&,
				const Elysium::Core::Collections::Template::Array<Elysium::Core::Utf8String>&> UserCertificateSelectionCallback =
				Elysium::Core::Template::Container::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::Utf8String&,
				const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&,
				const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&,
				const Elysium::Core::Collections::Template::Array<Elysium::Core::Utf8String>&>::Bind<&TlsStreamTests::SelectLocalCertificate>();

			TlsClientAuthenticationOptions ClientAuthenticationOptions = TlsClientAuthenticationOptions(true, CipherSuites, UserCertificateValidationCallback, UserCertificateSelectionCallback);
			
			TlsStream Stream = TlsStream(InnerStream, false, ClientAuthenticationOptions);
			try
			{
				//Stream.AuthenticateAsClient(String(u8"3.232.168.170"), nullptr, TlsProtocols::Tls10);
				//Stream.AuthenticateAsClient(String(u8"3.232.168.170"), nullptr, TlsProtocols::Tls11);
				Stream.AuthenticateAsClient(Elysium::Core::Utf8String(u8"3.232.168.170"), nullptr, TlsProtocols::Tls12);
				//Stream.AuthenticateAsClient(String(u8"3.232.168.170"), nullptr, TlsProtocols::Tls13);
				
				Elysium::Core::Utf8String RequestMessage = Elysium::Core::Utf8String(u8"GET /index.html HTTP/1.1\r\nHost: www.ulfheim.net\r\n\r\n");
				Stream.Write((byte*)&RequestMessage[0], RequestMessage.GetLength());
				
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Buffer =
					Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(32000);
				Elysium::Core::size BytesReceived = Stream.Read(&Buffer[0], Buffer.GetLength());
				Elysium::Core::Utf8String ResponseMessage = Elysium::Core::Utf8String((char8_t*)&Buffer[0], BytesReceived);
			}
			catch (const AuthenticationException& ex)
			{
				const Elysium::Core::int32_t ErrorCode = ex.GetErrorCode();
				Assert::Fail();
			}
			catch (const Exception& ex)
			{
				Assert::Fail();
			}
		}
	private:
		static const bool ValidateServerCertificate(const void* Sender, const X509Certificate& Certificate, const X509Chain& Chain, const TlsPolicyErrors PolicyErrors)
		{
			if (PolicyErrors == TlsPolicyErrors::None)
			{
				return true;
			}

			if (static_cast<Elysium::Core::uint32_t>(PolicyErrors & Elysium::Core::Net::Security::TlsPolicyErrors::RemoteCertificateChainErrors) != 0)
			{
				// ToDo: iterate certificate Chain.ChainStatus

				return true;
			}
			else
			{
				return false;
			}
		}

		static const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& SelectLocalCertificate(const void* Sender, const Elysium::Core::Utf8String& TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection& LocalCertificates, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& RemoteCertificate, const Collections::Template::Array<Elysium::Core::Utf8String>& AcceptableIssuers)
		{
			// https://docs.microsoft.com/en-us/dotnet/api/system.net.security.localcertificateselectioncallback?view=netcore-3.1
			if (LocalCertificates.GetCount() > 0 && AcceptableIssuers.GetLength() > 0)
			{

			}

			return LocalCertificates[0];
		}
	};
}
