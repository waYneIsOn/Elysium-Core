#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Atomic.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Net/Security/TlsSession.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InOutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/OutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Device/FileDevice.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Device/MemoryDevice.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/FileSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/MemorySink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/SocketSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/TlsSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/FileSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/MemorySource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/SocketSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/TlsSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/CharacterTraits.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/Convert.hpp"

using namespace Elysium::Core::Template::Net::Security;
using namespace Elysium::Core::Template::IO;
using namespace Elysium::Core::Template::IO::Device;
using namespace Elysium::Core::Template::IO::Sink;
using namespace Elysium::Core::Template::IO::Source;
using namespace Elysium::Core::Template::Net::Sockets;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::IO
{
	TEST_CLASS(CompositionalStreamTests)
	{
		using MemoryStream = InOutStream<MemorySink, MemorySource, DeviceResourceShared>;

		using InFileStream = InStream<FileSource>;
		using FileStream = InOutStream<FileSink, FileSource, DeviceResourceShared>;

		using TlsStream = InOutStream<TlsSink<SocketSink, TlsSession<SocketSink, SocketSource>>, TlsSource<SocketSource, TlsSession<SocketSink, SocketSource>>, TlsCoupled>;

		using OutFileStream = OutStream<FileSource>;
	public:
		TEST_METHOD(PolicyTest)
		{
			try
			{
				MemoryDevice SinkDevice(1024);
				MemorySink Sink(SinkDevice);

				MemoryDevice InvalidSourceDevice(1024);
				MemorySource Source(InvalidSourceDevice);

				MemoryStream Stream(Sink, Source);

				Assert::Fail();
			}
			catch(...)
			{  }

			try
			{
				FileDevice SinkDevice(u8"some file.txt", FileMode::Create);
				FileSink Sink(SinkDevice);

				FileDevice InvalidSourceDevice(u8"some other file.txt", FileMode::Create);
				FileSource Source(InvalidSourceDevice);

				FileStream Stream(Sink, Source);

				Assert::Fail();
			}
			catch (...)
			{ }
			
			try
			{
				Socket ClientSocket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);

				SocketDevice Device(ClientSocket);
				SocketSink Sink(Device);
				SocketSource Source(Device);

				TlsSession<SocketSink, SocketSource> SinkSession(Sink, Source);
				TlsSession<SocketSink, SocketSource> SourceSession(Sink, Source);
				
				TlsSink EncryptedSink(Sink, SinkSession);
				TlsSource EncryptedSource(Source, SourceSession);

				TlsStream Stream(EncryptedSink, EncryptedSource);

				Assert::Fail();
			}
			catch(...)
			{ }
			/*
			try
			{
				QuicSink Sink;
				QuicSource Source;
			}
			catch(...)
			{ }
			*/
		}
	public:
		TEST_METHOD(FileStreamTest)
		{	
			// same file, same device
			{
				FileDevice Device(u8"UnitTests.Core.Template.IO.FileStreamTest.txt", FileMode::Create, FileAccess::Read | FileAccess::Write, FileShare::ReadWrite);
				FileSink Sink(Device);
				FileSource Source(Device);

				FileStream Stream(Sink, Source);

				WriteAndReadBack(Stream, false);
			}

			// same file, different devices
			{
				FileDevice WriteDevice(u8"UnitTests.Core.Template.IO.FileStreamTest.txt", FileMode::Create, FileAccess::Write, FileShare::ReadWrite);
				FileSink Sink(WriteDevice);

				FileDevice ReadDevice(u8"UnitTests.Core.Template.IO.FileStreamTest.txt", FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
				FileSource Source(ReadDevice);

				FileStream Stream(Sink, Source);

				WriteAndReadBack(Stream, false);
			}
		}

		TEST_METHOD(FileDeviceIOCPTests)
		{
			for(Elysium::Core::Template::System::size i = 0; i < 100000; ++i)
			{
				FileDevice SourceDevice(u8"Lorem Ipsum.txt", FileMode::Open, FileAccess::Read);

				FileDevice TargetDevice(u8"UnitTests.Core.Template.IO.FileDeviceIOCPTests.txt", FileMode::Create, FileAccess::Write);

				while(true)
				{
					//OutputDebugStringA("----------------\r\n");
					Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> ReadTask = SourceDevice.ReadAsync(_Buffer, _BufferLength);
					ReadTask.Wait();
					Elysium::Core::Template::System::size BytesRead = ReadTask.GetResult();
					if (38 == ReadTask.GetErrorCode())
					{
						bool sdfg = false;
					}
					if (0 == BytesRead)
					{
						break;
					}
					/*
					if (_BufferLength != BytesRead)
					{
						const Elysium::Core::Template::Text::String<char> BytesLeft = Elysium::Core::Template::Text::Convert<char>::ToString(BytesRead);
						Logger::WriteMessage(&BytesLeft[0]);
					}
					*/
					Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> WriteTask = TargetDevice.WriteAsync(_Buffer, BytesRead);
					WriteTask.Wait();
				}

				const Elysium::Core::Template::System::size SourceLength = SourceDevice.GetLength();
				const Elysium::Core::Template::System::size TargetLength = TargetDevice.GetLength();
				if (SourceLength != TargetLength)
				{
					bool sdfsdf = false;
				}

				//Assert::AreEqual(SourceDevice.GetLength(), TargetDevice.GetLength());
			}

			{
				/*
				FileDevice SourceDevice(u8"Lorem Ipsum.txt", FileMode::Open, FileAccess::Read);
				FileSource Source(SourceDevice);

				FileDevice TargetDevice(u8"UnitTests.Core.Template.IO.FileDeviceIOCPTests.txt", FileMode::Create, FileAccess::Write);

				Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> DataView{};
				Elysium::Core::Template::Threading::Tasks::Task<Elysium::Core::Template::System::size> ReadTask = Source.ReadBlockAsync(DataView);
				ReadTask.Wait();

				bool sdf = false;
				*/
			}
		}

		TEST_METHOD(FileStreamIOCPTests)
		{
			Assert::Fail();
		}

		TEST_METHOD(MemoryStreamTest)
		{
			MemoryDevice Device(1024);
			MemorySink Sink(Device);
			MemorySource Source(Device);
			MemoryStream Stream(Sink, Source);

			WriteAndReadBack(Stream, false);
		}
	private:
		// @ToDo: create a concept for Streams to use here!
		// inline void WriteAndReadBack(Elysium::Core::Template::Concepts::Streamable auto& Stream)
		template <class S>
		inline void WriteAndReadBack(S& Stream, const bool FlushRequired)
		{
			constexpr const char* TempInput = "this is a text longer than what eventually is in the stream";
			constexpr const Elysium::Core::Template::System::size TempInputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(TempInput);

			constexpr const char* Input = "simple text";
			constexpr const Elysium::Core::Template::System::size InputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Input);

			constexpr const char* CombinedInput = "simple textext longer than what eventually is in the stream";
			constexpr const Elysium::Core::Template::System::size CombinedInputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(CombinedInput);

			Assert::IsTrue(TempInputLength > InputLength);
			Assert::AreEqual(CombinedInputLength, TempInputLength);

			Elysium::Core::Template::System::byte Buffer[CombinedInputLength + sizeof(char)] = {};

			for (Elysium::Core::Template::System::size i = 0; i < 2; ++i)
			{
				Stream.SetPosition(0);
				Stream.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(TempInput), TempInputLength);
				if (FlushRequired)
				{
					Stream.Flush();
				}

				Stream.SetPosition(0);
				Stream.Write(reinterpret_cast<const Elysium::Core::Template::System::byte*>(Input), InputLength);
				if (FlushRequired)
				{
					Stream.Flush();
				}

				Stream.SetPosition(0);
				Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> Span{};
				Elysium::Core::Template::System::size TotalBytesRead = 0;
				while (Stream.ReadBlock(Span) == Elysium::Core::Template::IO::ReadResult::HasData)
				{
					if (TotalBytesRead + Span.GetLength() > sizeof(Buffer))
					{
						Assert::Fail();
					}

					Elysium::Core::Template::Memory::MemCpy(&Buffer[TotalBytesRead], Span.GetData(), Span.GetLength());
					TotalBytesRead += Span.GetLength();

					Stream.AdvanceReadingBlock(Span.GetLength());
				}

				const char* Output = reinterpret_cast<const char*>(&Buffer[0]);
				const Elysium::Core::Template::System::size OutputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Output);

				Assert::AreEqual(TempInputLength, OutputLength);
				Assert::AreEqual(&CombinedInput[0], &Output[0]);
			}
		}
	private:
		inline static constexpr const Elysium::Core::Template::System::size _BufferLength = 4096;
		//inline static constexpr const Elysium::Core::Template::System::size _BufferLength = 4096 * 10000;
		const Elysium::Core::Template::System::byte _Buffer[_BufferLength]{};
		Elysium::Core::Template::Threading::ManualResetEvent _WaitForDeviceFullFileCopy{};
	private:
		Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> _Span{};
	};
}
