#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/BinaryReader.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO
{
	TEST_CLASS(BinaryReaderTests)
	{
	public:
		TEST_METHOD(ReadUsingBufferLargerThanInternal)
		{
			const size_t BufferSize = 8192;
			byte Buffer[BufferSize];

			ReadSomeFile(&Buffer[0], BufferSize);
		}

		TEST_METHOD(ReadUsingBufferSmallerThanInternal)
		{
			const size_t BufferSize = 2048;
			byte Buffer[BufferSize];

			ReadSomeFile(&Buffer[0], BufferSize);
		}
	private:
		void ReadSomeFile(byte* Buffer, const size_t Count)
		{
			FileStream SourceStream = FileStream(u8"TestFiles\\Elysium.Core.IO\\Lorem Ipsum.txt", FileMode::Open, FileAccess::Read, FileShare::None);
			BinaryReader Reader = BinaryReader(SourceStream, Encoding::UTF8(), false);

			const size_t TotalBytesToRead = SourceStream.GetLength();
			size_t TotalBytesRead = 0;
			do
			{
				const size_t BytesRead = Reader.ReadBytes(Buffer, Count);
				if (BytesRead == 0)
				{	// this shouldn't happen in the middle of reading a filestream
					break;
				}

				TotalBytesRead += BytesRead;
			} while (TotalBytesRead < TotalBytesToRead);

			Assert::AreEqual(TotalBytesToRead, TotalBytesRead);
		}
	};
}
