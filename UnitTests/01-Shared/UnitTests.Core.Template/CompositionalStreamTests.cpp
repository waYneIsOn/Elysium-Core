#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InOutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Device/FileDevice.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Device/MemoryDevice.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/BufferedSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/DeflateSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/FileSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/MemorySink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/BufferedSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/DeflateSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/GZipSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/FileSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/MemorySource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/CharacterTraits.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"

using namespace Elysium::Core::Template::IO;
using namespace Elysium::Core::Template::IO::Device;
using namespace Elysium::Core::Template::IO::Sink;
using namespace Elysium::Core::Template::IO::Source;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::IO
{
	TEST_CLASS(CompositionalStreamTests)
	{
		using MemoryStream = InOutStream<MemorySink, MemorySource, DeviceCoupled>;
		using BufferedMemoryStream = InOutStream<BufferedSink<MemorySink>, BufferedSource<MemorySource>, DeviceCoupled>;

		using FileStream = InOutStream<FileSink, FileSource, DeviceCoupled>;
		using BufferedFileStream = InOutStream<BufferedSink<FileSink>, BufferedSource<FileSource>, DeviceCoupled>;

		using DeflateStream = InOutStream<DeflateSink<MemorySink>, DeflateSource<FileSource>, DeviceCoupled>;
		using BufferedDeflateStream = InOutStream<BufferedSink<DeflateSink<MemorySink>>, BufferedSource<DeflateSource<FileSource>>, DeviceCoupled>;

		//using GZipStream = InOutStream<MemorySink, DeflateSource<GZipSource<FileSource>>>;
		using GZipStream = InOutStream<MemorySink, GZipSource<FileSource>>;
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
			/*
			try
			{
				Assert::Fail();
			}
			catch(...)
			{ }
			*/
		}
	public:
		TEST_METHOD(DeflateStreamTest)
		{
			{
				FileDevice WriteDevice(u8"C:\\test\\deflate.txt", FileMode::Create, FileAccess::Read | FileAccess::Write, FileShare::ReadWrite);
				FileSink Sink(WriteDevice);

				MemoryDevice Device(1024);
				MemorySource Source(Device);
				//DeflateStream Stream(Sink, Source);

				Assert::Fail();
			}
		}

		TEST_METHOD(GZipStreamTest)
		{
			{
				MemoryDevice WriteDevice(1024);
				MemorySink Sink(WriteDevice);

				FileDevice ReadDevice(u8"Lorem Ipsum.gz", FileMode::Open, FileAccess::Read | FileAccess::Write);
				FileSource Source(ReadDevice);
				GZipSource GZipSource(Source);
				DeflateSource DeflateSource(GZipSource);

				GZipStream Stream(Sink, GZipSource);

				Elysium::Core::Template::System::byte Buffer[1024] = {};
				Elysium::Core::Template::System::size BytesRead = Stream.Read(&Buffer[0], 1024);

				/*
				// @ToDo: all the reading currently works through source -> needs to be done through stream
				Elysium::Core::Template::IO::Compression::Format::GZip::GZipHeader Header = GZipSource.ReadHeader();
				GZipSource.ReadOptionalHeader(Header);

				while (GZipSource.ReadBlock())
				{

				}

				//Elysium::Core::Template::IO::Compression::Format::GZip::GZipFooter Footer = GZipSource.ReadFooter();
				*/


				/*
				*/

				Assert::Fail();
			}
		}

		TEST_METHOD(FileStreamTest)
		{			
			{
				FileDevice WriteDevice(u8"C:\\test\\bla.txt", FileMode::Create, FileAccess::Read | FileAccess::Write, FileShare::ReadWrite);
				FileSink Sink(WriteDevice);

				FileDevice ReadDevice(u8"C:\\test\\bla.txt", FileMode::Open, FileAccess::Read | FileAccess::Write, FileShare::ReadWrite);
				FileSource Source(ReadDevice);

				FileStream Stream(Sink, Source);

				WriteAndReadBack(Stream, false);
			}
			
			{
				FileDevice WriteDevice(u8"C:\\test\\bla.txt", FileMode::Create, FileAccess::Read | FileAccess::Write, FileShare::ReadWrite);
				FileSink Sink(WriteDevice);
				BufferedSink<FileSink> BufferedSink(Sink);

				FileDevice ReadDevice(u8"C:\\test\\bla.txt", FileMode::Open, FileAccess::Read | FileAccess::Write, FileShare::ReadWrite);
				FileSource Source(ReadDevice);
				BufferedSource<FileSource> BufferedSource(Source);

				BufferedFileStream Stream(BufferedSink, BufferedSource);

				WriteAndReadBack(Stream, true);
			}
		}

		TEST_METHOD(MemoryStreamTest)
		{
			{
				MemoryDevice Device(1024);
				MemorySink Sink(Device);
				MemorySource Source(Device);
				MemoryStream Stream(Sink, Source);

				WriteAndReadBack(Stream, false);
			}
			
			{
				MemoryDevice Device(1024);

				MemorySink Sink(Device);
				BufferedSink<MemorySink> BufferedSink(Sink);

				MemorySource Source(Device);
				BufferedSource<MemorySource> BufferedSource(Source);

				BufferedMemoryStream Stream(BufferedSink, BufferedSource);

				WriteAndReadBack(Stream, true);
			}
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
				Elysium::Core::Template::System::size TotalBytesRead = 0;
				while (TotalBytesRead < CombinedInputLength)
				{
					Elysium::Core::Template::System::size BytesRead = Stream.Read(&Buffer[TotalBytesRead], CombinedInputLength - TotalBytesRead);
					TotalBytesRead += BytesRead;
				}

				const char* Output = reinterpret_cast<const char*>(&Buffer[0]);
				const Elysium::Core::Template::System::size OutputLength = Elysium::Core::Template::Text::CharacterTraits<char>::GetLength(Output);

				Assert::AreEqual(TempInputLength, OutputLength);
				Assert::AreEqual(&CombinedInput[0], &Output[0]);
			}
		}
	};
}
