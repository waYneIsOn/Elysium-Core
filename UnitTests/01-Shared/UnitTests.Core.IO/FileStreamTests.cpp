#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/IOException.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO
{
	TEST_CLASS(FileStreamTests)
	{
	public:
		TEST_METHOD(AsyncReadAndWrite)
		{
			const size_t BufferLength = 255;
			byte Buffer[BufferLength];

			FileStream SourceStream = FileStream(u8"TestFiles\\Elysium.Core.IO\\Lorem Ipsum.txt", FileMode::Open, FileAccess::Read, FileShare::None);
			FileStream TargetStream = FileStream(u8"AsyncFileStream.txt", FileMode::Create, FileAccess::Write, FileShare::None);

			size BytesToRead = SourceStream.GetLength();
			size TotalBytesRead = 0;
			while (TotalBytesRead != BytesToRead)
			{
				const IAsyncResult* ReadResult = SourceStream.BeginRead((byte*)&Buffer[0], BufferLength,
					Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<FileStreamTests, &FileStreamTests::ReadCallback>(*this), nullptr);
				ReadResult->GetAsyncWaitHandle().WaitOne();

				FileStreamAsyncResult* CastReadResult = (Elysium::Core::IO::FileStreamAsyncResult*)ReadResult;

				uint16_t ReadErrorCode = CastReadResult->GetErrorCode();
				if (ReadErrorCode != static_cast<uint16_t>(Elysium::Core::Internal::WindowsErrorCode::Success))
				{
					TargetStream.EndRead(ReadResult);
					throw IOException(static_cast<Elysium::Core::uint32_t>(ReadErrorCode));
				}
				size BytesRead = TargetStream.EndRead(ReadResult);
				TotalBytesRead += BytesRead;

				const IAsyncResult* WriteResult = TargetStream.BeginWrite((byte*)&Buffer[0], BytesRead,
					Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<FileStreamTests, &FileStreamTests::WriteCallback>(*this), nullptr);
				WriteResult->GetAsyncWaitHandle().WaitOne();

				FileStreamAsyncResult* CastWriteResult = (FileStreamAsyncResult*)WriteResult;
				uint16_t WriteErrorCode = CastWriteResult->GetErrorCode();
				if (WriteErrorCode != static_cast<uint16_t>(Elysium::Core::Internal::WindowsErrorCode::Success))
				{
					TargetStream.EndWrite(WriteResult);
					throw IOException(static_cast<Elysium::Core::uint32_t>(WriteErrorCode));
				}
				TargetStream.EndWrite(WriteResult);
			}

			Assert::AreEqual(BytesToRead, TotalBytesRead);
		}
	private:
		void ReadCallback(const Elysium::Core::IAsyncResult* Result)
		{
			const FileStreamAsyncResult* AsyncResult = (const FileStreamAsyncResult*)Result;
			FileStream& TargetStream = AsyncResult->GetFileStream();

			((const Elysium::Core::Threading::ManualResetEvent&)Result->GetAsyncWaitHandle()).Set();
		}

		void WriteCallback(const Elysium::Core::IAsyncResult* Result)
		{
			const FileStreamAsyncResult* AsyncResult = (const FileStreamAsyncResult*)Result;
			FileStream& TargetStream = AsyncResult->GetFileStream();

			((const Elysium::Core::Threading::ManualResetEvent&)Result->GetAsyncWaitHandle()).Set();
		}
	};
}