#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#ifndef ELYSIUM_CORE_Byte
#include "../../../Libraries/01-Shared/Elysium.Core/Byte.hpp"
#endif

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{
	TEST_CLASS(ByteTest)
	{
	public:
		TEST_METHOD(Size)
		{
			Assert::AreEqual((size_t)1, sizeof(Elysium::Core::byte));
			Assert::AreEqual((size_t)1, sizeof(Elysium::Core::sbyte));
		}
	};
}