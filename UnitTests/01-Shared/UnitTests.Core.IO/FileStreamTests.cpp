#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Delegate.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/IAsyncResult.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/IOException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ManualResetEvent.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO
{
	TEST_CLASS(FileStreamTests)
	{
	public:
		TEST_METHOD(WriteReadCopyTo)
		{
			// write into a filestream
			FileStream InputOutputStream = FileStream(u8"FS1.txt", FileMode::Create, FileAccess::Read | FileAccess::Write, FileShare::ReadWrite);
			byte DataToWrite[] = { 0x73, 0x6F, 0x6D, 0x65, 0x20, 0x64, 0x61, 0x74, 0x61 };
			InputOutputStream.Write(DataToWrite, 9);

			// use the same stream to read from the file (in a single command)
			InputOutputStream.SetPosition(0);
			byte DataToRead[30];
			Elysium::Core::size BytesRead = InputOutputStream.Read(&DataToRead[0], 30);
			Assert::AreEqual((Elysium::Core::size)9, BytesRead);
			InputOutputStream.Close();

			// check the written data by using another stream (reading multiple times)
			memset(&DataToRead[0], 0x00, 9);
			FileStream OutputStream = FileStream(u8"FS1.txt", FileMode::Open, FileAccess::Read, FileShare::Read);
			BytesRead = OutputStream.Read(&DataToRead[0], 4);
			Assert::AreEqual((Elysium::Core::size)4, BytesRead);
			BytesRead = OutputStream.Read(&DataToRead[4], 4);
			Assert::AreEqual((Elysium::Core::size)4, BytesRead);
			BytesRead = OutputStream.Read(&DataToRead[8], 1);
			Assert::AreEqual((Elysium::Core::size)1, BytesRead);
			BytesRead = OutputStream.Read(&DataToRead[10], 20);
			Assert::AreEqual((Elysium::Core::size)0, BytesRead);
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
			Assert::AreEqual((Elysium::Core::size)9, DestinationStream.GetLength());

			// read from memory stream to make sure all bytes were written correctly
			memset(&DataToRead[0], 0x00, 9);
			DestinationStream.SetPosition(0);
			BytesRead = DestinationStream.Read(&DataToRead[0], 9);
			Assert::AreEqual((Elysium::Core::size)9, BytesRead);
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

		TEST_METHOD(AsyncReadAndWriteThroughIOThreads)
		{
			_CompletionSignal.Reset();

			FileStream SourceStream = FileStream(u8"TestFiles\\Elysium.Core.IO\\Lorem Ipsum.txt", FileMode::Open, FileAccess::Read, FileShare::None,
				4096, FileOptions::Asynchronous);
			FileStream TargetStream = FileStream(u8"AsyncFileStream.txt", FileMode::Create, FileAccess::Write, FileShare::None,
				4096, FileOptions::Asynchronous);

			_BytesToRead = SourceStream.GetLength();
			_TotalBytesWritten = 0;
			_SourceStream = &SourceStream;
			_TargetStream = &TargetStream;

			StartAsyncReadWrite();

			// wait for completion
			_CompletionSignal.WaitOne();
		}

		TEST_METHOD(AsyncReadAndWriteThroughWorkerThreads)
		{
			_CompletionSignal.Reset();

			FileStream SourceStream = FileStream(u8"TestFiles\\Elysium.Core.IO\\Lorem Ipsum.txt", FileMode::Open, FileAccess::Read, FileShare::None,
				4096, FileOptions::None);
			FileStream TargetStream = FileStream(u8"AsyncFileStream.txt", FileMode::Create, FileAccess::Write, FileShare::None,
				4096, FileOptions::None);

			_BytesToRead = SourceStream.GetLength();
			_TotalBytesWritten = 0;
			_SourceStream = &SourceStream;
			_TargetStream = &TargetStream;

			StartAsyncReadWrite();

			// wait for completion
			_CompletionSignal.WaitOne();
		}
	private:
		inline static ManualResetEvent _CompletionSignal = ManualResetEvent(false);
		static const size _BufferLength = 255;
		byte _Buffer[_BufferLength];

		FileStream* _SourceStream = nullptr;
		FileStream* _TargetStream = nullptr;

		size _BytesToRead = 0;
		size _TotalBytesWritten = 0;

		void StartAsyncReadWrite()
		{
			if (_TotalBytesWritten < _BytesToRead)
			{
				const Elysium::Core::IAsyncResult* ReadResult = _SourceStream->BeginRead(&_Buffer[0], _BufferLength,
					Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<FileStreamTests, &FileStreamTests::ReadCallback>(*this), nullptr);
				ReadResult->GetAsyncWaitHandle().WaitOne();
			}
			else
			{
				_CompletionSignal.Set();
			}
		}

		void ReadCallback(const Elysium::Core::IAsyncResult* Result)
		{
			const FileStreamAsyncResult* ReadResult = (const FileStreamAsyncResult*)Result;
			FileStream& SourceStream = ReadResult->GetFileStream();
			size BytesRead = SourceStream.EndRead(ReadResult);

			const Elysium::Core::IAsyncResult* WriteResult = _TargetStream->BeginWrite(&_Buffer[0], BytesRead,
				Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<FileStreamTests, &FileStreamTests::WriteCallback>(*this), nullptr);
			WriteResult->GetAsyncWaitHandle().WaitOne();
		}

		void WriteCallback(const Elysium::Core::IAsyncResult* Result)
		{
			const FileStreamAsyncResult* WriteResult = (const FileStreamAsyncResult*)Result;
			FileStream& TargetStream = WriteResult->GetFileStream();
			TargetStream.EndWrite(WriteResult);
			_TotalBytesWritten += WriteResult->GetBytesTransferred();

			StartAsyncReadWrite();
		}
	};
}