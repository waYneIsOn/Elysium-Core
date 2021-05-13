#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Decimal.hpp"

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core
{		
	TEST_CLASS(DecimalTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			Elysium::Core::Decimal Float128 = 3.14154564564564567458757686574867867586758675867876_M;
			AssertExtended::AreEqual(3LL, Float128.GetHighPart());
			AssertExtended::AreEqual(14154ULL, Float128.GetLowPart());
		}
	};
}