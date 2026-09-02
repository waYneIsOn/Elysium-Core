#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Atomic.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InOutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/InStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/OutStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Device/FileDevice.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/DeflateSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/ZLibSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Sink/FileSink.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/DeflateSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/ZLibSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/IO/Source/FileSource.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Text/CharacterTraits.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/System/Primitives.hpp"

using namespace Elysium::Core::Template::IO;
using namespace Elysium::Core::Template::IO::Device;
using namespace Elysium::Core::Template::IO::Sink;
using namespace Elysium::Core::Template::IO::Source;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::IO
{
	TEST_CLASS(ZLibStreamTests)
	{;
		using OutFileStream = OutStream<FileSource>;

		using ZLibWritingStream = InStream<ZLibSink<DeflateSink<FileSink>>>;
		using ZLibReadingStream = OutStream<ZLibSource<DeflateSource<FileSource>>>;

		using ZLibCompressionFromFileStream = InOutStream<ZLibSink<DeflateSink<FileSink>>, FileSource>;
	public:
		TEST_METHOD(CompressAndDecompressTest)
		{
			Compress(u8"Lorem Ipsum.txt", u8"Lorem Ipsum - Uncompressed.zlib", Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::Stored);
			Compress(u8"Lorem Ipsum.txt", u8"Lorem Ipsum - StaticOnly.zlib", Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::StaticOnly);
			Compress(u8"Lorem Ipsum.txt", u8"Lorem Ipsum - DynamicOnly.zlib", Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel::DynamicOnly);
		}

		TEST_METHOD(ExternalFilesTest)
		{
			Compare(u8"Lorem Ipsum.txt", u8"Lorem Ipsum.zlib");
		}
	private:
		inline void Compress(const char8_t* SourceFile, const char8_t* TargetFile, Elysium::Core::Template::IO::Compression::Algorithm::Deflate::DeflateCompressionLevel CompressionLevel)
		{
			{
				Elysium::Core::Template::System::size PendingCount = 0;

				FileDevice WriteDevice(TargetFile, FileMode::Create, FileAccess::Write);
				FileSink Sink(WriteDevice);
				DeflateSink DeflateSink(Sink, CompressionLevel);
				ZLibSink CompressionSink(DeflateSink);

				FileDevice ReadDevice(SourceFile, FileMode::Open, FileAccess::Read, FileShare::Read);
				FileSource Source(ReadDevice);

				ZLibCompressionFromFileStream Stream(CompressionSink, Source);

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

			Compare(SourceFile, TargetFile);
		}

		inline void Compare(const char8_t* SourceFile, const char8_t* CompressedFile)
		{
			FileDevice ExpectedDevice(SourceFile, FileMode::Open, FileAccess::Read, FileShare::Read);
			FileSource ExpectedSource(ExpectedDevice);
			OutFileStream ExpectedOutStream(ExpectedSource);

			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> ExpectedData{};
			{
				Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> Span{};

				while (true)
				{
					bool MadeProgress = false;
					const Elysium::Core::Template::IO::ReadResult ReadResult = ExpectedOutStream.ReadBlock(Span);
					switch (ReadResult)
					{
					case Elysium::Core::Template::IO::ReadResult::HasData:
						ExpectedData.PushBackRange(Span.GetData(), Span.GetLength());
						ExpectedOutStream.AdvanceReadingBlock(Span.GetLength());
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

			FileDevice ActualDevice(CompressedFile, FileMode::Open, FileAccess::Read, FileShare::Read);
			FileSource ActualSource(ActualDevice);
			DeflateSource ActualDecompressionSource(ActualSource);
			ZLibSource ActualCompressionSource(ActualDecompressionSource);
			ZLibReadingStream ActualOutStream(ActualCompressionSource);

			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> ActualData{};
			{
				Elysium::Core::Template::Container::View::Span<Elysium::Core::Template::System::byte> Span{};

				while (true)
				{
					bool MadeProgress = false;
					const Elysium::Core::Template::IO::ReadResult ReadResult = ActualOutStream.ReadBlock(Span);
					switch (ReadResult)
					{
					case Elysium::Core::Template::IO::ReadResult::HasData:
						ActualData.PushBackRange(Span.GetData(), Span.GetLength());
						ActualOutStream.AdvanceReadingBlock(Span.GetLength());

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

			const Elysium::Core::Template::System::size FileLength = ActualDevice.GetLength();
			const Elysium::Core::Template::System::size FilePosition = ActualDevice.GetPosition();

			Assert::AreEqual(FileLength, FilePosition);
			Assert::AreEqual(ExpectedData.GetLength(), ActualData.GetLength());

			const char* ExpectedText = reinterpret_cast<char*>(&ExpectedData[0]);
			const char* ActualText = reinterpret_cast<char*>(&ActualData[0]);

			Assert::AreEqual(ExpectedText, ActualText);
		}
	};
}
