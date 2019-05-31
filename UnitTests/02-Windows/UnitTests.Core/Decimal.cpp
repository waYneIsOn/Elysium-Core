#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#ifndef ELYSIUM_CORE_DECIMAL
#include "../../../Libraries/01-Shared/Elysium.Core/Decimal.hpp"
#endif

using namespace Elysium::Core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsCore
{		
	TEST_CLASS(Core_Decimal)
	{
	public:
		TEST_METHOD(Constructors)
		{
			Elysium::Core::Decimal FromFloat(3.14154564564564567458757686574867867586758675867876f);
			Assert::AreEqual(3LL, *FromFloat.GetHighPart());
			Assert::AreEqual(14154LL, *FromFloat.GetLowPart());
		}
	};
}