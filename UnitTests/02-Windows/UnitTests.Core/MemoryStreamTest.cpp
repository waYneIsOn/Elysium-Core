#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO
{
	TEST_CLASS(MemoryStreamTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			MemoryStream MS1 = MemoryStream();
		}

		TEST_METHOD(WriteReadCopyTo)
		{
			// write into a memory stream
			MemoryStream SourceStream = MemoryStream();
			byte* DataToWrite = (byte*)"some data";
			SourceStream.Write(&DataToWrite[1], 7);
			Assert::AreEqual((Elysium::Core::size)7, SourceStream.GetLength());

			// check the written data by reading it
			byte DataToRead[7];
			SourceStream.Read(&DataToRead[0], 7);
			Assert::AreEqual((Elysium::Core::size)7, SourceStream.GetLength());
			Assert::AreEqual((byte)'o', DataToRead[0]);
			Assert::AreEqual((byte)'m', DataToRead[1]);
			Assert::AreEqual((byte)'e', DataToRead[2]);
			Assert::AreEqual((byte)' ', DataToRead[3]);
			Assert::AreEqual((byte)'d', DataToRead[4]);
			Assert::AreEqual((byte)'a', DataToRead[5]);
			Assert::AreEqual((byte)'t', DataToRead[6]);

			// copy from the previously used memory stream to another
			SourceStream.SetPosition(0);
			MemoryStream DestinationStream = MemoryStream();
			SourceStream.CopyTo(DestinationStream);
			Assert::AreEqual((Elysium::Core::size)7, DestinationStream.GetLength());
			/*
			Assert::AreEqual((byte)'o', DataToRead[0]);
			Assert::AreEqual((byte)'m', DataToRead[1]);
			Assert::AreEqual((byte)'e', DataToRead[2]);
			Assert::AreEqual((byte)' ', DataToRead[3]);
			Assert::AreEqual((byte)'d', DataToRead[4]);
			Assert::AreEqual((byte)'a', DataToRead[5]);
			Assert::AreEqual((byte)'t', DataToRead[6]);
			*/
		}
	};
}
