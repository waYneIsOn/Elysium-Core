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
		TEST_METHOD(GetFullPaths)
		{
			const bool SetCurrentDirectoryResult = Environment::CurrentDirectory(u8"C:\\test\\");
			Assert::IsTrue(SetCurrentDirectoryResult);

			const Utf8String CurrentDirectory = Environment::CurrentDirectory();
			AssertExtended::AreEqual(u8"C:\\test", CurrentDirectory);

			// --- GetPath(const T& Path) ---
			const Utf8String FolderOnly = u8"tmp";
			Utf8String FolderOnlyResult = Path::GetFullPath(FolderOnly);
			AssertExtended::AreEqual(u8"C:\\test\\tmp", FolderOnlyResult);

			const Utf8StringView FolderOnlyView = Utf8StringView(FolderOnly);
			Utf8String FolderOnlyViewResult = Path::GetFullPath(FolderOnlyView);
			AssertExtended::AreEqual(u8"C:\\test\\tmp", FolderOnlyViewResult);

			const Utf8String RelativeFolder = u8"../relative";
			Utf8String RelativeFolderResult = Path::GetFullPath(RelativeFolder);
			AssertExtended::AreEqual(u8"C:\\relative", RelativeFolderResult);

			const Utf8StringView RelativeFolderView = Utf8StringView(RelativeFolder);
			Utf8String RelativeFolderViewResult = Path::GetFullPath(RelativeFolderView);
			AssertExtended::AreEqual(u8"C:\\relative", RelativeFolderViewResult);

			const Utf8String FileOnly = u8"file.txt";
			Utf8String FileOnlyResult = Path::GetFullPath(FileOnly);
			AssertExtended::AreEqual(u8"C:\\test\\file.txt", FileOnlyResult);

			const Utf8StringView FileOnlyView = Utf8StringView(FileOnly);;
			Utf8String FileOnlyViewResult = Path::GetFullPath(FileOnlyView);
			AssertExtended::AreEqual(u8"C:\\test\\file.txt", FileOnlyViewResult);

			const Utf8String RelativeFile = u8"/relative/file.txt";
			Utf8String RelativeFileResult = Path::GetFullPath(RelativeFile);
			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", RelativeFileResult);

			const Utf8StringView RelativeFileView = Utf8StringView(RelativeFile);
			Utf8String RelativeFileViewResult = Path::GetFullPath(RelativeFileView);
			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", RelativeFileViewResult);

			Utf8String xy = u8"\\\\?\\";
			Utf8String xyr = Path::GetFullPath(xy);

			// --- GetPath(const T& Path, const T& BasePath) ---
			const Utf8String BasePath = u8"C:\\otherTest\\";
			//FolderOnlyResult = Path::GetFullPath(FolderOnly, BasePath);

			bool sdfsdf = false;
		}
	};
}
