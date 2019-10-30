#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../../../Libraries/01-Shared/Elysium.Core/Environment.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;

namespace UnitTestsCore
{
	TEST_CLASS(Core_Environment)
	{
	public:
		TEST_METHOD(Properties)
		{
			String MachineName = Environment::MachineName();
			OperatingSystem OS = Environment::OSVersion();
			int ProcessorCount = Environment::ProcessorCount();
			String UserName = Environment::UserName();
			String SystemDirectory = Environment::SystemDirectory();
		}
	};
}
