#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Net/Socket.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Net/NetworkStream.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_SSLSTREAM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Net/SslStream.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Exception.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Net::Security;
using namespace Elysium::Core::Net::Sockets;
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
			TcpSocket.Connect(String(u"3.232.168.170"), 443);	// https://httpbin.org
			NetworkStream InnerStream = NetworkStream(TcpSocket);

			SslStream Stream = SslStream(InnerStream, false, &RemoteCertificateValidationCallback::CreateDelegate<&SslStreamTests::ValidateServerCertificate>(), nullptr,
				EncryptionPolicy::RequireEncryption);
			try
			{
				Stream.AuthenticateAsClient(String(u"3.232.168.170"));
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
		static const bool ValidateServerCertificate(const void* Sender, const X509Certificate& Certificate, const X509Chain& Chain, const SslPolicyErrors PolicyErrors)
		{
			if (PolicyErrors == SslPolicyErrors::None)
			{
				return true;
			}

			return false;
		}
	};
}
