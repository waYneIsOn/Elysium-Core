#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Dispatch/MessageQueue.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/Convert.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/AutoResetEvent.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Threading/Thread.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"

using namespace Elysium::Core::Template::Dispatch;
using namespace Elysium::Core::Template::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Dispatch
{
	TEST_CLASS(EnumMessageQueueTests)
	{
	private:
		enum class MessageId
			: Elysium::Core::Template::System::uint8_t
		{
			Uninitialized = 0,

			Success = 1,

			Warning = 2,

			Error = 3,

			Max = Error + 1
		};
	private:
		using MessageIdType = MessageId;
		using MessagePayloadType = void;
		using MessageType = Message<MessageIdType, MessagePayloadType>;
	public:
		TEST_METHOD(Run)
		{
			constexpr const Elysium::Core::Template::System::size NumberOfThreads = 4;
			Thread Threads[NumberOfThreads]{};
			
			for (Elysium::Core::Template::System::size i = 0; i < NumberOfThreads; ++i)
			{
				Elysium::Core::Template::Container::Function StartMethod = &EnumMessageQueueTests::PushMessages;
				Threads[i].Start(Elysium::Core::Template::Functional::Move(StartMethod), *this);
			}
			_StartPopulatingEvent.Set();

			// stupid way to wait for the first message but for this test it will suffice!
			MessageType Message{};
			while (!_Queue.Get(Message))
			{ }

			while (_Queue.Get(Message))
			{
				switch (Message.GetId())
				{
				case MessageId::Uninitialized:
					Logger::WriteMessage("Uninitialized\r\n");
					break;
				case MessageId::Success:
					Logger::WriteMessage("Success\r\n");
					break;
				case MessageId::Warning:
					Logger::WriteMessage("Warning\r\n");
					break;
				case MessageId::Error:
					Logger::WriteMessage("Error\r\n");
					break;
				default:
					Logger::WriteMessage("Unknown\r\n");
					break;
				}
			}
		}
	private:
		inline void PushMessages()
		{
			_StartPopulatingEvent.WaitOne();

			for (Elysium::Core::Template::System::size i = 0; i < static_cast<Elysium::Core::Template::System::uint8_t>(MessageId::Max) * 4; ++i)
			{
				MessageType Message(static_cast<MessageId>(i % static_cast<Elysium::Core::Template::System::uint8_t>(MessageId::Max)));
				_Queue.Post(Elysium::Core::Template::Functional::Move(Message));
			}
		}
	private:
		AutoResetEvent _StartPopulatingEvent{};
		MessageQueue<MessageType> _Queue{};
	};

	TEST_CLASS(SizeMessageQueueTests)
	{
	private:
		using MessageIdType = Elysium::Core::Template::System::size;
		using MessagePayloadType = Elysium::Core::Template::System::uint32_t;
		using MessageType = Message<MessageIdType, MessagePayloadType>;
	public:
		TEST_METHOD(Run)
		{
			constexpr const Elysium::Core::Template::System::size NumberOfThreads = 4;
			Thread Threads[NumberOfThreads]{};

			for (Elysium::Core::Template::System::size i = 0; i < NumberOfThreads; ++i)
			{
				Elysium::Core::Template::Container::Function StartMethod = &SizeMessageQueueTests::PushMessages;
				Threads[i].Start(Elysium::Core::Template::Functional::Move(StartMethod), *this);
			}
			_StartPopulatingEvent.Set();

			// stupid way to wait for the first message but for this test it will suffice!
			MessageType Message{};
			while (!_Queue.Get(Message))
			{ }

			while (_Queue.Get(Message))
			{
				Elysium::Core::Template::Text::String<char> Id = Elysium::Core::Template::Text::Convert<char>::ToString(Message.GetId());
				Elysium::Core::Template::Text::String<char> Payload = Elysium::Core::Template::Text::Convert<char>::ToString(Message.GetPayload());

				Logger::WriteMessage(&Id[0]);
				Logger::WriteMessage(" - ");
				Logger::WriteMessage(&Payload[0]);
				Logger::WriteMessage("\r\n");
			}
		}
	private:
		inline void PushMessages()
		{
			const bool WaitResult = _StartPopulatingEvent.WaitOne();

			const Elysium::Core::Template::System::uint32_t CurrentThreadId = Thread::RetrieveCurrentThreadId();

			for (Elysium::Core::Template::System::size i = 0; i < 200; ++i)
			{
				MessageType Message(i, CurrentThreadId);
				_Queue.Post(Elysium::Core::Template::Functional::Move(Message));
			}
		}
	private:
		AutoResetEvent _StartPopulatingEvent{};
		MessageQueue<MessageType> _Queue{};
	};
}