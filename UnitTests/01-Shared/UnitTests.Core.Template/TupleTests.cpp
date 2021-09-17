#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Tuple.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Collections;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template
{
	TEST_CLASS(TupleTests)
	{
	public:
		TEST_METHOD(Tuple1Test)
		{
			Tuple<int> Instance = Tuple<int>(13);
			int& Item1 = Instance.GetItem1();

			Assert::AreEqual(13, Item1);

			Item1 = 27;
			Assert::AreEqual(27, Item1);
		}

		TEST_METHOD(Tuple2Test)
		{
			Tuple<int, int> Instance = Tuple<int, int>(13, 25);
			int& Item1 = Instance.GetItem1();
			int& Item2 = Instance.GetItem2();

			Assert::AreEqual(13, Item1);
			Assert::AreEqual(25, Item2);

			Item1 = 27;
			Assert::AreEqual(27, Item1);
		}

		TEST_METHOD(Tuple3Test)
		{
			Tuple<int, int, int> Instance = Tuple<int, int, int>(13, 25, -5);
			int& Item1 = Instance.GetItem1();
			int& Item2 = Instance.GetItem2();
			int& Item3 = Instance.GetItem3();

			Assert::AreEqual(13, Item1);
			Assert::AreEqual(25, Item2);
			Assert::AreEqual(-5, Item3);

			Item1 = 27;
			Assert::AreEqual(27, Item1);
		}
	};
}
