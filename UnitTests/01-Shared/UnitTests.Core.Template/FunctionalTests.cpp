#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Functional.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Functional;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Functional
{
	TEST_CLASS(FunctionalTests)
	{
	public:
		TEST_METHOD(SwapBytes)
		{
			byte Left = 0;
			byte Right = 255;

			Swap(Left, Right);

			Assert::AreEqual(static_cast<byte>(255), Left);
			Assert::AreEqual(static_cast<byte>(0), Right);
		}

		TEST_METHOD(SwapInteger)
		{
			int32_t Left = -1;
			int32_t Right = 45356;

			Swap(Left, Right);

			Assert::AreEqual(-1, Right);
			Assert::AreEqual(45356, Left);
		}
	};
}
