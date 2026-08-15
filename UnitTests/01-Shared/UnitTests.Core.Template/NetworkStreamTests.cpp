#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/StringView.hpp"
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
using namespace Elysium::Core::Template::Net::Sockets;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::IO
{
	TEST_CLASS(NetworkStreamTests)
	{
		using NetworkReadingStream = OutStream<SocketSource>;
		using NetworkWritingStream = InStream<SocketSink>;

		using NetworkStream = InOutStream<SocketSink, SocketSource, DeviceCoupled>;

		using TlsNetworkStream = InOutStream<TlsSink<SocketSink>, TlsSource<SocketSource>, DeviceCoupled>;
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
			TlsSink EncryptedSink(Sink);
			SocketSource Source(Device);
			TlsSource EncryptedSource(Source);

			TlsNetworkStream Stream(EncryptedSink, EncryptedSource);

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
	};
}
