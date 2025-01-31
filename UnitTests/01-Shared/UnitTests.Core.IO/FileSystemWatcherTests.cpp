#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/File.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO.FileSystem.Watcher/FileSystemWatcher.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO.FileSystem.Watcher/FileSystemWatcherAsyncResult.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Delegate.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/RunTimeTypeInformation/Enumeration.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ManualResetEvent.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::RunTimeTypeInformation;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO
{
	TEST_CLASS(FileSystemWatcherTests)
	{
	public:
		TEST_METHOD(WatchAllChangesInDirectory)
		{
			File::Delete(_FilePath);
			File::Delete(_FilePath2);

			FileSystemWatcher Watcher = FileSystemWatcher(_Directory);
			Watcher.OnChanged += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnChanged>(*this);
			Watcher.OnCreated += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnCreated>(*this);
			Watcher.OnDeleted += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnDeleted>(*this);
			Watcher.OnError += Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnError>(*this);
			Watcher.OnRenamed += Delegate<void, const FileSystemWatcher&, const RenamedEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnRenamed>(*this);
			
			/*
			* Make sure this loop runs for a multiple of two!
			* Because of calling EndInit() with Modulo 2 the last run should work without calling it,
			* testing what happens when FileSystemWatcher runs out of scope in terms of IOCP.
			*/
			for (Elysium::Core::Template::System::uint8_t i = 0; i < 4; ++i)
			{
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
					Assert::Fail((wchar_t*)&ex.GetExceptionMessage()[0]);
				}

				// test both with and without calling EndInit()
				if (i % 2 == 0)
				{
					Watcher.EndInit();
				}

				Logger::WriteMessage(L"----\r\n");
			}
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
			Logger::WriteMessage("FileSystemWatcher_OnChanged\r\n");

			const WatcherChangeTypes ChangeType = EventArgs.GetChangeType();
			//const Utf8String ChangeTypeName = Enumeration<WatcherChangeTypes>::GetNamedValue<ChangeType>();

			const Utf8String FullPath = EventArgs.GetFullPath();
			Logger::WriteMessage("\tFullPath: ");
			Logger::WriteMessage((char*)&FullPath[0]);
			Logger::WriteMessage("\r\n");

			const Utf8String FileName = EventArgs.GetName();
			Logger::WriteMessage("\tFileName: ");
			Logger::WriteMessage((char*)&FileName[0]);
			Logger::WriteMessage("\r\n");

			_ChangedResetEvent.Set();
		}

		void FileSystemWatcher_OnCreated(const FileSystemWatcher& Watcher, const FileSystemEventArgs& EventArgs)
		{
			Logger::WriteMessage("FileSystemWatcher_OnCreated\r\n");

			const WatcherChangeTypes ChangeType = EventArgs.GetChangeType();

			const Utf8String FullPath = EventArgs.GetFullPath();
			Logger::WriteMessage("\tFullPath: ");
			Logger::WriteMessage((char*)&FullPath[0]);
			Logger::WriteMessage("\r\n");

			const Utf8String FileName = EventArgs.GetName();
			Logger::WriteMessage("\tFileName: ");
			Logger::WriteMessage((char*)&FileName[0]);
			Logger::WriteMessage("\r\n");

			_CreatedResetEvent.Set();
		}

		void FileSystemWatcher_OnDeleted(const FileSystemWatcher& Watcher, const FileSystemEventArgs& EventArgs)
		{
			Logger::WriteMessage("FileSystemWatcher_OnDeleted\r\n");

			const WatcherChangeTypes ChangeType = EventArgs.GetChangeType();

			const Utf8String FullPath = EventArgs.GetFullPath();
			Logger::WriteMessage("\tFullPath: ");
			Logger::WriteMessage((char*)&FullPath[0]);
			Logger::WriteMessage("\r\n");

			const Utf8String FileName = EventArgs.GetName();
			Logger::WriteMessage("\tFileName: ");
			Logger::WriteMessage((char*)&FileName[0]);
			Logger::WriteMessage("\r\n");

			_DeletedResetEvent.Set();
		}

		void FileSystemWatcher_OnError(const FileSystemWatcher& Watcher, const ErrorEventArgs& EventArgs)
		{
			// ToDo:
			Logger::WriteMessage("....");

			Logger::WriteMessage("FileSystemWatcher_OnError\r\n");
			_ErrorResetEvent.Set();
		}

		void FileSystemWatcher_OnRenamed(const FileSystemWatcher& Watcher, const RenamedEventArgs& EventArgs)
		{
			Logger::WriteMessage("FileSystemWatcher_OnRenamed\r\n");

			const WatcherChangeTypes ChangeType = EventArgs.GetChangeType();

			const Utf8String FullPath = EventArgs.GetFullPath();
			Logger::WriteMessage("\tFullPath: ");
			Logger::WriteMessage((char*)&FullPath[0]);
			Logger::WriteMessage("\r\n");

			const Utf8String FileName = EventArgs.GetName();
			Logger::WriteMessage("\tFileName: ");
			Logger::WriteMessage((char*)&FileName[0]);
			Logger::WriteMessage("\r\n");
			/*
			const Utf8String OldFullPath = EventArgs.GetOldFullPath();
			Logger::WriteMessage("\tOldFullPath: ");
			Logger::WriteMessage((char*)&OldFullPath[0]);
			Logger::WriteMessage("\r\n");
			*/
			const Utf8String OldFileName = EventArgs.GetOldName();
			Logger::WriteMessage("\tOldName: ");
			Logger::WriteMessage((char*)&OldFileName[0]);
			Logger::WriteMessage("\r\n");
			
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