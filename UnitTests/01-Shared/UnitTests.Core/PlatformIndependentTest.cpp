#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PlatformIndependentTest)
	{
	public:
		TEST_METHOD(TypeComparison)
		{
			Assert::AreEqual(sizeof(int), sizeof(long));
		}
	};
}
