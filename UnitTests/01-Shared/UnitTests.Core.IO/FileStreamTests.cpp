#include "CppUnitTest.h"

#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;

namespace UnitTests::Core::IO
{
	TEST_CLASS(FileStreamTests)
	{
	public:
		TEST_METHOD(AsyncWrite)
		{
			FileStream TargetStream = FileStream(u8"AsyncFileStream.txt", FileMode::Create, FileAccess::Write, FileShare::None);
			const IAsyncResult* WriteResult = TargetStream.BeginWrite((byte*)&_Content[0], _Content.GetLength(),
				Delegate<void, const Elysium::Core::IAsyncResult*>::Bind<FileStreamTests, &FileStreamTests::WriteCallback>(*this), nullptr);
			WriteResult->GetAsyncWaitHandle().WaitOne();
			delete WriteResult;
		}
	private:
		String _Content = u8"lorem ipsum et cetera pp.";

		void WriteCallback(const Elysium::Core::IAsyncResult* Result)
		{
			const FileStreamAsyncResult* AsyncResult = (const FileStreamAsyncResult*)Result;
			FileStream& TargetStream = AsyncResult->GetFileStream();
			TargetStream.EndWrite(Result);

			((const Elysium::Core::Threading::ManualResetEvent&)Result->GetAsyncWaitHandle()).Set();
		}
	};
}