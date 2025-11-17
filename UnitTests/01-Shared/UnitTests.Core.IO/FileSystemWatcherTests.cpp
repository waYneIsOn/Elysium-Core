#include <CppUnitTest.h>
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../UnitTestExtensions/ThreadsafeLogger.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/String.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/File.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO.FileSystem.Watcher/FileSystemWatcher.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO.FileSystem.Watcher/FileSystemWatcherAsyncResult.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Delegate.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/FileSystem.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/RunTimeTypeInformation/Enumeration.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/ManualResetEvent.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::RunTimeTypeInformation;
using namespace Elysium::Core::Threading;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//int CurrentDebugFlags = _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// dump memory leaks
/*
int DumpMemoryLeaks = _CrtDumpMemoryLeaks();
//long BreakAllocResult = _CrtSetBreakAlloc(566623);	// Set breakpoint for specific allocation number
long BreakAllocResult = _CrtSetBreakAlloc(166);	// Set breakpoint for specific allocation number
*/
namespace UnitTests::Core::IO
{
	TEST_CLASS(FileSystemWatcherTests)
	{
	public:
		BEGIN_TEST_METHOD_ATTRIBUTE(A_RunAllTestMultipleTimesToProvokeCodeErrors)
			TEST_METHOD_ATTRIBUTE(L"Category", L"LongRunning")
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(A_RunAllTestMultipleTimesToProvokeCodeErrors)
		{
			const DateTime Now = DateTime::UtcNow();
			const DateTime End = DateTime::UtcNow() + TimeSpan::FromHours(3);

			while (DateTime::UtcNow() < End)
			{
				NonUTWatchAllChanges();
				NonUTWatchFilteredChanges();
				NonUTWatchZeroChanges();
				NonUTProvokeBufferOverflow();
				NonUTProvokeOtherErrors();
				NonUTRapidFire();
				NonUTReuse();
			}
		}

		TEST_METHOD(WatchAllChanges)
		{
			NonUTWatchAllChanges();
		}

		TEST_METHOD(WatchFilteredChanges)
		{
			NonUTWatchFilteredChanges();
		}

		TEST_METHOD(WatchZeroChanges)
		{
			NonUTWatchZeroChanges();
		}

		TEST_METHOD(ProvokeBufferOverflow)
		{
			NonUTProvokeBufferOverflow();
		}
		
		TEST_METHOD(ProvokeOtherErrors)
		{
			NonUTProvokeOtherErrors();
		}

		TEST_METHOD(RapidFire)
		{
			NonUTRapidFire();
		}

		TEST_METHOD(Reuse)
		{
			NonUTReuse();
		}
	private:
		void NonUTRapidFire()
		{
			// This tests for the following errors:
			//	- Exception thrown at 0x0000000000000000 in testhost.exe: 0xC0000005: Access violation executing location 0x0000000000000000.
			// Happens in some os-thread and cannot be debugged. It most likely means that FileSystemWatcherAsyncResult gets deleted
			// too early in which case the vtable lookup would return a nullptr.
			// - CloseHandle(...) was called with no in-flight ios (BeginRead() followed by callback)
			for (int i = 0; i < 1000; ++i)
			{
				FileSystemWatcher DirectoryWatcher = FileSystemWatcher(_BaseDirectory);
				DirectoryWatcher.BeginInit();
			}
		}

		void NonUTWatchAllChanges()
		{
			File::Delete(_FilePath0);
			File::Delete(_FilePath1);
			File::Delete(_OtherFilePath0);

			Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath0);
			Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath1);

			FileSystemWatcher DirectoryWatcher = FileSystemWatcher(_BaseDirectory);
			DirectoryWatcher.OnChanged += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnChanged>(*this);
			DirectoryWatcher.OnCreated += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnCreated>(*this);
			DirectoryWatcher.OnDeleted += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnDeleted>(*this);
			DirectoryWatcher.OnError += Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnError>(*this);
			DirectoryWatcher.OnRenamed += Delegate<void, const FileSystemWatcher&, const RenamedEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnRenamed>(*this);

			/*
			* Make sure this loop runs for a multiple of two!
			* Because of calling EndInit() with Modulo 2 the last run should work without calling it,
			* testing what happens when FileSystemWatcher runs out of scope in terms of IOCP.
			*/
			for (Elysium::Core::Template::System::uint8_t i = 0; i < 4; ++i)
			{
				DirectoryWatcher.BeginInit();
				
				CreateFileAndWait(_FilePath0, _CreatedResetEvent, true);
				ChangeFileAndWait(_FilePath0, _ChangedResetEvent, true);
				RenameFileAndWait(_FilePath0, _FilePath1, _RenamedResetEvent, true);
				DeleteFileAndWait(_FilePath0, _DeletedResetEvent, true);

				CreateFolderAndWait(_DirectoryPath0, _CreatedResetEvent, true);
				RenameFolderAndWait(_DirectoryPath0, _DirectoryPath1, _RenamedResetEvent, true);
				DeleteFolderAndWait(_DirectoryPath0, _DeletedResetEvent, true);
				
				CreateFileAndWait(_OtherFilePath0, _OtherCreatedResetEvent, true);
				DeleteFileAndWait(_OtherFilePath0, _OtherDeletedResetEvent, true);

				// test both with and without calling EndInit()
				if (i % 2 == 0)
				{
					//DirectoryWatcher.EndInit();
				}

				ThreadsafeLogger::WriteMessage(L"----\r\n");
			}
		}

		void NonUTWatchFilteredChanges()
		{
			// only text-files
			{
				File::Delete(_FilePath0);
				File::Delete(_FilePath1);
				File::Delete(_OtherFilePath0);

				Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath0);
				Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath1);

				FileSystemWatcher FileWatcher = FileSystemWatcher(_BaseDirectory, u8"*.txt");
				FileWatcher.OnChanged += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnChanged>(*this);
				FileWatcher.OnCreated += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnCreated>(*this);
				FileWatcher.OnDeleted += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnDeleted>(*this);
				FileWatcher.OnError += Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnError>(*this);
				FileWatcher.OnRenamed += Delegate<void, const FileSystemWatcher&, const RenamedEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnRenamed>(*this);

				/*
				* Make sure this loop runs for a multiple of two!
				* Because of calling EndInit() with Modulo 2 the last run should work without calling it,
				* testing what happens when FileSystemWatcher runs out of scope in terms of IOCP.
				*/
				for (Elysium::Core::Template::System::uint8_t i = 0; i < 4; ++i)
				{
					FileWatcher.BeginInit();
					
					CreateFileAndWait(_FilePath0, _CreatedResetEvent, true);
					ChangeFileAndWait(_FilePath0, _ChangedResetEvent, true);
					RenameFileAndWait(_FilePath0, _FilePath1, _RenamedResetEvent, true);
					DeleteFileAndWait(_FilePath0, _DeletedResetEvent, true);
					
					CreateFolderAndWait(_DirectoryPath0, _CreatedResetEvent, false);
					RenameFolderAndWait(_DirectoryPath0, _DirectoryPath1, _RenamedResetEvent, false);
					DeleteFolderAndWait(_DirectoryPath0, _DeletedResetEvent, false);

					CreateFileAndWait(_OtherFilePath0, _OtherCreatedResetEvent, false);
					DeleteFileAndWait(_OtherFilePath0, _OtherDeletedResetEvent, false);

					// test both with and without calling EndInit()
					if (i % 2 == 0)
					{
						//FileWatcher.EndInit();
					}

					ThreadsafeLogger::WriteMessage(L"----\r\n");
				}
			}

			// only log-files
			{
				File::Delete(_FilePath0);
				File::Delete(_FilePath1);
				File::Delete(_OtherFilePath0);

				Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath0);
				Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath1);

				FileSystemWatcher FileWatcher = FileSystemWatcher(_BaseDirectory, u8"*.log");
				FileWatcher.OnChanged += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnChanged>(*this);
				FileWatcher.OnCreated += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnCreated>(*this);
				FileWatcher.OnDeleted += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnDeleted>(*this);
				FileWatcher.OnError += Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnError>(*this);
				FileWatcher.OnRenamed += Delegate<void, const FileSystemWatcher&, const RenamedEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnRenamed>(*this);

				/*
				* Make sure this loop runs for a multiple of two!
				* Because of calling EndInit() with Modulo 2 the last run should work without calling it,
				* testing what happens when FileSystemWatcher runs out of scope in terms of IOCP.
				*/
				for (Elysium::Core::Template::System::uint8_t i = 0; i < 4; ++i)
				{
					FileWatcher.BeginInit();

					CreateFileAndWait(_FilePath0, _CreatedResetEvent, false);
					ChangeFileAndWait(_FilePath0, _ChangedResetEvent, false);
					RenameFileAndWait(_FilePath0, _FilePath1, _RenamedResetEvent, false);
					DeleteFileAndWait(_FilePath0, _DeletedResetEvent, false);

					CreateFolderAndWait(_DirectoryPath0, _CreatedResetEvent, false);
					RenameFolderAndWait(_DirectoryPath0, _DirectoryPath1, _RenamedResetEvent, false);
					DeleteFolderAndWait(_DirectoryPath0, _DeletedResetEvent, false);

					CreateFileAndWait(_OtherFilePath0, _OtherCreatedResetEvent, true);
					DeleteFileAndWait(_OtherFilePath0, _OtherDeletedResetEvent, true);

					// test both with and without calling EndInit()
					if (i % 2 == 0)
					{
						//FileWatcher.EndInit();
					}

					ThreadsafeLogger::WriteMessage(L"----\r\n");
				}
			}

			// files with specific name independent of extension
			{
				File::Delete(_FilePath0);
				File::Delete(_FilePath1);
				File::Delete(_OtherFilePath0);

				Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath0);
				Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath1);

				FileSystemWatcher FileWatcher = FileSystemWatcher(_BaseDirectory, u8"file.*");
				FileWatcher.OnChanged += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnChanged>(*this);
				FileWatcher.OnCreated += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnCreated>(*this);
				FileWatcher.OnDeleted += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnDeleted>(*this);
				FileWatcher.OnError += Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnError>(*this);
				FileWatcher.OnRenamed += Delegate<void, const FileSystemWatcher&, const RenamedEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnRenamed>(*this);

			}

			// only specific file
			{
				File::Delete(_FilePath0);
				File::Delete(_FilePath1);
				File::Delete(_OtherFilePath0);

				Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath0);
				Elysium::Core::Template::IO::FileSystem::RemoveFolder(_DirectoryPath1);

				FileSystemWatcher FileWatcher = FileSystemWatcher(_BaseDirectory, _OtherFilePath0);
				FileWatcher.OnChanged += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnChanged>(*this);
				FileWatcher.OnCreated += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnCreated>(*this);
				FileWatcher.OnDeleted += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnDeleted>(*this);
				FileWatcher.OnError += Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnError>(*this);
				FileWatcher.OnRenamed += Delegate<void, const FileSystemWatcher&, const RenamedEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnRenamed>(*this);

			}

			// only directories
			{

			}
		}

		void NonUTWatchZeroChanges()
		{
			const Elysium::Core::uint32_t ExecutingThreadId = Elysium::Core::Threading::Thread::GetCurrentThreadIdX();

			ThreadsafeLogger::WriteMessage(L"Main thread: ");
			ThreadsafeLogger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(ExecutingThreadId)[0]);
			ThreadsafeLogger::WriteMessage(L"\r\nwatching directory:\r\n");

			{
				for (Elysium::Core::Template::System::uint8_t i = 0; i < 4; ++i)
				{
					FileSystemWatcher DirectoryWatcher = FileSystemWatcher(_BaseDirectory);
					ThreadsafeLogger::WriteMessage(L"\tBeginInit()\r\n");
					DirectoryWatcher.BeginInit();

					// test both with and without calling EndInit()
					if (i % 2 == 0)
					{
						ThreadsafeLogger::WriteMessage(L"\tEndInit()\r\n");
						//DirectoryWatcher.EndInit();
					}
					else
					{
						ThreadsafeLogger::WriteMessage(L"\trunning out of scope\r\n");
					}
					ThreadsafeLogger::WriteMessage(L"\t----\r\n");
				}
			}

			ThreadsafeLogger::WriteMessage(L"\r\nwatching file:\r\n");
			{
				for (Elysium::Core::Template::System::uint8_t i = 0; i < 4; ++i)
				{
					FileSystemWatcher FileWatcher = FileSystemWatcher(_BaseDirectory, u8"file3.txt");
					ThreadsafeLogger::WriteMessage(L"\tBeginInit()\r\n");
					FileWatcher.BeginInit();

					// test both with and without calling EndInit()
					if (i % 2 == 0)
					{
						ThreadsafeLogger::WriteMessage(L"\tEndInit()\r\n");
						//FileWatcher.EndInit();
					}
					else
					{
						ThreadsafeLogger::WriteMessage(L"\trunning out of scope\r\n");
					}
					ThreadsafeLogger::WriteMessage(L"\t----\r\n");
				}
			}

			ThreadsafeLogger::WriteMessage(L"end of test");
		}

		void NonUTProvokeBufferOverflow()
		{
			File::Delete(_FilePathBufferOverflow);

			{
				FileStream TargetFileStream = FileStream(_FilePathBufferOverflow, FileMode::CreateNew, FileAccess::Write);
			}

			FileSystemWatcher DirectoryWatcher = FileSystemWatcher(_BaseDirectory, u8"*.*", FileSystemWatcher::DefaultNotifyFilters,
				false, 90);
			DirectoryWatcher.OnDeleted += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnDeleted>(*this);
			DirectoryWatcher.OnError += Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnError>(*this);
			DirectoryWatcher.BeginInit();

			File::Delete(_FilePathBufferOverflow);

			const bool WaitResult = _ErrorResetEvent.WaitOne(1000);
			Assert::IsTrue(WaitResult);
		}

		void NonUTProvokeOtherErrors()
		{
			// prepare everything required for the test
			constexpr const Elysium::Core::Template::System::size NumberOfFiles = 1;
			constexpr const char8_t* FileExtension = u8".txt";

			const Elysium::Core::Template::System::size DirectoryLength =
				Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(_ErrorDirectory);

			for (Elysium::Core::Template::System::size i = 0; i < NumberOfFiles; ++i)
			{
				const Elysium::Core::Template::Text::String<char8_t> Index = Elysium::Core::Template::Text::Convert<char8_t>::ToString(i);

				Elysium::Core::Template::Text::String<char8_t> FileName = Elysium::Core::Template::Text::String<char8_t>(
					DirectoryLength + sizeof(char8_t) + Index.GetLength() + sizeof(char8_t) * 4);
				Elysium::Core::Template::Memory::MemCpy(&FileName[0], &_ErrorDirectory[0], DirectoryLength);
				FileName[DirectoryLength] = u8'\\';
				Elysium::Core::Template::Memory::MemCpy(&FileName[DirectoryLength + sizeof(char8_t)], &Index[0], Index.GetLength());
				Elysium::Core::Template::Memory::MemCpy(&FileName[DirectoryLength + sizeof(char8_t) + Index.GetLength()],
					FileExtension, sizeof(char8_t) * 4);

				File::Delete(&FileName[0]);
			}

			bool CreateFolderResult = Elysium::Core::Template::IO::FileSystem::CreateFolder(_ErrorDirectory);
			Assert::IsTrue(CreateFolderResult);

			for (Elysium::Core::Template::System::size i = 0; i < NumberOfFiles; ++i)
			{
				const Elysium::Core::Template::Text::String<char8_t> Index =
					Elysium::Core::Template::Text::Convert<char8_t>::ToString(i);

				Elysium::Core::Template::Text::String<char8_t> FileName = Elysium::Core::Template::Text::String<char8_t>(
					DirectoryLength + sizeof(char8_t) + Index.GetLength() + sizeof(char8_t) * 4);
				Elysium::Core::Template::Memory::MemCpy(&FileName[0], &_ErrorDirectory[0], DirectoryLength);
				FileName[DirectoryLength] = u8'\\';
				Elysium::Core::Template::Memory::MemCpy(&FileName[DirectoryLength + sizeof(char8_t)], &Index[0], Index.GetLength());
				Elysium::Core::Template::Memory::MemCpy(&FileName[DirectoryLength + sizeof(char8_t) + Index.GetLength()],
					FileExtension, sizeof(char8_t) * 4);

				FileStream TargetFileStream = FileStream(FileName, FileMode::CreateNew, FileAccess::Write);
			}

			// run the actual test
			FileSystemWatcher DirectoryWatcher = FileSystemWatcher(_ErrorDirectory, u8"*.*", FileSystemWatcher::DefaultNotifyFilters,
				false, 90);
			DirectoryWatcher.OnDeleted += Delegate<void, const FileSystemWatcher&, const FileSystemEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnDeleted>(*this);
			DirectoryWatcher.OnError += Delegate<void, const FileSystemWatcher&, const ErrorEventArgs&>::Bind<FileSystemWatcherTests, &FileSystemWatcherTests::FileSystemWatcher_OnError>(*this);
			DirectoryWatcher.BeginInit();

			// it's not even necessary to have multiple threads deleting files as long as the buffer is small enough
			for (Elysium::Core::Template::System::size i = 0; i < NumberOfFiles; ++i)
			{
				const Elysium::Core::Template::Text::String<char8_t> Index = Elysium::Core::Template::Text::Convert<char8_t>::ToString(i);

				Elysium::Core::Template::Text::String<char8_t> FileName = Elysium::Core::Template::Text::String<char8_t>(
					DirectoryLength + sizeof(char8_t) + Index.GetLength() + sizeof(char8_t) * 4);
				Elysium::Core::Template::Memory::MemCpy(&FileName[0], &_ErrorDirectory[0], DirectoryLength);
				FileName[DirectoryLength] = u8'\\';
				Elysium::Core::Template::Memory::MemCpy(&FileName[DirectoryLength + sizeof(char8_t)], &Index[0], Index.GetLength());
				Elysium::Core::Template::Memory::MemCpy(&FileName[DirectoryLength + sizeof(char8_t) + Index.GetLength()],
					FileExtension, sizeof(char8_t) * 4);

				File::Delete(&FileName[0]);
			}

			// give it a maximum of 30s for the error to occcure
			const bool WaitResult = _ErrorResetEvent.WaitOne(30000);
			Assert::IsTrue(WaitResult);

			// wait just a little bit longer to maybe catch a few more errors and get a (somewhat) complete picture.
			//Elysium::Core::Threading::Thread::Sleep(TimeSpan::FromSeconds(20));
		}

		void NonUTReuse()
		{
			FileSystemWatcher DirectoryWatcher = FileSystemWatcher(_BaseDirectory);
			for (int i = 0; i < 1000; ++i)
			{
				DirectoryWatcher.BeginInit();
				//DirectoryWatcher.EndInit();
			}
		}
	private:
		void CreateFileAndWait(const char8_t* FQPN, ManualResetEvent& Event, const bool ShouldTrigger)
		{
			FileStream TargetFileStream = FileStream(FQPN, FileMode::CreateNew, FileAccess::Write);
			const bool WaitResult = Event.WaitOne(1000);
			if(ShouldTrigger && !WaitResult)
			{
				Assert::Fail(L"File creation event was not triggered within given time limit.");
			}
			else if (!ShouldTrigger && WaitResult)
			{
				Assert::Fail(L"File creation event was triggered within given time limit and should have been filtered out.");
			}
			Event.Reset();
		}

		void ChangeFileAndWait(const char8_t* FQPN, ManualResetEvent& Event, const bool ShouldTrigger)
		{
			byte Buffer[1024] = { 0 };

			FileStream TargetFileStream = FileStream(FQPN, FileMode::Open, FileAccess::Write);
			TargetFileStream.Write(Buffer, 1024);
			TargetFileStream.Flush();
			const bool WaitResult = Event.WaitOne(1000);
			if (ShouldTrigger && !WaitResult)
			{
				Assert::Fail(L"File change event was not triggered within given time limit.");
			}
			else if (!ShouldTrigger && WaitResult)
			{
				Assert::Fail(L"File change event was triggered within given time limit and should have been filtered out.");
			}
			Event.Reset();
		}

		void RenameFileAndWait(const char8_t* FQPNInitial, const char8_t* FQPNChanged, ManualResetEvent& Event, const bool ShouldTrigger)
		{
			File::Move(FQPNInitial, FQPNChanged, false);
			const bool WaitResult0 = Event.WaitOne(1000);
			if (ShouldTrigger && !WaitResult0)
			{
				Assert::Fail(L"File rename event was not triggered within given time limit.");
			}
			else if (!ShouldTrigger && WaitResult0)
			{
				Assert::Fail(L"File rename event was triggered within given time limit and should have been filtered out.");
			}
			Event.Reset();

			File::Move(FQPNChanged, FQPNInitial, false);
			const bool WaitResult1 = Event.WaitOne(1000);
			if (ShouldTrigger && !WaitResult1)
			{
				Assert::Fail(L"File rename event was not triggered within given time limit.");
			}
			else if (!ShouldTrigger && WaitResult1)
			{
				Assert::Fail(L"File rename event was triggered within given time limit and should have been filtered out.");
			}
			Event.Reset();
		}

		void DeleteFileAndWait(const char8_t* FQPN, ManualResetEvent& Event, const bool ShouldTrigger)
		{
			File::Delete(FQPN);
			const bool WaitResult = Event.WaitOne(1000);
			if (ShouldTrigger && !WaitResult)
			{
				Assert::Fail(L"File deletion event was not triggered within given time limit.");
			}
			else if (!ShouldTrigger && WaitResult)
			{
				Assert::Fail(L"File deletion event was triggered within given time limit and should have been filtered out.");
			}
			Event.Reset();
		}

		void CreateFolderAndWait(const char8_t* FQPN, ManualResetEvent& Event, const bool ShouldTrigger)
		{
			bool CreateFolderResult = Elysium::Core::Template::IO::FileSystem::CreateFolder(FQPN);
			const bool WaitResult = Event.WaitOne(1000);
			if (ShouldTrigger && !WaitResult)
			{
				Assert::Fail(L"Folder creation event was not triggered within given time limit.");
			}
			else if (!ShouldTrigger && WaitResult)
			{
				Assert::Fail(L"Folder creation event was triggered within given time limit and should have been filtered out.");
			}
			Event.Reset();
		}

		void RenameFolderAndWait(const char8_t* FQPNInitial, const char8_t* FQPNChanged, ManualResetEvent& Event, const bool ShouldTrigger)
		{
			bool RenameFolderResult1 = Elysium::Core::Template::IO::FileSystem::RenameFolder(FQPNInitial, FQPNChanged);
			const bool WaitResult0 = Event.WaitOne(1000);
			if (ShouldTrigger && !WaitResult0)
			{
				Assert::Fail(L"File rename event was not triggered within given time limit.");
			}
			else if (!ShouldTrigger && WaitResult0)
			{
				Assert::Fail(L"File rename event was triggered within given time limit and should have been filtered out.");
			}
			Event.Reset();

			bool RenameFolderResult2 = Elysium::Core::Template::IO::FileSystem::RenameFolder(FQPNChanged, FQPNInitial);
			const bool WaitResult1 = Event.WaitOne(1000);
			if (ShouldTrigger && !WaitResult1)
			{
				Assert::Fail(L"File rename event was not triggered within given time limit.");
			}
			else if (!ShouldTrigger && WaitResult1)
			{
				Assert::Fail(L"File rename event was triggered within given time limit and should have been filtered out.");
			}
			Event.Reset();
		}

		void DeleteFolderAndWait(const char8_t* FQPN, ManualResetEvent& Event, const bool ShouldTrigger)
		{
			bool RemoveFolderResult = Elysium::Core::Template::IO::FileSystem::RemoveFolder(FQPN);
			const bool WaitResult = _DeletedResetEvent.WaitOne(1000);
			if (ShouldTrigger && !WaitResult)
			{
				Assert::Fail(L"Folder deletion event was not triggered within given time limit.");
			}
			else if (!ShouldTrigger && WaitResult)
			{
				Assert::Fail(L"Folder deletion event not triggered within given time limit and should have been filtered out.");
			}
			_DeletedResetEvent.Reset();
		}
	private:
		void FileSystemWatcher_OnCreated(const FileSystemWatcher& Watcher, const FileSystemEventArgs& EventArgs)
		{
			ThreadsafeLogger::WriteMessage("FileSystemWatcher_OnCreated\r\n");

			const WatcherChangeTypes ChangeType = EventArgs.GetChangeType();

			const Utf8String FullPath = EventArgs.GetFullPath();
			ThreadsafeLogger::WriteMessage("\tFullPath: ");
			ThreadsafeLogger::WriteMessage((char*)&FullPath[0]);
			ThreadsafeLogger::WriteMessage("\r\n");

			const Utf8String FileName = EventArgs.GetName();
			ThreadsafeLogger::WriteMessage("\tFileName: ");
			ThreadsafeLogger::WriteMessage((char*)&FileName[0]);
			ThreadsafeLogger::WriteMessage("\r\n");

			_CreatedResetEvent.Set();

			if (Elysium::Core::Template::Text::CharacterTraits<char8_t>::EqualsCaseInsensitive(&FullPath[0], FullPath.GetLength(),
				_OtherFilePath0, Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(_OtherFilePath0)))
			{
				_OtherCreatedResetEvent.Set();
			}
		}

		void FileSystemWatcher_OnChanged(const FileSystemWatcher& Watcher, const FileSystemEventArgs& EventArgs)
		{
			ThreadsafeLogger::WriteMessage("FileSystemWatcher_OnChanged\r\n");

			const WatcherChangeTypes ChangeType = EventArgs.GetChangeType();
			//const Utf8String ChangeTypeName = Enumeration<WatcherChangeTypes>::GetNamedValue<ChangeType>();

			const Utf8String FullPath = EventArgs.GetFullPath();
			ThreadsafeLogger::WriteMessage("\tFullPath: ");
			ThreadsafeLogger::WriteMessage((char*)&FullPath[0]);
			ThreadsafeLogger::WriteMessage("\r\n");

			const Utf8String FileName = EventArgs.GetName();
			ThreadsafeLogger::WriteMessage("\tFileName: ");
			ThreadsafeLogger::WriteMessage((char*)&FileName[0]);
			ThreadsafeLogger::WriteMessage("\r\n");
			
			_ChangedResetEvent.Set();
		}

		void FileSystemWatcher_OnDeleted(const FileSystemWatcher& Watcher, const FileSystemEventArgs& EventArgs)
		{
			ThreadsafeLogger::WriteMessage("FileSystemWatcher_OnDeleted\r\n");

			const WatcherChangeTypes ChangeType = EventArgs.GetChangeType();

			const Utf8String FullPath = EventArgs.GetFullPath();
			ThreadsafeLogger::WriteMessage("\tFullPath: ");
			ThreadsafeLogger::WriteMessage((char*)&FullPath[0]);
			ThreadsafeLogger::WriteMessage("\r\n");

			const Utf8String FileName = EventArgs.GetName();
			ThreadsafeLogger::WriteMessage("\tFileName: ");
			ThreadsafeLogger::WriteMessage((char*)&FileName[0]);
			ThreadsafeLogger::WriteMessage("\r\n");

			_DeletedResetEvent.Set();

			if (Elysium::Core::Template::Text::CharacterTraits<char8_t>::EqualsCaseInsensitive(&FullPath[0], FullPath.GetLength(),
				_OtherFilePath0, Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(_OtherFilePath0)))
			{
				_OtherDeletedResetEvent.Set();
			}
		}

		void FileSystemWatcher_OnRenamed(const FileSystemWatcher& Watcher, const RenamedEventArgs& EventArgs)
		{
			ThreadsafeLogger::WriteMessage("FileSystemWatcher_OnRenamed\r\n");

			const WatcherChangeTypes ChangeType = EventArgs.GetChangeType();

			const Utf8String FullPath = EventArgs.GetFullPath();
			ThreadsafeLogger::WriteMessage("\tFullPath: ");
			ThreadsafeLogger::WriteMessage((char*)&FullPath[0]);
			ThreadsafeLogger::WriteMessage("\r\n");

			const Utf8String FileName = EventArgs.GetName();
			ThreadsafeLogger::WriteMessage("\tFileName: ");
			ThreadsafeLogger::WriteMessage((char*)&FileName[0]);
			ThreadsafeLogger::WriteMessage("\r\n");
			/*
			const Utf8String OldFullPath = EventArgs.GetOldFullPath();
			ThreadsafeLogger::WriteMessage("\tOldFullPath: ");
			ThreadsafeLogger::WriteMessage((char*)&OldFullPath[0]);
			ThreadsafeLogger::WriteMessage("\r\n");
			*/
			const Utf8String OldFileName = EventArgs.GetOldName();
			ThreadsafeLogger::WriteMessage("\tOldName: ");
			ThreadsafeLogger::WriteMessage((char*)&OldFileName[0]);
			ThreadsafeLogger::WriteMessage("\r\n");
			
			_RenamedResetEvent.Set();
		}

		void FileSystemWatcher_OnError(const FileSystemWatcher& Watcher, const ErrorEventArgs& EventArgs)
		{
			ThreadsafeLogger::WriteMessage("FileSystemWatcher_OnError\r\n");

			const Elysium::Core::Template::Exceptions::IO::InternalBufferOverflowException& Exception = EventArgs.GetException();
			const Elysium::Core::Template::System::uint32_t ErrorCode = Exception.GetErrorCode();
			const Elysium::Core::Template::Text::String<char8_t>& Message = Exception.GetExceptionMessage();

			ThreadsafeLogger::WriteMessage("\tErrorCode: ");
			ThreadsafeLogger::WriteMessage((char*)&Elysium::Core::Template::Text::Convert<char>::ToString(ErrorCode)[0]);
			ThreadsafeLogger::WriteMessage("\r\n");
			ThreadsafeLogger::WriteMessage("\tMessage: ");
			ThreadsafeLogger::WriteMessage((char*)&Message[0]);
			ThreadsafeLogger::WriteMessage("\r\n");
			
			_ErrorResetEvent.Set();
		}
	private:
		inline static constexpr const char8_t* _BaseDirectory = u8"C:\\test";	// @ToDo: use Directory::CurrentDirectory()
		inline static constexpr const char8_t* _FilePath0 = u8"C:\\test\\file.txt";
		inline static constexpr const char8_t* _FilePath1 = u8"C:\\test\\file2.txt";

		inline static constexpr const char8_t* _DirectoryPath0 = u8"C:\\test\\subfolder";
		inline static constexpr const char8_t* _DirectoryPath1 = u8"C:\\test\\subfolder_renamed";

		inline static constexpr const char8_t* _OtherFilePath0 = u8"C:\\test\\file.log";

		inline static constexpr const char8_t* _ErrorDirectory = u8"C:\\test\\othererrors";	// @ToDo: use Directory::CurrentDirectory() + "\bufferoverflow"

		inline static constexpr const char8_t* _FilePathBufferOverflow = u8"C:\\test\\bufferoverflow.txt";
	private:
		// don't have access to FileSystemWatcher's internal IAsyncResult
		ManualResetEvent _ChangedResetEvent = ManualResetEvent(false);
		ManualResetEvent _CreatedResetEvent = ManualResetEvent(false);
		ManualResetEvent _DeletedResetEvent = ManualResetEvent(false);
		ManualResetEvent _ErrorResetEvent = ManualResetEvent(false);
		ManualResetEvent _RenamedResetEvent = ManualResetEvent(false);

		ManualResetEvent _OtherCreatedResetEvent = ManualResetEvent(false);
		ManualResetEvent _OtherDeletedResetEvent = ManualResetEvent(false);
	};
}