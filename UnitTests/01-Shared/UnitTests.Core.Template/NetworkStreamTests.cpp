#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InOutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/OutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/BufferedSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/SocketSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/SocketSource.hpp"

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
		using NetworkWritingStream = InStream<BufferedSink<SocketSink>>;

		using NetworkStream = InOutStream<BufferedSink<SocketSink>, SocketSource, DeviceCoupled>;
	public:
		TEST_METHOD(bla)
		{
			Socket ClientSocket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			SocketDevice Device(ClientSocket);
			SocketSink DeviceSink(Device);
			BufferedSink OuterSink(DeviceSink);

			NetworkWritingStream Stream(OuterSink);
			



			Device.Connect(u8"www.tutorialspoint.com", 80);

			//Device.Shutdown(SocketShutdown::Both);
			//Device.Disconnect(false);
		}
	};
}
