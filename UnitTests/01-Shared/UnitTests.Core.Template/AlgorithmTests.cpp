#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Clear.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Copy.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Reverse.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Swap.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Algorithms
{
	TEST_CLASS(AlgorithmTests)
	{
	public:
		TEST_METHOD(CopyAndClear)
		{
			int Values[3] = { 0, 1, 2 };
			int* PointerValues[3] = { &Values[0], &Values[1], &Values[2] };

			// ...
			int Target[3];

			Elysium::Core::Template::Algorithms::Copy(&Values[0], &Values[2], &Target[0]);
			Assert::AreEqual(Values[0], Target[0]);
			Assert::AreEqual(Values[1], Target[1]);
			Assert::AreEqual(Values[2], Target[2]);

			Elysium::Core::Template::Algorithms::Clear(Target[0], Target[2]);
			Assert::AreEqual(Target[0], 0);
			Assert::AreEqual(Target[1], 0);
			Assert::AreEqual(Target[2], 0);

			// ...
			int* PointerTarget[3];
			Elysium::Core::Template::Algorithms::Copy(&PointerValues[0], &PointerValues[2], &PointerTarget[0]);
			Assert::AreEqual(PointerValues[0], PointerTarget[0]);
			Assert::AreEqual(PointerValues[1], PointerTarget[1]);
			Assert::AreEqual(PointerValues[2], PointerTarget[2]);

			Elysium::Core::Template::Algorithms::Clear(PointerTarget[0], PointerTarget[2]);
			Assert::AreEqual(*PointerTarget[0], 0);
			Assert::AreEqual(*PointerTarget[1], 0);
			Assert::AreEqual(*PointerTarget[2], 0);
		}
	};
}
