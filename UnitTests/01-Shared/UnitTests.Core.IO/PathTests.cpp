#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/Environment.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/Path.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO
{
	TEST_CLASS(PathTests)
	{
	public:
		TEST_METHOD(EndsInDirectorySeperatorTests)
		{
			const Utf8String Empty = u8"";
			try
			{
				Path::EndsInDirectorySeperator(Empty);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			const Utf8StringView EmptyView = Utf8StringView(Empty);
			try
			{
				Path::EndsInDirectorySeperator(EmptyView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			const Utf8String Invalid = u8"C:\\<\\";
			try
			{
				Path::EndsInDirectorySeperator(Invalid);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			const Utf8StringView InvalidView = Utf8StringView(Invalid);
			try
			{
				Path::EndsInDirectorySeperator(InvalidView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			const Utf8String FolderOnly = u8"tmp\\";
			Assert::IsTrue(Path::EndsInDirectorySeperator(FolderOnly));

			const Utf8StringView FolderOnlyView = Utf8StringView(FolderOnly);
			Assert::IsTrue(Path::EndsInDirectorySeperator(FolderOnlyView));

			const Utf8String RelativeFolder = u8"../relative";
			Assert::IsFalse(Path::EndsInDirectorySeperator(RelativeFolder));

			const Utf8StringView RelativeFolderView = Utf8StringView(RelativeFolder);
			Assert::IsFalse(Path::EndsInDirectorySeperator(RelativeFolderView));

			const Utf8String FileOnly = u8"file.txt";
			Assert::IsFalse(Path::EndsInDirectorySeperator(FileOnly));

			const Utf8StringView FileOnlyView = Utf8StringView(FileOnly);
			Assert::IsFalse(Path::EndsInDirectorySeperator(FileOnlyView));

			const Utf8String RelativeFile = u8"/relative/file.txt";
			Assert::IsFalse(Path::EndsInDirectorySeperator(RelativeFile));

			const Utf8StringView RelativeFileView = Utf8StringView(RelativeFile);
			Assert::IsFalse(Path::EndsInDirectorySeperator(RelativeFileView));

			const Utf8String UriFile = u8"file://localhost/somefolder/file.txt";
			Assert::IsFalse(Path::EndsInDirectorySeperator(UriFile));

			const Utf8StringView UriFileView = Utf8StringView(UriFile);
			Assert::IsFalse(Path::EndsInDirectorySeperator(UriFileView));

			const Utf8String DosFile = u8"\\\\?\\C:\\Test\\file.txt";
			Assert::IsFalse(Path::EndsInDirectorySeperator(DosFile));

			const Utf8String DosPath = u8"\\\\.\\C:\\";
			Assert::IsTrue(Path::EndsInDirectorySeperator(DosPath));
		}

		TEST_METHOD(GetFullPathTests)
		{
			const bool SetCurrentDirectoryResult = Environment::CurrentDirectory(u8"C:\\test\\");
			Assert::IsTrue(SetCurrentDirectoryResult);

			const Utf8String CurrentDirectory = Environment::CurrentDirectory();
			AssertExtended::AreEqual(u8"C:\\test", CurrentDirectory);

			// --- GetPath(const T& Path) ---
			const Utf8String Empty = u8"";
			try
			{
				Utf8String EmptyResult = Path::GetFullPath(Empty);
				Assert::Fail();
			}
			catch(ArgumentException&)
			{ }

			const Utf8StringView EmptyView = Utf8StringView(Empty);
			try
			{
				Utf8String EmptyViewResult = Path::GetFullPath(EmptyView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			const Utf8String Invalid = u8"C:\\<\\";
			try
			{
				Utf8String InvalidResult = Path::GetFullPath(Invalid);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			const Utf8StringView InvalidView = Utf8StringView(Invalid);
			try
			{
				Utf8String InvalidViewResult = Path::GetFullPath(InvalidView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			const Utf8String FolderOnly = u8"tmp\\";
			Utf8String FolderOnlyResult = Path::GetFullPath(FolderOnly);
			AssertExtended::AreEqual(u8"C:\\test\\tmp\\", FolderOnlyResult);

			const Utf8StringView FolderOnlyView = Utf8StringView(FolderOnly);
			Utf8String FolderOnlyViewResult = Path::GetFullPath(FolderOnlyView);
			AssertExtended::AreEqual(u8"C:\\test\\tmp\\", FolderOnlyViewResult);

			const Utf8String RelativeFolder = u8"../relative";
			Utf8String RelativeFolderResult = Path::GetFullPath(RelativeFolder);
			AssertExtended::AreEqual(u8"C:\\relative", RelativeFolderResult);

			const Utf8StringView RelativeFolderView = Utf8StringView(RelativeFolder);
			Utf8String RelativeFolderViewResult = Path::GetFullPath(RelativeFolderView);
			AssertExtended::AreEqual(u8"C:\\relative", RelativeFolderViewResult);

			const Utf8String FileOnly = u8"file.txt";
			Utf8String FileOnlyResult = Path::GetFullPath(FileOnly);
			AssertExtended::AreEqual(u8"C:\\test\\file.txt", FileOnlyResult);

			const Utf8StringView FileOnlyView = Utf8StringView(FileOnly);
			Utf8String FileOnlyViewResult = Path::GetFullPath(FileOnlyView);
			AssertExtended::AreEqual(u8"C:\\test\\file.txt", FileOnlyViewResult);

			const Utf8String RelativeFile = u8"/relative/file.txt";
			Utf8String RelativeFileResult = Path::GetFullPath(RelativeFile);
			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", RelativeFileResult);

			const Utf8StringView RelativeFileView = Utf8StringView(RelativeFile);
			Utf8String RelativeFileViewResult = Path::GetFullPath(RelativeFileView);
			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", RelativeFileViewResult);

			const Utf8String UriFile = u8"file://localhost/somefolder/file.txt";
			Utf8String UriFileResult = Path::GetFullPath(UriFile);
			AssertExtended::AreEqual(u8"C:\\test\\file:\\localhost\\somefolder\\file.txt", UriFileResult);

			const Utf8StringView UriFileView = Utf8StringView(UriFile);
			Utf8String UriFileViewResult = Path::GetFullPath(UriFileView);
			AssertExtended::AreEqual(u8"C:\\test\\file:\\localhost\\somefolder\\file.txt", UriFileViewResult);
			
			const Utf8String DosFile = u8"\\\\?\\C:\\Test\\file.txt";
			Utf8String DosFileResult = Path::GetFullPath(DosFile);
			AssertExtended::AreEqual(DosFile, DosFileResult);
			
			const Utf8String DosPath = u8"\\\\.\\C:\\";
			Utf8String DosPathResult = Path::GetFullPath(DosPath);
			AssertExtended::AreEqual(DosPath, DosPathResult);

			// --- GetPath(const T& Path, const T& BasePath) ---
			const Utf8String BasePath = u8"C:\\otherTest\\";
			//FolderOnlyResult = Path::GetFullPath(FolderOnly, BasePath);

			bool sdfsdf = false;
		}
	};
}
