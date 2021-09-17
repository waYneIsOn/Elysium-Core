#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Utility.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template
{
	TEST_CLASS(UtilityTest)
	{
	public:
		TEST_METHOD(TestSwap)
		{
			byte Left = 0;
			byte Right = 255;

			Utility::Swap(Left, Right);

			Assert::AreEqual(static_cast<byte>(255), Left);
			Assert::AreEqual(static_cast<byte>(0), Right);
		}
	};
}
