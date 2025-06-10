#include "CppUnitTest.h"

#include "CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/Environment.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/RunTimeTypeInformation/Enumeration.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Text;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(EnvironmentTests)
	{
	public:

		TEST_METHOD(AssertableRuntimeValues)
		{
			const OperatingSystem OS = Environment::OSVersion();
			const PlatformID OSPlatform = OS.GetPlatform();
			const Version& OSVersion = OS.GetVersion();

			//Elysium::Core::Template::RunTimeTypeInformation::Enumeration<PlatformID>::GetNamedValue<OS.GetPlatform()>();

			Logger::WriteMessage("Current OS Information:\r\n\r\n");
			Logger::WriteMessage("Platform: ");
			Logger::WriteMessage("...");
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage("Version String: ");
			Logger::WriteMessage("...");
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage("Version Information:\r\n");
			Logger::WriteMessage("\tMajor: ");
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(OSVersion.GetMajor())[0]);
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage("\tMinor: ");
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(OSVersion.GetMinor())[0]);
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage("Service Pack: ");
			Logger::WriteMessage("...");
			Logger::WriteMessage("\r\n");

			const Elysium::Core::Utf8String SystemDirectory = Environment::SystemDirectory();
			Logger::WriteMessage("SystemDirectory: ");
			Logger::WriteMessage((char*)&SystemDirectory[0]);
			Logger::WriteMessage("\r\n");

			const Elysium::Core::Utf8String& NewLine = Environment::NewLine;
			Logger::WriteMessage("NewLine: ");
			Logger::WriteMessage((char*)&NewLine[0]);

#if defined ELYSIUM_CORE_OS_WINDOWS
			Assert::IsTrue(OS.IsWindows());
			AssertExtended::AreEqual(u8"\r\n", NewLine);
			AssertExtended::AreEqual(u8"C:\\WINDOWS\\system32", SystemDirectory);
#else
#error "unsupported os"
#endif
		}

		TEST_METHOD(OtherRuntimeValues)
		{
			const OperatingSystem OS = Environment::OSVersion();
			const Elysium::Core::Utf8String MachineName = Environment::MachineName();
			Logger::WriteMessage((char*)&MachineName[0]);
			const Elysium::Core::uint32_t ProcessorCount = Environment::ProcessorCount();
			const Elysium::Core::Utf8String UserName = Environment::UserName();
		}

		TEST_METHOD(CurrentDirectoryTests)
		{
			const Elysium::Core::Utf8String InitialDirectory = Environment::CurrentDirectory();
			Assert::IsTrue(InitialDirectory.GetLength() > 0);

			try
			{
				Logger::WriteMessage("setting simple path\r\n");

				const Elysium::Core::Utf8String DirectoryPathSimple = u8"C:\\Windows";
				Environment::CurrentDirectory(&DirectoryPathSimple[0], DirectoryPathSimple.GetLength());

				const Elysium::Core::Utf8String SetDirectorySimple = Environment::CurrentDirectory();
				AssertExtended::AreEqual(DirectoryPathSimple, SetDirectorySimple);
			}
			catch (const SystemException& ex)
			{
				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Logger::WriteMessage("\r\nErrorCode:");
				Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(ex.GetErrorCode())[0]);
				Logger::WriteMessage("\r\n");

				Environment::CurrentDirectory(&InitialDirectory[0], InitialDirectory.GetLength());
				Assert::Fail();
			}
			/*
			try
			{
				Logger::WriteMessage("setting long path\r\n");

				// @Info: this only works if "long path support" is enabled:
				//		https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file#maximum-path-length-limitation
				//		https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=registry
				//		[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\FileSystem]
				//		"LongPathsEnabled" = dword:00000001
				const Elysium::Core::Utf8String DirectoryPathLong = u8"C:\\22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222";
				Environment::CurrentDirectory(&DirectoryPathLong[0], DirectoryPathLong.GetLength());

				const Elysium::Core::Utf8String SetDirectoryLong = Environment::CurrentDirectory();
				AssertExtended::AreEqual(DirectoryPathLong, SetDirectoryLong);

			}
			catch (const SystemException& ex)
			{
				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Logger::WriteMessage("\r\nErrorCode:");
				Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(ex.GetErrorCode())[0]);
				Logger::WriteMessage("\r\n");

				Environment::CurrentDirectory(&InitialDirectory[0], InitialDirectory.GetLength());
				Assert::Fail();
			}
			*/
			try
			{
				Logger::WriteMessage("setting special char path\r\n");
				const Elysium::Core::Utf8String DirectoryPathSpecialChars = u8"C:\\testüüüüöööööö";
				Environment::CurrentDirectory(&DirectoryPathSpecialChars[0], DirectoryPathSpecialChars.GetLength());

				const Elysium::Core::Utf8String SetDirectorySpecialChars = Environment::CurrentDirectory();
				AssertExtended::AreEqual(DirectoryPathSpecialChars, SetDirectorySpecialChars);
			}
			catch (const SystemException& ex)
			{
				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Logger::WriteMessage("\r\nErrorCode:");
				Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(ex.GetErrorCode())[0]);
				Logger::WriteMessage("\r\n");

				Environment::CurrentDirectory(&InitialDirectory[0], InitialDirectory.GetLength());
				Assert::Fail();
			}

			try
			{
				Logger::WriteMessage("resetting initial path\r\n");
				Environment::CurrentDirectory(&InitialDirectory[0], InitialDirectory.GetLength());

				const Elysium::Core::Utf8String SetDirectoryReset = Environment::CurrentDirectory();
				AssertExtended::AreEqual(InitialDirectory, SetDirectoryReset);
			}
			catch (const SystemException& ex)
			{
				Logger::WriteMessage((char*)&ex.GetExceptionMessage()[0]);
				Logger::WriteMessage("\r\nErrorCode:");
				Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(ex.GetErrorCode())[0]);
				Logger::WriteMessage("\r\n");

				Environment::CurrentDirectory(&InitialDirectory[0], InitialDirectory.GetLength());
				Assert::Fail();
			}
		}
	};
}
