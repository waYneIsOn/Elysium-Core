#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

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
		{	// this test will obviously only work correctly in my scenario.
			// ToDo: think about a better solution.
			Utf8String FolderOnly = u8"tmp";
			Utf8String FolderOnlyResult = Path::GetFullPath(FolderOnly);
			AssertExtended::AreEqual(u8"D:\\GitHub\\Repos\\bin\\Debug\\x64\\tmp", FolderOnlyResult);

			Utf8StringView FolderOnlyView = Utf8StringView(FolderOnly);
			Utf8String FolderOnlyViewResult = Path::GetFullPath(FolderOnlyView);
			AssertExtended::AreEqual(u8"D:\\GitHub\\Repos\\bin\\Debug\\x64\\tmp", FolderOnlyViewResult);

			Utf8String RelativeFolder = u8"../relative";
			Utf8String RelativeFolderResult = Path::GetFullPath(RelativeFolder);
			AssertExtended::AreEqual(u8"D:\\GitHub\\Repos\\bin\\Debug\\relative", RelativeFolderResult);

			Utf8StringView RelativeFolderView = Utf8StringView(RelativeFolder);
			Utf8String RelativeFolderViewResult = Path::GetFullPath(RelativeFolderView);
			AssertExtended::AreEqual(u8"D:\\GitHub\\Repos\\bin\\Debug\\relative", RelativeFolderViewResult);

			Utf8String FileOnly = u8"file.txt";
			Utf8String FileOnlyResult = Path::GetFullPath(FileOnly);
			AssertExtended::AreEqual(u8"D:\\GitHub\\Repos\\bin\\Debug\\x64\\file.txt", FileOnlyResult);

			Utf8StringView FileOnlyView = Utf8StringView(FileOnly);;
			Utf8String FileOnlyViewResult = Path::GetFullPath(FileOnlyView);
			AssertExtended::AreEqual(u8"D:\\GitHub\\Repos\\bin\\Debug\\x64\\file.txt", FileOnlyViewResult);

			Utf8String RelativeFile = u8"./relative/file.txt";
			Utf8String RelativeFileResult = Path::GetFullPath(RelativeFile);
			AssertExtended::AreEqual(u8"D:\\GitHub\\Repos\\bin\\Debug\\x64\\relative\\file.txt", RelativeFileResult);

			Utf8StringView RelativeFileView = Utf8StringView(RelativeFile);
			Utf8String RelativeFileViewResult = Path::GetFullPath(RelativeFileView);
			AssertExtended::AreEqual(u8"D:\\GitHub\\Repos\\bin\\Debug\\x64\\relative\\file.txt", RelativeFileViewResult);

			Utf8String xy = u8"C:\\?\\";
			Utf8String xyr = Path::GetFullPath(xy);

			// -------------------------------------------------------------------
			Utf8String BasePath = u8"C:/";

			bool sdfsdf = false;
		}
	};
}
