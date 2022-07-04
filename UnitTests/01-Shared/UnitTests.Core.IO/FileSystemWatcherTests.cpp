#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO.FileSystem.Watcher/FileSystemWatcher.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::IO;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::IO
{
	TEST_CLASS(FileSystemWatcherTests)
	{
	public:
		TEST_METHOD(Bla)
		{
			FileSystemWatcher Watcher = FileSystemWatcher(u8"C:\\", u8"*.*");
			Watcher.BeginInit();
		}
	};
}