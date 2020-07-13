#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(FileStreamTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
		}

		TEST_METHOD(WriteReadCopyTo)
		{
			// write into a filestream
			FileStream InputOutputStream = FileStream(u"FS1.txt", FileMode::Create, FileAccess::ReadWrite, FileShare::ReadWrite);
			byte DataToWrite[] = { 0x73, 0x6F, 0x6D, 0x65, 0x20, 0x64, 0x61, 0x74, 0x61 };
			InputOutputStream.Write(DataToWrite, 9);

			// use the same stream to read from the file (in a single command)
			InputOutputStream.SetPosition(0);
			byte DataToRead[9];
			size_t BytesRead = InputOutputStream.Read(&DataToRead[0], 9);
			Assert::AreEqual((size_t)9, BytesRead);
			InputOutputStream.Close();

			// check the written data by using another stream (reading multiple times)
			memset(&DataToRead[0], 0x00, 9);
			FileStream OutputStream = FileStream(u"FS1.txt", FileMode::Open, FileAccess::Read, FileShare::Read);
			BytesRead = OutputStream.Read(&DataToRead[0], 4);
			Assert::AreEqual((size_t)4, BytesRead);
			BytesRead = OutputStream.Read(&DataToRead[4], 4);
			Assert::AreEqual((size_t)4, BytesRead);
			BytesRead = OutputStream.Read(&DataToRead[8], 1);
			Assert::AreEqual((size_t)1, BytesRead);
			BytesRead = OutputStream.Read(&DataToRead[10], 20);
			Assert::AreEqual((size_t)0, BytesRead);
			Assert::AreEqual((byte)'s', DataToRead[0]);
			Assert::AreEqual((byte)'o', DataToRead[1]);
			Assert::AreEqual((byte)'m', DataToRead[2]);
			Assert::AreEqual((byte)'e', DataToRead[3]);
			Assert::AreEqual((byte)' ', DataToRead[4]);
			Assert::AreEqual((byte)'d', DataToRead[5]);
			Assert::AreEqual((byte)'a', DataToRead[6]);
			Assert::AreEqual((byte)'t', DataToRead[7]);
			Assert::AreEqual((byte)'a', DataToRead[8]);

			// copy from the previously used file stream to a memory stream
			OutputStream.SetPosition(0);
			MemoryStream DestinationStream = MemoryStream();
			OutputStream.CopyTo(DestinationStream);
			Assert::AreEqual((size_t)9, DestinationStream.GetLength());

			// read from memory stream to make sure all bytes were written correctly
			memset(&DataToRead[0], 0x00, 9);
			DestinationStream.SetPosition(0);
			BytesRead = DestinationStream.Read(&DataToRead[0], 9);
			Assert::AreEqual((size_t)9, BytesRead);
			Assert::AreEqual((byte)'s', DataToRead[0]);
			Assert::AreEqual((byte)'o', DataToRead[1]);
			Assert::AreEqual((byte)'m', DataToRead[2]);
			Assert::AreEqual((byte)'e', DataToRead[3]);
			Assert::AreEqual((byte)' ', DataToRead[4]);
			Assert::AreEqual((byte)'d', DataToRead[5]);
			Assert::AreEqual((byte)'a', DataToRead[6]);
			Assert::AreEqual((byte)'t', DataToRead[7]);
			Assert::AreEqual((byte)'a', DataToRead[8]);
		}
	};
}
