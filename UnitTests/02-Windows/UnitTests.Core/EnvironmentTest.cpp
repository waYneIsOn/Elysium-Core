#include "CppUnitTest.h"

#include "CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/Environment.hpp"

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
			const String& NewLine = Environment::NewLine();
			const String SystemDirectory = Environment::SystemDirectory();

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
			const String MachineName = Environment::MachineName();
			const Elysium::Core::uint32_t ProcessorCount = Environment::ProcessorCount();
			const String UserName = Environment::UserName();
		}
	};
}
