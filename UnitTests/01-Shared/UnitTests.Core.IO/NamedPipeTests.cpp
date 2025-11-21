#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core/StringView.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO.Pipes/NamedPipeClientStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO.Pipes/NamedPipeServerStream.hpp"


#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO::Pipes;
using namespace Elysium::Core::Threading;
using namespace Elysium::Core::Template::Container;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO::Pipes
{
	TEST_CLASS(NamedPipeTests)
	{
	public:
		TEST_METHOD(SingleClientTest)
		{
			Thread ServerThread = Thread(Delegate<void>::Bind<&RunServer>());
			Thread ClientThread = Thread(Delegate<void>::Bind<&RunClient>());
			
			// specifically start the client first to test whether it "waits" for an available connection
			ClientThread.Start();
			ServerThread.Start();

			ServerThread.Join();
			ClientThread.Join();
		}

		TEST_METHOD(MultipleClientsTest)
		{
			{
				Thread ServerThread = Thread(Delegate<void, void*>::Bind<&RunMultipleServer>());
				Thread ClientThread = Thread(Delegate<void, void*>::Bind<&RunMultipleClients>());

				ServerThread.Start(reinterpret_cast<void*>(false));
				ClientThread.Start(reinterpret_cast<void*>(false));

				ServerThread.Join();
				ClientThread.Join();
			}

			{
				Thread ServerThread = Thread(Delegate<void, void*>::Bind<&RunMultipleServer>());
				Thread ClientThread = Thread(Delegate<void, void*>::Bind<&RunMultipleClients>());

				ServerThread.Start(reinterpret_cast<void*>(true));
				ClientThread.Start(reinterpret_cast<void*>(true));

				ServerThread.Join();
				ClientThread.Join();
			}
		}

		TEST_METHOD(AsyncIOCPBla)
		{
			Assert::Fail();
		}
	private:
		static void RunServer()
		{
			NamedPipeServerStream Server = NamedPipeServerStream(PipeName);
			Server.WaitForConnection();

			const Elysium::Core::String WelcomeMessage = "welcome message from server\r\n";
			Server.Write(reinterpret_cast<const Elysium::Core::byte*>(&WelcomeMessage[0]), WelcomeMessage.GetLength());

			Elysium::Core::byte Buffer[1024] = { 0 };
			Elysium::Core::size BytesRead = Server.Read(&Buffer[0], 1024);
		}

		static void RunClient()
		{
			NamedPipeClientStream Client = NamedPipeClientStream(PipeName);
			Client.Connect();

			Elysium::Core::byte Buffer[1024] = { 0 };
			Elysium::Core::size BytesRead = Client.Read(&Buffer[0], 1024);

			Elysium::Core::StringView WelcomeMessage = Elysium::Core::StringView(
				static_cast<char*>(static_cast<void*>(&Buffer[0])), BytesRead);

			constexpr const char* Request1 = "this is the first request\r\n";
			constexpr const Elysium::Core::size Request1Length = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Request1);
			Client.Write(reinterpret_cast<const Elysium::Core::byte*>(&Request1[0]), Request1Length);
		}
	private:
		static void RunMultipleServer(void* Input)
		{
			const bool SendAndReceive = reinterpret_cast<bool>(Input);
			Elysium::Core::Template::System::size ClientIteration = -1;

			for (Elysium::Core::Template::System::size i = 0; i < _NumberOfClients; ++i)
			{
				NamedPipeServerStream Server = NamedPipeServerStream(PipeName);
				Server.WaitForConnection();

				if (SendAndReceive)
				{
					Elysium::Core::Template::System::size BytesRead =
						Server.Read(reinterpret_cast<Elysium::Core::byte*>(&ClientIteration),
							sizeof(Elysium::Core::Template::System::size));
					Assert::AreEqual(i, ClientIteration);

					Server.Write(reinterpret_cast<Elysium::Core::byte*>(&i), sizeof(Elysium::Core::Template::System::size));
				}
			}
		}

		static void RunMultipleClients(void* Input)
		{
			const bool SendAndReceive = reinterpret_cast<bool>(Input);
			Elysium::Core::Template::System::size ServerIteration = -1;

			for (Elysium::Core::Template::System::size i = 0; i < _NumberOfClients; ++i)
			{
				NamedPipeClientStream Client = NamedPipeClientStream(PipeName);
				Client.Connect();

				if (SendAndReceive)
				{
					Client.Write(reinterpret_cast<Elysium::Core::byte*>(&i), sizeof(Elysium::Core::Template::System::size));

					Elysium::Core::Template::System::size BytesRead =
						Client.Read(reinterpret_cast<Elysium::Core::byte*>(&ServerIteration),
							sizeof(Elysium::Core::Template::System::size));
					Assert::AreEqual(i, ServerIteration);
				}
			}
		}
	private:
		static constexpr const char8_t* PipeName = u8"MyTestPipe";

		static constexpr const Elysium::Core::Template::System::size _NumberOfClients = 1000000;
	};
}
