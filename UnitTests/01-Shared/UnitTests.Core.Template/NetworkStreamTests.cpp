#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/StringView.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Net/Security/TlsCipherSuite.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Net/Security/TlsSession.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InOutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/OutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/SocketSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/TlsSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/SocketSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/TlsSource.hpp"

using namespace Elysium::Core::Template::IO;
using namespace Elysium::Core::Template::IO::Device;
using namespace Elysium::Core::Template::IO::Sink;
using namespace Elysium::Core::Template::IO::Source;
using namespace Elysium::Core::Template::Net::Security;
using namespace Elysium::Core::Template::Net::Sockets;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::IO
{
	TEST_CLASS(NetworkStreamTests)
	{
		using NetworkReadingStream = OutStream<SocketSource>;
		using NetworkWritingStream = InStream<SocketSink>;

		using NetworkStream = InOutStream<SocketSink, SocketSource, DeviceCoupled>;

		using TlsNetworkStream = InOutStream<TlsSink<SocketSink, TlsSession<SocketSink, SocketSource>>, TlsSource<SocketSource, TlsSession<SocketSink, SocketSource>>, TlsCoupled>;
	public:
		TEST_METHOD(FtpClientReadWelcomeMessage)
		{
			Socket ClientSocket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(u8"demo.wftpserver.com", 21);

			SocketDevice Device(ClientSocket);
			SocketSource Source(Device);
			NetworkReadingStream InStream(Source);

			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> View{};
			const Elysium::Core::Template::IO::ReadResult Result0 = InStream.ReadBlock(View);

			Elysium::Core::Template::Text::String<char> Response(reinterpret_cast<char*>(View.GetData()), View.GetLength());
			Logger::WriteMessage(&Response[0]);
			Logger::WriteMessage("\r\n");

			InStream.AdvanceReadingBlock(4);
			const Elysium::Core::Template::IO::ReadResult Result1 = InStream.ReadBlock(View);

			ClientSocket.Shutdown(Elysium::Core::Template::Net::Sockets::SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}

		TEST_METHOD(HttpClientSendAndReceive)
		{
			Socket ClientSocket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(u8"www.tutorialspoint.com", 80);

			SocketDevice Device(ClientSocket);
			SocketSink Sink(Device);
			SocketSource Source(Device);

			NetworkStream Stream(Sink, Source);

			Elysium::Core::Template::Text::String<char8_t> HttpRequest = u8"GET / HTTP/1.1\r\nHost: www.tutorialspoint.com\r\nConnection: keep-alive\r\n\r\n";
			Stream.Write(reinterpret_cast<Elysium::Core::Template::System::byte*>(&HttpRequest[0]), HttpRequest.GetLength());
			Stream.Flush();

			Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> View{};
			const Elysium::Core::Template::IO::ReadResult Result = Stream.ReadBlock(View);

			Elysium::Core::Template::Text::String<char> Response(reinterpret_cast<char*>(View.GetData()), View.GetLength());
			Logger::WriteMessage(&Response[0]);
			Logger::WriteMessage("\r\n");

			ClientSocket.Shutdown(Elysium::Core::Template::Net::Sockets::SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}
		
		TEST_METHOD(HttpsClientSendAndReceive)
		{
			Socket ClientSocket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(u8"www.tutorialspoint.com", 443);

			SocketDevice Device(ClientSocket);
			SocketSink Sink(Device);
			SocketSource Source(Device);
			
			TlsSession<SocketSink, SocketSource> Session(Sink, Source);
			Session.AuthenticateAsClient(u8"www.tutorialspoint.com", nullptr, Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls12);
			//Session.AuthenticateAsClient(u8"www.tutorialspoint.com", nullptr, Elysium::Core::Template::Security::Authentication::TlsProtocols::Tls13);
			
			TlsSink EncryptedSink(Sink, Session);
			TlsSource EncryptedSource(Source, Session);
			
			TlsNetworkStream Stream(EncryptedSink, EncryptedSource);
			
			for (Elysium::Core::Template::System::size i = 0; i < 10; ++i)
			{
				Elysium::Core::Template::Text::String<char8_t> HttpRequest = u8"GET / HTTP/1.1\r\nHost: www.tutorialspoint.com\r\nConnection: keep-alive\r\n\r\n";
				Stream.Write(reinterpret_cast<Elysium::Core::Template::System::byte*>(&HttpRequest[0]), HttpRequest.GetLength());
				Stream.Flush();

				Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> View{};
				const Elysium::Core::Template::IO::ReadResult Result = Stream.ReadBlock(View);
				if (Elysium::Core::Template::IO::ReadResult::HasData != Result)
				{
					throw 1;
				}

				Elysium::Core::Template::Text::String<char> Response(reinterpret_cast<char*>(View.GetData()), View.GetLength());
				Logger::WriteMessage(&Response[0]);
				Logger::WriteMessage("\r\n------------------------------------------\r\n");

				Stream.AdvanceReadingBlock(View.GetLength());
			}
			
			ClientSocket.Shutdown(Elysium::Core::Template::Net::Sockets::SocketShutdown::Both);
			ClientSocket.Disconnect(false);
		}
		/*
		TEST_METHOD(LdapClientSendAndReceive)
		{
			Socket ClientSocket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			ClientSocket.Connect(u8"ldap.forumsys.com", 389);

			SocketDevice Device(ClientSocket);
			SocketSink Sink(Device);
			TlsSink EncryptedSink(Sink);
			SocketSource Source(Device);

			NetworkStream Stream(Sink, Source);

			// cn=read-only-admin,dc=example,dc=com Bind Password: password
		}

		TEST_METHOD(LdapsClientSendAndReceive)
		{
			Assert::Fail();
		}
		*/
	private:
		static const bool ValidateServerCertificate(const void* Sender, const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate& Certificate,
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Chain& Chain, const Elysium::Core::Template::Net::Security::TlsPolicyErrors PolicyErrors)
		{
			if (PolicyErrors == Elysium::Core::Template::Net::Security::TlsPolicyErrors::None)
			{
				return true;
			}

			if (static_cast<Elysium::Core::uint32_t>(PolicyErrors & Elysium::Core::Template::Net::Security::TlsPolicyErrors::RemoteCertificateChainErrors) != 0)
			{
				// ToDo: iterate certificate Chain.ChainStatus

				return true;
			}
			else
			{
				return false;
			}
		}

		static const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate& SelectLocalCertificate(const void* Sender, 
			const Elysium::Core::Utf8StringView TargetHost, 
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>& LocalCertificates, 
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate& RemoteCertificate, 
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>>& AcceptableIssuers)
		{
			// https://docs.microsoft.com/en-us/dotnet/api/system.net.security.localcertificateselectioncallback?view=netcore-3.1
			if (LocalCertificates.GetLength() > 0 && AcceptableIssuers.GetLength() > 0)
			{

			}

			return LocalCertificates[0];
		}
		private:
			inline static const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Net::Security::TlsCipherSuite> _CipherSuites = {
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
				TlsCipherSuite::TLS_RSA_WITH_3DES_EDE_CBC_SHA,
				*/
				Elysium::Core::Template::Net::Security::TlsCipherSuite::TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
			};
	};
}
