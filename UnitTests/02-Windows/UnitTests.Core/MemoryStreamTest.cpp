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

namespace UnitTestsCore
{
	TEST_CLASS(Core_MemoryStream)
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
			BYTE* DataToWrite = (BYTE*)"some data";
			SourceStream.Write(&DataToWrite[1], 7);
			Assert::AreEqual((size_t)7, SourceStream.GetLength());

			// check the written data by reading it
			BYTE DataToRead[7];
			SourceStream.Read(&DataToRead[0], 7);
			Assert::AreEqual((size_t)7, SourceStream.GetLength());
			Assert::AreEqual((BYTE)'o', DataToRead[0]);
			Assert::AreEqual((BYTE)'m', DataToRead[1]);
			Assert::AreEqual((BYTE)'e', DataToRead[2]);
			Assert::AreEqual((BYTE)' ', DataToRead[3]);
			Assert::AreEqual((BYTE)'d', DataToRead[4]);
			Assert::AreEqual((BYTE)'a', DataToRead[5]);
			Assert::AreEqual((BYTE)'t', DataToRead[6]);

			// copy from the previously used memory stream to another
			SourceStream.SetPosition(0);
			MemoryStream DestinationStream = MemoryStream();
			SourceStream.CopyTo(DestinationStream);
			Assert::AreEqual((size_t)7, DestinationStream.GetLength());
			/*
			Assert::AreEqual((BYTE)'o', DataToRead[0]);
			Assert::AreEqual((BYTE)'m', DataToRead[1]);
			Assert::AreEqual((BYTE)'e', DataToRead[2]);
			Assert::AreEqual((BYTE)' ', DataToRead[3]);
			Assert::AreEqual((BYTE)'d', DataToRead[4]);
			Assert::AreEqual((BYTE)'a', DataToRead[5]);
			Assert::AreEqual((BYTE)'t', DataToRead[6]);
			*/
		}
	};
}
