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

			try
			{
				Path::EndsInDirectorySeperator(_Invalid);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			try
			{
				Path::EndsInDirectorySeperator(_InvalidView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			Assert::IsTrue(Path::EndsInDirectorySeperator(_FolderOnly));
			Assert::IsTrue(Path::EndsInDirectorySeperator(_FolderOnlyView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_FolderOnlyAlternative));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_FolderOnlyAlternativeView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFolder));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFolderView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeAlternativeFolder));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeAlternativeFolderView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_FileOnly));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_FileOnlyView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFile));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFileView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFileAlternative));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFileAlternativeView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFileMixed));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFileMixedView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFileMixedAlternative));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_RelativeFileMixedAlternativeView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_FullFile));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_FullFileView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_FullFileAlternative));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_FullFileAlternativeView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_UriFile));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_UriFileView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_UriFileAlternative));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_UriFileAlternativeView));

			Assert::IsTrue(Path::EndsInDirectorySeperator(_FullPath));
			Assert::IsTrue(Path::EndsInDirectorySeperator(_FullPathView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_FullPathAlternative));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_FullPathAlternative));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_DosFile));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_DosFileView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_DosFileAlternative));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_DosFileAlternativeView));

			Assert::IsTrue(Path::EndsInDirectorySeperator(_DosPath));
			Assert::IsTrue(Path::EndsInDirectorySeperator(_DosPathView));

			Assert::IsTrue(Path::EndsInDirectorySeperator(_UncPath));
			Assert::IsTrue(Path::EndsInDirectorySeperator(_UncPathView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_UncFile));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_UncFileView));

			Assert::IsFalse(Path::EndsInDirectorySeperator(_UncFileMixed));
			Assert::IsFalse(Path::EndsInDirectorySeperator(_UncFileMixedView));
		}

		TEST_METHOD(GetExtensionTests)
		{
			try
			{
				Utf8String EmptyResult = Path::GetExtension(Utf8String());
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			try
			{
				Utf8StringView EmptyViewResult = Path::GetExtension(_EmptyView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			try
			{
				Utf8String InvalidResult = Path::GetExtension(_Invalid);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			try
			{
				Utf8StringView InvalidViewResult = Path::GetExtension(_InvalidView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetExtension(_FolderOnly)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetExtension(_FolderOnlyView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetExtension(_FolderOnlyAlternative)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetExtension(_FolderOnlyAlternativeView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetExtension(_RelativeFolder)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetExtension(_RelativeFolderView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetExtension(_RelativeAlternativeFolder)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetExtension(_RelativeAlternativeFolderView)));

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_FileOnly));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_FileOnlyView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_RelativeFile));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_RelativeFileView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_RelativeFileAlternative));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_RelativeFileAlternativeView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_RelativeFileMixed));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_RelativeFileMixedView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_RelativeFileMixedAlternative));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_RelativeFileMixedAlternativeView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_FullFile));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_FullFileView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_FullFileAlternative));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_FullFileAlternativeView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_UriFile));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_UriFileView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_UriFileAlternative));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_UriFileAlternativeView).ToString());

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetExtension(_FullPath)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetExtension(_FullPathView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetExtension(_FullPathAlternative)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetExtension(_FullPathAlternativeView)));

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_DosFile));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_DosFileView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_DosFileAlternative));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_DosFileAlternativeView).ToString());

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetExtension(_DosPath)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetExtension(_DosPathView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetExtension(_UncPath)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetExtension(_UncPathView)));

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_UncFile));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_UncFileView).ToString());

			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_UncFileMixed));
			AssertExtended::AreEqual(u8".txt", Path::GetExtension(_UncFileMixedView).ToString());
		}

		TEST_METHOD(GetDirectoryNameTests)
		{
			Assert::Fail();
		}

		TEST_METHOD(GetFileNameTests)
		{
			try
			{
				Utf8String EmptyResult = Path::GetFileName(Utf8String());
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			try
			{
				Utf8StringView EmptyViewResult = Path::GetFileName(_EmptyView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			try
			{
				Utf8String InvalidResult = Path::GetFileName(_Invalid);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			try
			{
				Utf8StringView InvalidViewResult = Path::GetFileName(_InvalidView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_FolderOnly)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_FolderOnlyView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_FolderOnlyAlternative)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_FolderOnlyAlternativeView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_RelativeFolder)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_RelativeFolderView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_RelativeAlternativeFolder)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_RelativeAlternativeFolderView)));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_FileOnly));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_FileOnlyView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_RelativeFile));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_RelativeFileView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_RelativeFileAlternative));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_RelativeFileAlternativeView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_RelativeFileMixed));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_RelativeFileMixedView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_RelativeFileMixedAlternative));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_RelativeFileMixedAlternativeView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_FullFile));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_FullFileView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_FullFileAlternative));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_FullFileAlternativeView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_UriFile));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_UriFileView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_UriFileAlternative));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_UriFileAlternativeView));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_FullPath)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_FullPathView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_FullPathAlternative)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_FullPathAlternativeView)));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_DosFile));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_DosFileView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_DosFileAlternative));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_DosFileAlternativeView));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_DosPath)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_DosPathView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_UncPath)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_UncPathView)));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_UncFile));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_UncFileView));

			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_UncFileMixed));
			AssertExtended::AreEqual(u8"file.txt", Path::GetFileName(_UncFileMixedView));
		}

		TEST_METHOD(GetFullPathTests)
		{
			const Elysium::Core::Utf8String Directory = u8"C:\\test\\";
			Environment::CurrentDirectory(&Directory[0], Directory.GetLength());

			const Utf8String CurrentDirectory = Environment::CurrentDirectory();
			AssertExtended::AreEqual(Directory, CurrentDirectory);

			// --- GetPath(const T& Path) ---
			try
			{
				Utf8String EmptyResult = Path::GetFullPath(Utf8String());
				Assert::Fail();
			}
			catch(ArgumentException&)
			{ }

			try
			{
				Utf8String EmptyViewResult = Path::GetFullPath(_EmptyView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			try
			{
				Utf8String InvalidResult = Path::GetFullPath(_Invalid);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			try
			{
				Utf8String InvalidViewResult = Path::GetFullPath(_InvalidView);
				Assert::Fail();
			}
			catch (ArgumentException&)
			{ }

			AssertExtended::AreEqual(u8"C:\\test\\tmp\\", Path::GetFullPath(_FolderOnly));
			AssertExtended::AreEqual(u8"C:\\test\\tmp\\", Path::GetFullPath(_FolderOnlyView));

			AssertExtended::AreEqual(u8"C:\\test\\tmp\\", Path::GetFullPath(_FolderOnlyAlternative));
			AssertExtended::AreEqual(u8"C:\\test\\tmp\\", Path::GetFullPath(_FolderOnlyAlternativeView));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_RelativeFolder)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_RelativeFolderView)));

			Assert::IsTrue(Utf8String::CharacterTraits::IsEmpty(&Path::GetFileName(_RelativeAlternativeFolder)[0]));
			Assert::IsTrue(Utf8StringView::IsNullOrEmtpy(Path::GetFileName(_RelativeAlternativeFolderView)));

			AssertExtended::AreEqual(u8"C:\\test\\file.txt", Path::GetFullPath(_FileOnly));
			AssertExtended::AreEqual(u8"C:\\test\\file.txt", Path::GetFullPath(_FileOnlyView));

			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", Path::GetFullPath(_RelativeFile));
			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", Path::GetFullPath(_RelativeFileView));

			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", Path::GetFullPath(_RelativeFileAlternative));
			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", Path::GetFullPath(_RelativeFileAlternativeView));

			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", Path::GetFullPath(_RelativeFileMixed));
			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", Path::GetFullPath(_RelativeFileMixedView));

			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", Path::GetFullPath(_RelativeFileMixedAlternative));
			AssertExtended::AreEqual(u8"C:\\relative\\file.txt", Path::GetFullPath(_RelativeFileMixedAlternativeView));

			AssertExtended::AreEqual(u8"C:\\some.path\\file.txt", Path::GetFullPath(_FullFile));
			AssertExtended::AreEqual(u8"C:\\some.path\\file.txt", Path::GetFullPath(_FullFileView));

			AssertExtended::AreEqual(u8"C:\\some.path\\file.txt", Path::GetFullPath(_FullFileAlternative));
			AssertExtended::AreEqual(u8"C:\\some.path\\file.txt", Path::GetFullPath(_FullFileAlternativeView));

			AssertExtended::AreEqual(u8"C:\\test\\file:\\localhost\\somefolder\\file.txt", Path::GetFullPath(_UriFile));
			AssertExtended::AreEqual(u8"C:\\test\\file:\\localhost\\somefolder\\file.txt", Path::GetFullPath(_UriFileView));

			AssertExtended::AreEqual(u8"C:\\test\\file:\\localhost\\somefolder\\file.txt", Path::GetFullPath(_UriFileAlternative));
			AssertExtended::AreEqual(u8"C:\\test\\file:\\localhost\\somefolder\\file.txt", Path::GetFullPath(_UriFileAlternativeView));

			AssertExtended::AreEqual(u8"C:\\some.path\\", Path::GetFullPath(_FullPath));
			AssertExtended::AreEqual(u8"C:\\some.path\\", Path::GetFullPath(_FullPathView));

			AssertExtended::AreEqual(u8"C:\\some.path\\", Path::GetFullPath(_FullPathAlternative));
			AssertExtended::AreEqual(u8"C:\\some.path\\", Path::GetFullPath(_FullPathAlternativeView));

			AssertExtended::AreEqual(u8"\\\\?\\C:\\Test\\file.txt", Path::GetFullPath(_DosFile));
			AssertExtended::AreEqual(u8"\\\\?\\C:\\Test\\file.txt", Path::GetFullPath(_DosFileView));

			AssertExtended::AreEqual(u8"\\\\?\\C:\\Test\\file.txt", Path::GetFullPath(_DosFileAlternative));
			AssertExtended::AreEqual(u8"\\\\?\\C:\\Test\\file.txt", Path::GetFullPath(_DosFileAlternativeView));

			AssertExtended::AreEqual(u8"\\\\.\\C:\\", Path::GetFullPath(_DosPath));
			AssertExtended::AreEqual(u8"\\\\.\\C:\\", Path::GetFullPath(_DosPathView));

			AssertExtended::AreEqual(u8"\\\\server\\some.path\\", Path::GetFullPath(_UncPath));
			AssertExtended::AreEqual(u8"\\\\server\\some.path\\", Path::GetFullPath(_UncPathView));

			AssertExtended::AreEqual(u8"\\\\server\\some.path\\file.txt", Path::GetFullPath(_UncFile));
			AssertExtended::AreEqual(u8"\\\\server\\some.path\\file.txt", Path::GetFullPath(_UncFileView));

			AssertExtended::AreEqual(u8"\\\\server\\some.path\\file.txt", Path::GetFullPath(_UncFileMixed));
			AssertExtended::AreEqual(u8"\\\\server\\some.path\\file.txt", Path::GetFullPath(_UncFileMixedView));






			const Utf8String MultiplePaths = u8"tmp;../relative;\\\\.\\C:\\;\\\\server\\some.path\\file.txt";
			Utf8String MultiplePathsResult = Path::GetFullPath(MultiplePaths);
			AssertExtended::AreEqual(u8"C:\\test\\tmp;..\\relative;\\C:\\;\\server\\some.path\\file.txt", MultiplePathsResult);

			// --- GetPath(const T& Path, const T& BasePath) ---
			const Utf8String BasePath = u8"C:\\otherTest\\";
			//FolderOnlyResult = Path::GetFullPath(FolderOnly, BasePath);

			bool sdfsdf = false;
		}
	private:
		inline static const Utf8StringView _EmptyView = Utf8StringView();

		inline static const Utf8String _Invalid = u8"C:\\</";
		inline static const Utf8StringView _InvalidView = Utf8StringView(_Invalid);

		inline static const Utf8String _FolderOnly = u8"tmp\\";
		inline static const Utf8StringView _FolderOnlyView = Utf8StringView(_FolderOnly);

		inline static const Utf8String _FolderOnlyAlternative = u8"tmp/";
		inline static const Utf8StringView _FolderOnlyAlternativeView = Utf8StringView(_FolderOnlyAlternative);

		inline static const Utf8String _RelativeFolder = u8"..\\relative";
		inline static const Utf8StringView _RelativeFolderView = Utf8StringView(_RelativeFolder);

		inline static const Utf8String _RelativeAlternativeFolder = u8"../relative";
		inline static const Utf8StringView _RelativeAlternativeFolderView = Utf8StringView(_RelativeAlternativeFolder);

		inline static const Utf8String _FileOnly = u8"file.txt";
		inline static const Utf8StringView _FileOnlyView = Utf8StringView(_FileOnly);

		inline static const Utf8String _RelativeFile = u8"\\relative\\file.txt";
		inline static const Utf8StringView _RelativeFileView = Utf8StringView(_RelativeFile);
		
		inline static const Utf8String _RelativeFileAlternative = u8"/relative/file.txt";
		inline static const Utf8StringView _RelativeFileAlternativeView = Utf8StringView(_RelativeFileAlternative);

		inline static const Utf8String _RelativeFileMixed = u8"\\relative/file.txt";
		inline static const Utf8StringView _RelativeFileMixedView = Utf8StringView(_RelativeFileMixed);

		inline static const Utf8String _RelativeFileMixedAlternative = u8"/relative\\file.txt";
		inline static const Utf8StringView _RelativeFileMixedAlternativeView = Utf8StringView(_RelativeFileMixedAlternative);
		
		inline static const Utf8String _FullFile = u8"C:\\some.path\\file.txt";
		inline static const Utf8StringView _FullFileView = Utf8StringView(_FullFile);

		inline static const Utf8String _FullFileAlternative = u8"C:\\some.path\\file.txt";
		inline static const Utf8StringView _FullFileAlternativeView = Utf8StringView(_FullFileAlternative);

		inline static const Utf8String _UriFile = u8"file:\\\\localhost\\somefolder\\file.txt";
		inline static const Utf8StringView _UriFileView = Utf8StringView(_UriFile);

		inline static const Utf8String _UriFileAlternative = u8"file://localhost/somefolder/file.txt";
		inline static const Utf8StringView _UriFileAlternativeView = Utf8StringView(_UriFileAlternative);

		inline static const Utf8String _FullPath = u8"C:\\some.path\\";
		inline static const Utf8StringView _FullPathView = Utf8StringView(_FullPath);

		inline static const Utf8String _FullPathAlternative = u8"C:/some.path/";
		inline static const Utf8StringView _FullPathAlternativeView = Utf8StringView(_FullPathAlternative);

		inline static const Utf8String _DosFile = u8"\\\\?\\C:\\Test\\file.txt";
		inline static const Utf8StringView _DosFileView = Utf8StringView(_DosFile);

		inline static const Utf8String _DosFileAlternative = u8"//?/C:/Test/file.txt";
		inline static const Utf8StringView _DosFileAlternativeView = Utf8StringView(_DosFileAlternative);
		
		inline static const Utf8String _DosPath = u8"\\\\.\\C:\\";
		inline static const Utf8StringView _DosPathView = Utf8StringView(_DosPath);

		inline static const Utf8String _UncPath = u8"\\\\server\\some.path\\";
		inline static const Utf8StringView _UncPathView = Utf8StringView(_UncPath);

		inline static const Utf8String _UncFile = u8"\\\\server\\some.path\\file.txt";
		inline static const Utf8StringView _UncFileView = Utf8StringView(_UncFile);

		inline static const Utf8String _UncFileMixed = u8"\\\\server\\some.path/file.txt";
		inline static const Utf8StringView _UncFileMixedView = Utf8StringView(_UncFileMixed);
	};
}
