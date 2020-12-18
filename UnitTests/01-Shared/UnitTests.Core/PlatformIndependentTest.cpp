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
			Assert::AreEqual(static_cast<size_t>(1), sizeof(char8_t));
			Assert::AreEqual(static_cast<size_t>(2), sizeof(char16_t));
			Assert::AreEqual(static_cast<size_t>(4), sizeof(char32_t));
		}
	};
}
