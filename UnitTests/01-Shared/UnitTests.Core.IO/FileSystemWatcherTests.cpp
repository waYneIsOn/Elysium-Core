#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/File.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO.FileSystem.Watcher/FileSystemWatcher.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO.FileSystem.Watcher/FileSystemWatcherAsyncResult.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Delegate.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ManualResetEvent.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO
{
	TEST_CLASS(FileSystemWatcherTests)
	{
	public:
		TEST_METHOD(WatchAllChangesInDirectory)
		{
			Assert::Fail(L"IOCP implementation is not correct! things run out of scope causing problems!");

			File::Delete(_FilePath);
			File::Delete(_FilePath2);

			FileSystemWatcher Watcher = FileSystemWatcher(_Directory);
			Watcher.OnChanged += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnChanged>(*this);
			Watcher.OnCreated += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnCreated>(*this);
			Watcher.OnDeleted += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnDeleted>(*this);
			Watcher.OnError += Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnError>(*this);
			Watcher.OnRenamed += Delegate<void, const FileSystemWatcher&, const RenamedEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnRenamed>(*this);
			Watcher.BeginInit();

			try
			{
				CreateFileAndWait();
				ChangeFileAndWait();
				RenameFileAndWait();
				DeleteFileAndWait();
			}
			catch(const Exception& ex)
			{
				Utf8String sdf = ex.GetExceptionMessage();

				//Logger::WriteMessage("------");
				Assert::Fail((wchar_t*)&ex.GetExceptionMessage()[0]);
			}

			//Watcher.EndInit();

			Assert::Fail(L"while this test works, the implemenation of iocp-cancelation is not correct yet (multiple threads deleting FileSystemWatcherAsyncResult for instance)");
		}

		TEST_METHOD(WatchFile)
		{
			Assert::Fail();
		}
	private:
		void CreateFileAndWait()
		{
			FileStream TargetFileStream = FileStream(_FilePath, FileMode::CreateNew, FileAccess::Write);
			if(!_CreatedResetEvent.WaitOne(1000))
			{
				Assert::Fail(L"File creation event was not triggered within a second.");
			}
			_CreatedResetEvent.Reset();
		}

		void ChangeFileAndWait()
		{
			byte Buffer[1024] = { 0 };

			FileStream TargetFileStream = FileStream(_FilePath, FileMode::Open, FileAccess::Write);
			TargetFileStream.Write(Buffer, 1024);
			TargetFileStream.Flush();
			if (!_ChangedResetEvent.WaitOne(1000))
			{
				Assert::Fail(L"File change event was not triggered within a second.");
			}
			_ChangedResetEvent.Reset();
		}

		void RenameFileAndWait()
		{
			File::Move(_FilePath, _FilePath2, false);
			if (!_RenamedResetEvent.WaitOne(1000))
			{
				Assert::Fail(L"File rename event was not triggered within a second.");
			}
			_RenamedResetEvent.Reset();

			File::Move(_FilePath2, _FilePath, false);
			if (!_RenamedResetEvent.WaitOne(1000))
			{
				Assert::Fail(L"File rename event was not triggered within a second.");
			}
			_RenamedResetEvent.Reset();
		}

		void DeleteFileAndWait()
		{
			File::Delete(_FilePath);
			if (!_DeletedResetEvent.WaitOne(1000))
			{
				Assert::Fail(L"File deletion event was not triggered within a second.");
			}
			_DeletedResetEvent.Reset();
		}

		void CreateFolderAndWait()
		{

		}

		void ChangeFolderAndWait()
		{

		}

		void RenameFolderAndWait()
		{

		}

		void DeleteFolderAndWait()
		{

		}

		void FileSystemWatcher_OnChanged(const FileSystemWatcher& Watcher, const FileSystemEventArgs& EventArgs)
		{
			_ChangedResetEvent.Set();
		}

		void FileSystemWatcher_OnCreated(const FileSystemWatcher& Watcher, const FileSystemEventArgs& EventArgs)
		{
			_CreatedResetEvent.Set();
		}

		void FileSystemWatcher_OnDeleted(const FileSystemWatcher& Watcher, const FileSystemEventArgs& EventArgs)
		{
			_DeletedResetEvent.Set();
		}

		void FileSystemWatcher_OnError(const FileSystemWatcher& Watcher, const ErrorEventArgs& EventArgs)
		{
			// ToDo:
			Logger::WriteMessage(L"....");

			_ErrorResetEvent.Set();
		}

		void FileSystemWatcher_OnRenamed(const FileSystemWatcher& Watcher, const RenamedEventArgs& EventArgs)
		{
			_RenamedResetEvent.Set();
		}
	private:
		const char8_t* _Directory = u8"C:\\test";	// ToDo: use Directory::CurrentDirectory()
		const char8_t* _FilePath = u8"C:\\test\\file.txt";
		const char8_t* _FilePath2 = u8"C:\\test\\file2.txt";

		ManualResetEvent _ChangedResetEvent = ManualResetEvent(false);
		ManualResetEvent _CreatedResetEvent = ManualResetEvent(false);
		ManualResetEvent _DeletedResetEvent = ManualResetEvent(false);
		ManualResetEvent _ErrorResetEvent = ManualResetEvent(false);
		ManualResetEvent _RenamedResetEvent = ManualResetEvent(false);
	};
}