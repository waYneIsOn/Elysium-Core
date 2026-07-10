#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InOutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/OutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Device/FileDevice.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Device/MemoryDevice.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/BufferedSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/DeflateSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/GZipSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/FileSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/MemorySink.hpp"
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
		using FileStream = InOutStream<FileSink, FileSource, DeviceCoupled>;

		using InFileStream = InOutStream<MemorySink, FileSource>;

		using GZipReadingStream = InOutStream<MemorySink, GZipSource<FileSource>>;
		using GZipWritingStream = InOutStream<GZipSink<DeflateSink<FileSink>>, FileSource>;

		using InGZipStream = InOutStream<MemorySink, GZipSource<FileSource>>;

		using DeflateStream = InOutStream<DeflateSink<MemorySink>, DeflateSource<FileSource>, DeviceCoupled>;
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
		TEST_METHOD(GZipStreamCompressAndDecompressTest)
		{
			WriteAndReadGZip(u8"Lorem Ipsum.txt", u8"Lorem Ipsum - Uncompressed.gz", Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::Stored);
			//WriteAndReadGZip(u8"Lorem Ipsum.txt", u8"Lorem Ipsum - DynamicOnly.gz", Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::DynamicOnly);
			WriteAndReadGZip(u8"Lorem Ipsum.txt", u8"Lorem Ipsum - StaticOnly.gz", Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::StaticOnly);
		}

		TEST_METHOD(GZipStreamExternalFilesTest)
		{
			// read fully dynamic
			{
				MemoryDevice WriteDevice(1024);
				MemorySink Sink(WriteDevice);

				FileDevice ReadDevice(u8"Lorem Ipsum.gz", FileMode::Open, FileAccess::Read | FileAccess::Write, FileShare::Read);
				FileSource Source(ReadDevice);
				GZipSource GZipSource(Source);

				GZipReadingStream Stream(Sink, GZipSource);

				Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> Span{};
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result{};

				while (true)
				{
					bool MadeProgress = false;
					const Elysium::Core::Template::IO::ReadResult ReadResult = Stream.ReadBlock(Span);
					switch (ReadResult)
					{
					case Elysium::Core::Template::IO::ReadResult::HasData:
						Result.PushBackRange(Span.GetData(), Span.GetLength());
						Stream.AdvanceReadingBlock(Span.GetLength());
						MadeProgress = true;
						break;
					case Elysium::Core::Template::IO::ReadResult::Pending:
						// for now simply continue running the loop
						MadeProgress = true;
						break;
					case Elysium::Core::Template::IO::ReadResult::EndOfStream:
						break;
					}

					if (!MadeProgress)
					{
						break;
					}
				}

				const Elysium::Core::Template::System::size FileLength = ReadDevice.GetLength();
				const Elysium::Core::Template::System::size FilePosition = ReadDevice.GetPosition();

				Assert::AreEqual(FileLength, FilePosition);
				Assert::AreEqual(10485760_ui64, Result.GetLength());
			}
		}

		TEST_METHOD(FileStreamTest)
		{	
			// same file, same device
			{
				FileDevice Device(u8"C:\\test\\bla.txt", FileMode::Create, FileAccess::Read | FileAccess::Write, FileShare::ReadWrite);
				FileSink Sink(Device);
				FileSource Source(Device);

				FileStream Stream(Sink, Source);

				WriteAndReadBack(Stream, false);
			}

			// same file, different devices
			{
				FileDevice WriteDevice(u8"C:\\test\\bla.txt", FileMode::Create, FileAccess::Write, FileShare::ReadWrite);
				FileSink Sink(WriteDevice);

				FileDevice ReadDevice(u8"C:\\test\\bla.txt", FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
				FileSource Source(ReadDevice);

				FileStream Stream(Sink, Source);

				WriteAndReadBack(Stream, false);
			}
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
		inline void WriteAndReadGZip(const char8_t* SourceFile, const char8_t* TargetFile, 
			Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel CompressionLevel)
		{
			{
				Elysium::Core::Template::System::size PendingCount = 0;

				FileDevice WriteDevice(TargetFile, FileMode::Create, FileAccess::Write);
				FileSink Sink(WriteDevice);
				DeflateSink DeflateSink(Sink, CompressionLevel);
				GZipSink CompressionSink(DeflateSink);

				FileDevice ReadDevice(SourceFile, FileMode::Open, FileAccess::Read, FileShare::Read);
				FileSource Source(ReadDevice);

				GZipWritingStream Stream(CompressionSink, Source);

				Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> ReadSpan{};
				while (true)
				{
					bool MadeProgress = false;
					const Elysium::Core::Template::IO::ReadResult ReadResult = Stream.ReadBlock(ReadSpan);
					switch (ReadResult)
					{
					case Elysium::Core::Template::IO::ReadResult::HasData:
						Stream.AdvanceReadingBlock(ReadSpan.GetLength());

						Stream.Write(ReadSpan.GetData(), ReadSpan.GetLength());

						MadeProgress = true;
						break;
					case Elysium::Core::Template::IO::ReadResult::Pending:
						++PendingCount;

						// for now simply continue running the loop
						MadeProgress = true;
						break;
					case Elysium::Core::Template::IO::ReadResult::EndOfStream:
						break;
					}

					if (!MadeProgress)
					{
						break;
					}
				}
				Stream.Flush();
			}

			{
				MemoryDevice ExpectedDummyDevice(1024);
				MemorySink ExpectedDummySink(ExpectedDummyDevice);
				FileDevice ExpectedDevice(SourceFile, FileMode::Open, FileAccess::Read, FileShare::Read);
				FileSource ExpectedSource(ExpectedDevice);
				InFileStream ExpectedInStream(ExpectedDummySink, ExpectedSource);

				MemoryDevice ActualDummyDevice(1024);
				MemorySink ActualDummySink(ActualDummyDevice);
				FileDevice ActualDevice(TargetFile, FileMode::Open, FileAccess::Read, FileShare::Read);
				FileSource ActualSource(ActualDevice);
				GZipSource ActualCompressionSource(ActualSource);
				InGZipStream ActualInStream(ActualDummySink, ActualCompressionSource);

				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> ExpectedData{};
				{
					Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> Span{};

					while (true)
					{
						bool MadeProgress = false;
						const Elysium::Core::Template::IO::ReadResult ReadResult = ExpectedInStream.ReadBlock(Span);
						switch (ReadResult)
						{
						case Elysium::Core::Template::IO::ReadResult::HasData:
							ExpectedData.PushBackRange(Span.GetData(), Span.GetLength());
							ExpectedInStream.AdvanceReadingBlock(Span.GetLength());
							MadeProgress = true;
							break;
						case Elysium::Core::Template::IO::ReadResult::Pending:
							// for now simply continue running the loop
							MadeProgress = true;
							break;
						case Elysium::Core::Template::IO::ReadResult::EndOfStream:
							break;
						}

						if (!MadeProgress)
						{
							break;
						}
					}
					ExpectedData.PushBack(0x00);
				}


				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> ActualData{};
				{
					Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> Span{};

					while (true)
					{
						bool MadeProgress = false;
						const Elysium::Core::Template::IO::ReadResult ReadResult = ActualInStream.ReadBlock(Span);
						switch (ReadResult)
						{
						case Elysium::Core::Template::IO::ReadResult::HasData:
							ActualData.PushBackRange(Span.GetData(), Span.GetLength());
							ActualInStream.AdvanceReadingBlock(Span.GetLength());

							MadeProgress = true;
							break;
						case Elysium::Core::Template::IO::ReadResult::Pending:
							// for now simply continue running the loop
							MadeProgress = true;
							break;
						case Elysium::Core::Template::IO::ReadResult::EndOfStream:
							break;
						}

						if (!MadeProgress)
						{
							break;
						}
					}
					ActualData.PushBack(0x00);
				}

				Assert::AreEqual(ExpectedData.GetLength(), ActualData.GetLength());

				const char* ExpectedText = reinterpret_cast<char*>(&ExpectedData[0]);
				const char* ActualText = reinterpret_cast<char*>(&ActualData[0]);

				Assert::AreEqual(ExpectedText, ActualText);
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
	};
}
